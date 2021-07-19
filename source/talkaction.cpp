////////////////////////////////////////////////////////////////////////
// OpenTibia - an opensource roleplaying game
////////////////////////////////////////////////////////////////////////
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
////////////////////////////////////////////////////////////////////////
#include "otpch.h"
#include "talkaction.h"

#include <boost/config.hpp>
#include <boost/version.hpp>

#include "iologindata.h"
#include "ioban.h"

#include "player.h"
#include "npc.h"

#include "house.h"
#include "town.h"

#include "teleport.h"
#include "status.h"
#include "textlogger.h"

#ifdef __ENABLE_SERVER_DIAGNOSTIC__
#include "outputmessage.h"
#include "connection.h"
#include "admin.h"
#include "protocollogin.h"
#include "protocolold.h"
#endif

#include "configmanager.h"
#include "game.h"
#include "chat.h"
#include "tools.h"
#include "resources.h"

extern ConfigManager g_config;
extern Game g_game;
extern Chat g_chat;
extern TalkActions* g_talkActions;

TalkActions::TalkActions() :
m_interface("TalkAction Interface")
{
	m_interface.initState();
}

TalkActions::~TalkActions()
{
	clear();
}

void TalkActions::clear()
{
	for(TalkActionsMap::iterator it = talksMap.begin(); it != talksMap.end(); ++it)
		delete it->second;

	talksMap.clear();
	m_interface.reInitState();
}

Event* TalkActions::getEvent(const std::string& nodeName)
{
	if(asLowerCaseString(nodeName) == "talkaction")
		return new TalkAction(&m_interface);

	return NULL;
}

bool TalkActions::registerEvent(Event* event, xmlNodePtr p, bool override)
{
	TalkAction* talkAction = dynamic_cast<TalkAction*>(event);
	if(!talkAction)
		return false;

	std::string sep;
	if(!readXMLString(p, "separator", sep) || sep.empty())
		sep = ";";

	StringVec strVector = explodeString(talkAction->getWords(), sep);
	for(StringVec::iterator it = strVector.begin(); it != strVector.end(); ++it)
	{
		trimString(*it);
		talkAction->setWords(*it);
		if(talksMap.find(*it) != talksMap.end())
		{
			if(!override)
			{
				std::cout << "[Warning - TalkAction::configureEvent] Duplicate registered talkaction with words: " << (*it) << std::endl;
				continue;
			}
			else
				delete talksMap[(*it)];
		}

		talksMap[(*it)] = new TalkAction(talkAction);
	}

	delete talkAction;
	return true;
}

bool TalkActions::onPlayerSay(Creature* creature, uint16_t channelId, const std::string& words, bool ignoreAccess)
{
	std::string cmdstring[TALKFILTER_LAST] = words, paramstring[TALKFILTER_LAST] = "";
	size_t loc = words.find('"', 0);
	if(loc != std::string::npos && loc >= 0)
	{
		cmdstring[TALKFILTER_QUOTATION] = std::string(words, 0, loc);
		paramstring[TALKFILTER_QUOTATION] = std::string(words, (loc + 1), (words.size() - (loc - 1)));
		trimString(cmdstring[TALKFILTER_QUOTATION]);
	}

	loc = words.find(" ", 0);
	if(loc != std::string::npos && loc >= 0)
	{
		cmdstring[TALKFILTER_WORD] = std::string(words, 0, loc);
		paramstring[TALKFILTER_WORD] = std::string(words, (loc + 1), (words.size() - (loc - 1)));

		size_t sloc = words.find(" ", ++loc);
		if(sloc != std::string::npos && sloc >= 0)
		{
			cmdstring[TALKFILTER_WORD_SPACED] = std::string(words, 0, sloc);
			paramstring[TALKFILTER_WORD_SPACED] = std::string(words, (sloc + 1), (words.size() - (sloc - 1)));
		}
	}

	TalkAction* talkAction = NULL;
	for(TalkActionsMap::iterator it = talksMap.begin(); it != talksMap.end(); ++it)
	{
		if(it->first == cmdstring[it->second->getFilter()] || (!it->second->isSensitive() &&
			!strcasecmp(it->first.c_str(), cmdstring[it->second->getFilter()].c_str())))
		{
			talkAction = it->second;
			break;
		}
	}

	if(!talkAction || (talkAction->getChannel() != -1 && talkAction->getChannel() != channelId))
		return false;

	Player* player = creature->getPlayer();
	StringVec exceptions = talkAction->getExceptions();
	if(player && ((!ignoreAccess && std::find(exceptions.begin(), exceptions.end(), asLowerCaseString(
		player->getName())) == exceptions.end() && talkAction->getAccess() > player->getAccess())
		|| player->isAccountManager()))
	{
		if(player->hasCustomFlag(PlayerCustomFlag_GamemasterPrivileges))
		{
			player->sendTextMessage(MSG_STATUS_SMALL, "You cannot execute this talkaction.");
			return true;
		}

		return false;
	}

	if(talkAction->isLogged())
	{
		if(player)
			player->sendTextMessage(MSG_STATUS_CONSOLE_RED, words.c_str());

		Logger::getInstance()->eFile("talkactions/" + creature->getName() + ".log", words, true);
	}

	if(talkAction->isScripted())
		return talkAction->executeSay(creature, cmdstring[talkAction->getFilter()], paramstring[talkAction->getFilter()], channelId);

	if(TalkFunction* function = talkAction->getFunction())
		return function(creature, cmdstring[talkAction->getFilter()], paramstring[talkAction->getFilter()]);

	return false;
}

TalkAction::TalkAction(LuaScriptInterface* _interface):
Event(_interface)
{
	m_function = NULL;
	m_filter = TALKFILTER_WORD;
	m_access = 0;
	m_channel = -1;
	m_logged = m_hidden = false;
	m_sensitive = true;
}

TalkAction::TalkAction(const TalkAction* copy):
Event(copy)
{
	m_words = copy->m_words;
	m_function = copy->m_function;
	m_filter = copy->m_filter;
	m_access = copy->m_access;
	m_channel = copy->m_channel;
	m_logged = copy->m_logged;
	m_hidden = copy->m_hidden;
	m_sensitive = copy->m_sensitive;
	m_exceptions = copy->m_exceptions;
}

bool TalkAction::configureEvent(xmlNodePtr p)
{
	std::string strValue;
	if(readXMLString(p, "words", strValue))
		m_words = strValue;
	else
	{
		std::cout << "[Error - TalkAction::configureEvent] No words for TalkAction." << std::endl;
		return false;
	}

	if(readXMLString(p, "filter", strValue))
	{
		std::string tmpStrValue = asLowerCaseString(strValue);
		if(tmpStrValue == "quotation")
			m_filter = TALKFILTER_QUOTATION;
		else if(tmpStrValue == "word")
			m_filter = TALKFILTER_WORD;
		else if(tmpStrValue == "word-spaced")
			m_filter = TALKFILTER_WORD_SPACED;
		else
			std::cout << "[Warning - TalkAction::configureEvent] Unknown filter for TalkAction: " << strValue << ", using default." << std::endl;
	}

	int32_t intValue;
	if(readXMLInteger(p, "access", intValue))
		m_access = intValue;

	if(readXMLInteger(p, "channel", intValue))
		m_channel = intValue;

	if(readXMLString(p, "log", strValue) || readXMLString(p, "logged", strValue))
		m_logged = booleanString(strValue);

	if(readXMLString(p, "hide", strValue) || readXMLString(p, "hidden", strValue))
		m_hidden = booleanString(strValue);

	if(readXMLString(p, "case-sensitive", strValue) || readXMLString(p, "casesensitive", strValue) || readXMLString(p, "sensitive", strValue))
		m_sensitive = booleanString(strValue);

	if(readXMLString(p, "exception", strValue))
		m_exceptions = explodeString(asLowerCaseString(strValue), ";");

	return true;
}

bool TalkAction::loadFunction(const std::string& functionName)
{
	std::string tmpFunctionName = asLowerCaseString(functionName);
	if(tmpFunctionName == "housebuy")
		m_function = houseBuy;
 	else if(tmpFunctionName == "housesell")
		m_function = houseSell;
	else if(tmpFunctionName == "housekick")
		m_function = houseKick;
	else if(tmpFunctionName == "housedoorlist")
		m_function = houseDoorList;
	else if(tmpFunctionName == "houseguestlist")
		m_function = houseGuestList;
	else if(tmpFunctionName == "housesubownerlist")
		m_function = houseSubOwnerList;
 	else if(tmpFunctionName == "guildjoin")
		m_function = guildJoin;
 	else if(tmpFunctionName == "guildcreate")
		m_function = guildCreate;
	else if(tmpFunctionName == "thingproporties")
		m_function = thingProporties;
	else if(tmpFunctionName == "banishmentinfo")
		m_function = banishmentInfo;
	else if(tmpFunctionName == "diagnostics")
		m_function = diagnostics;
	else if(tmpFunctionName == "addskill")
		m_function = addSkill;
	else if(tmpFunctionName == "ghost")
		m_function = ghost;
		
	else if(tmpFunctionName == "setworldtype")
		m_function = setWorldType;
	else if(tmpFunctionName == "addplayerpremium")
		m_function = addPlayerPremium;
	else if(tmpFunctionName == "openserver")
		m_function = openServer;
	else if(tmpFunctionName == "closeserver")
		m_function = closeServer;
	else if(tmpFunctionName == "broadcastmessage")
		m_function = broadcastMessage;
	else if(tmpFunctionName == "broadcastclass")
		m_function = broadcastClass;
	else if(tmpFunctionName == "placenpc")
		m_function = placeNpc;
	else if(tmpFunctionName == "placemonster")
		m_function = placeMonster;
	else if(tmpFunctionName == "placesummon")
		m_function = placeSummon;
	else if(tmpFunctionName == "cleanmap")
		m_function = cleanMap;
	else if(tmpFunctionName == "multiclientcheck")
		m_function = multiClientCheck;
	else if(tmpFunctionName == "kickplayer")
		m_function = kickPlayer;
	else if(tmpFunctionName == "newtype")
		m_function = newType;
	else if(tmpFunctionName == "testcommand")
		m_function = testCommand;
	else if(tmpFunctionName == "testtutorialcommand")
		m_function = testTutorialCommand;
	else if(tmpFunctionName == "creatorserver")
		m_function = creatorServer;
	else if(tmpFunctionName == "showexpforlevel")
		m_function = showExpForLevel;
	else if(tmpFunctionName == "showmanaforlevel")
		m_function = showManaForLevel;
	else if(tmpFunctionName == "serverinfo")
		m_function = serverInfo;
	else if(tmpFunctionName == "pvpinformation")
		m_function = pvpInformation;
	else if(tmpFunctionName == "checkmoney")
		m_function = checkMoney;
	else if(tmpFunctionName == "showworlduptime")
		m_function = showWorldUpTime;
	else if(tmpFunctionName == "shownotices")
		m_function = showNotices;
	else if(tmpFunctionName == "whoisonline")
		m_function = whoIsOnline;
	else if(tmpFunctionName == "goup")
		m_function = goUp;
	else if(tmpFunctionName == "godown")
		m_function = goDown;
	else if(tmpFunctionName == "teleporttotemple")
		m_function = teleportToTemple;
	else if(tmpFunctionName == "pushplayer")
		m_function = pushPlayer;
	else if(tmpFunctionName == "teleportgoto")
		m_function = teleportGoto;
	else if(tmpFunctionName == "teleportntiles")
		m_function = teleportNTiles;
	else if(tmpFunctionName == "teleporttotown")
		m_function = teleportToTown;
	else
	{
		std::cout << "[Warning - TalkAction::loadFunction] Function \"" << functionName << "\" does not exist." << std::endl;
		return false;
	}

	m_scripted = EVENT_SCRIPT_FALSE;
	return true;
}

int32_t TalkAction::executeSay(Creature* creature, const std::string& words, std::string param, uint16_t channel)
{
	//onSay(cid, words, param, channel)
	if(m_interface->reserveEnv())
	{
		trimString(param);
		ScriptEnviroment* env = m_interface->getEnv();
		if(m_scripted == EVENT_SCRIPT_BUFFER)
		{
			env->setRealPos(creature->getPosition());
			std::stringstream scriptstream;
			scriptstream << "local cid = " << env->addThing(creature) << std::endl;

			scriptstream << "local words = \"" << words << "\"" << std::endl;
			scriptstream << "local param = \"" << param << "\"" << std::endl;
			scriptstream << "local channel = " << channel << std::endl;

			scriptstream << m_scriptData;
			bool result = true;
			if(m_interface->loadBuffer(scriptstream.str()))
			{
				lua_State* L = m_interface->getState();
				result = m_interface->getGlobalBool(L, "_result", true);
			}

			m_interface->releaseEnv();
			return result;
		}
		else
		{
			#ifdef __DEBUG_LUASCRIPTS__
			char desc[125];
			sprintf(desc, "%s - %s- %s", creature->getName().c_str(), words.c_str(), param.c_str());
			env->setEventDesc(desc);
			#endif

			env->setScriptId(m_scriptId, m_interface);
			env->setRealPos(creature->getPosition());

			lua_State* L = m_interface->getState();
			m_interface->pushFunction(m_scriptId);
			lua_pushnumber(L, env->addThing(creature));

			lua_pushstring(L, words.c_str());
			lua_pushstring(L, param.c_str());
			lua_pushnumber(L, channel);

			bool result = m_interface->callFunction(4);
			m_interface->releaseEnv();
			return result;
		}
	}
	else
	{
		std::cout << "[Error - TalkAction::executeSay] Call stack overflow." << std::endl;
		return 0;
	}
}

bool TalkAction::houseBuy(Creature* creature, const std::string& cmd, const std::string& param)
{
	Player* player = creature->getPlayer();
	if(!player || !g_config.getBool(ConfigManager::HOUSE_BUY_AND_SELL))
		return false;

	const Position& pos = getNextPosition(player->getDirection(), player->getPosition());
	Tile* tile = g_game.getTile(pos);
	if(!tile)
	{
		player->sendCancel("You have to be looking at door of flat you would like to purchase.");
		g_game.addMagicEffect(player->getPosition(), MAGIC_EFFECT_POFF);
		return false;
	}

	HouseTile* houseTile = tile->getHouseTile();
	if(!houseTile)
	{
		player->sendCancel("You have to be looking at door of flat you would like to purchase.");
		g_game.addMagicEffect(player->getPosition(), MAGIC_EFFECT_POFF);
		return false;
	}

	House* house = houseTile->getHouse();
	if(!house)
	{
		player->sendCancel("You have to be looking at door of flat you would like to purchase.");
		g_game.addMagicEffect(player->getPosition(), MAGIC_EFFECT_POFF);
		return false;
	}

	if(!house->getDoorByPosition(pos))
	{
		player->sendCancel("You have to be looking at door of flat you would like to purchase.");
		g_game.addMagicEffect(player->getPosition(), MAGIC_EFFECT_POFF);
		return false;
	}

	if(!house->isGuild())
	{
		if(Houses::getInstance()->getHouseByPlayerId(player->getGUID()))
		{
			player->sendCancel("You already rent another house.");
			g_game.addMagicEffect(player->getPosition(), MAGIC_EFFECT_POFF);
			return false;
		}

		uint16_t accountHouses = g_config.getNumber(ConfigManager::HOUSES_PER_ACCOUNT);
		if(accountHouses > 0 && Houses::getInstance()->getHousesCount(player->getAccount()) >= accountHouses)
		{
			char buffer[80];
			sprintf(buffer, "You may own only %d house%s per account.", accountHouses, (accountHouses != 1 ? "s" : ""));

			player->sendCancel(buffer);
			g_game.addMagicEffect(player->getPosition(), MAGIC_EFFECT_POFF);
			return false;
		}

		if(g_config.getBool(ConfigManager::HOUSE_NEED_PREMIUM) && !player->isPremium())
		{
			player->sendCancelMessage(RET_YOUNEEDPREMIUMACCOUNT);
			g_game.addMagicEffect(player->getPosition(), MAGIC_EFFECT_POFF);
			return false;
		}

		uint32_t levelToBuyHouse = g_config.getNumber(ConfigManager::LEVEL_TO_BUY_HOUSE);
		if(player->getLevel() < levelToBuyHouse)
		{
			char buffer[90];
			sprintf(buffer, "You have to be at least Level %d to purchase a house.", levelToBuyHouse);
			player->sendCancel(buffer);
			g_game.addMagicEffect(player->getPosition(), MAGIC_EFFECT_POFF);
			return false;
		}
	}
	else
	{
		if(!player->getGuildId() || player->getGuildLevel() != GUILDLEVEL_LEADER)
		{
			player->sendCancel("You have to be at least a guild leader to purchase a hall.");
			g_game.addMagicEffect(player->getPosition(), MAGIC_EFFECT_POFF);
			return false;
		}

		if(Houses::getInstance()->getHouseByGuildId(player->getGuildId()))
		{
			player->sendCancel("Your guild rents already another hall.");
			g_game.addMagicEffect(player->getPosition(), MAGIC_EFFECT_POFF);
			return false;
		}
	}

	if(house->getOwner())
	{
		player->sendCancel("This flat is already owned by someone else.");
		g_game.addMagicEffect(player->getPosition(), MAGIC_EFFECT_POFF);
		return false;
	}

	if(g_game.getMoney(player) < house->getPrice() || !g_game.removeMoney(player, house->getPrice()))
	{
		player->sendCancel("You do not have enough money.");
		g_game.addMagicEffect(player->getPosition(), MAGIC_EFFECT_POFF);
		return false;
	}

	house->setOwnerEx(player->getGUID(), true);
	std::string ret = "You have successfully bought this ";
	if(house->isGuild())
		ret += "hall";
	else
		ret += "house";

	ret += ", remember to leave money at ";
	if(house->isGuild())
		ret += "guild owner ";

	if(g_config.getBool(ConfigManager::BANK_SYSTEM))
		ret += "bank or ";

	ret += "depot of this town for rent.";
	player->sendTextMessage(MSG_INFO_DESCR, ret.c_str());

	g_game.addMagicEffect(player->getPosition(), MAGIC_EFFECT_WRAPS_BLUE);
	return false;
}

bool TalkAction::houseSell(Creature* creature, const std::string& cmd, const std::string& param)
{
	Player* player = creature->getPlayer();
	if(!player || !g_config.getBool(ConfigManager::HOUSE_BUY_AND_SELL))
		return false;

	House* house = Houses::getInstance()->getHouseByPlayerId(player->getGUID());
	if(!house && (!player->getGuildId() || !(house = Houses::getInstance()->getHouseByGuildId(player->getGuildId()))))
	{
		player->sendCancel("You do not rent any flat.");
		g_game.addMagicEffect(player->getPosition(), MAGIC_EFFECT_POFF);
		return false;
	}

	if(house->isGuild() && player->getGuildLevel() != GUILDLEVEL_LEADER)
	{
		player->sendCancel("You have to be at least a guild leader to sell this hall.");
		g_game.addMagicEffect(player->getPosition(), MAGIC_EFFECT_POFF);
		return false;
	}

	Player* tradePartner = NULL;
	ReturnValue ret = g_game.getPlayerByNameWildcard(param, tradePartner);
	if(ret != RET_NOERROR)
	{
		player->sendCancelMessage(ret);
		g_game.addMagicEffect(player->getPosition(), MAGIC_EFFECT_POFF);
		return false;
	}

	if(tradePartner == player)
	{
		player->sendCancel("You cannot trade with yourself.");
		g_game.addMagicEffect(player->getPosition(), MAGIC_EFFECT_POFF);
		return false;
	}

	if(!house->isGuild())
	{
		if(Houses::getInstance()->getHouseByPlayerId(tradePartner->getGUID()))
		{
			player->sendCancel("Trade player already rents another house.");
			g_game.addMagicEffect(player->getPosition(), MAGIC_EFFECT_POFF);
			return false;
		}

		uint16_t housesPerAccount = g_config.getNumber(ConfigManager::HOUSES_PER_ACCOUNT);
		if(housesPerAccount > 0 && Houses::getInstance()->getHousesCount(tradePartner->getAccount()) >= housesPerAccount)
		{
			char buffer[100];
			sprintf(buffer, "Trade player has reached limit of %d house%s per account.", housesPerAccount, (housesPerAccount != 1 ? "s" : ""));

			player->sendCancel(buffer);
			g_game.addMagicEffect(player->getPosition(), MAGIC_EFFECT_POFF);
			return false;
		}

		if(!tradePartner->isPremium() && !g_config.getBool(ConfigManager::HOUSE_NEED_PREMIUM))
		{
			player->sendCancel("Trade player does not have a premium account.");
			g_game.addMagicEffect(player->getPosition(), MAGIC_EFFECT_POFF);
			return false;
		}

		uint32_t levelToBuyHouse = g_config.getNumber(ConfigManager::LEVEL_TO_BUY_HOUSE);
		if(tradePartner->getLevel() < levelToBuyHouse)
		{
			char buffer[100];
			sprintf(buffer, "Trade player has to be at least Level %d to buy house.", levelToBuyHouse);

			player->sendCancel(buffer);
			g_game.addMagicEffect(player->getPosition(), MAGIC_EFFECT_POFF);
			return false;
		}
	}
	else
	{
		if(!tradePartner->getGuildId() || tradePartner->getGuildLevel() != GUILDLEVEL_LEADER)
		{
			player->sendCancel("Trade player has to be at least a guild leader to buy a hall.");
			g_game.addMagicEffect(player->getPosition(), MAGIC_EFFECT_POFF);
			return false;
		}

		if(Houses::getInstance()->getHouseByGuildId(tradePartner->getGuildId()))
		{
			player->sendCancel("Trade player's guild already rents another hall.");
			g_game.addMagicEffect(player->getPosition(), MAGIC_EFFECT_POFF);
			return false;
		}
	}

	if(!Position::areInRange<3,3,0>(tradePartner->getPosition(), player->getPosition()))
	{
		player->sendCancel("Trade player is too far away.");
		g_game.addMagicEffect(player->getPosition(), MAGIC_EFFECT_POFF);
		return false;
	}

	if(!Houses::getInstance()->payRent(player, house, 0))
	{
		player->sendCancel("You have to pay a pre-rent first.");
		g_game.addMagicEffect(player->getPosition(), MAGIC_EFFECT_POFF);
		return false;
	}

	Item* transferItem = TransferItem::createTransferItem(house);
	player->transferContainer.__addThing(NULL, transferItem);

	player->transferContainer.setParent(player);
	if(!g_game.internalStartTrade(player, tradePartner, transferItem))
		transferItem->onTradeEvent(ON_TRADE_CANCEL, player, NULL);

	g_game.addMagicEffect(player->getPosition(), MAGIC_EFFECT_WRAPS_BLUE);
	return false;
}

bool TalkAction::houseKick(Creature* creature, const std::string& cmd, const std::string& param)
{
	Player* player = creature->getPlayer();
	if(!player)
		return false;

	Player* targetPlayer = NULL;
	if(g_game.getPlayerByNameWildcard(param, targetPlayer) != RET_NOERROR)
		targetPlayer = player;

	House* house = Houses::getInstance()->getHouseByPlayer(targetPlayer);
	if(!house || !house->kickPlayer(player, targetPlayer))
	{
		g_game.addMagicEffect(player->getPosition(), MAGIC_EFFECT_POFF);
		player->sendCancelMessage(RET_NOTPOSSIBLE);
	}
	else
		g_game.addMagicEffect(player->getPosition(), MAGIC_EFFECT_WRAPS_BLUE);

	return false;
}

bool TalkAction::houseDoorList(Creature* creature, const std::string& cmd, const std::string& param)
{
	Player* player = creature->getPlayer();
	if(!player)
		return false;

	House* house = Houses::getInstance()->getHouseByPlayer(player);
	if(!house)
	{
		player->sendCancelMessage(RET_NOTPOSSIBLE);
		g_game.addMagicEffect(player->getPosition(), MAGIC_EFFECT_POFF);
		return false;
	}

	Door* door = house->getDoorByPosition(getNextPosition(player->getDirection(), player->getPosition()));
	if(door && house->canEditAccessList(door->getDoorId(), player))
	{
		player->setEditHouse(house, door->getDoorId());
		player->sendHouseWindow(house, door->getDoorId());
		g_game.addMagicEffect(player->getPosition(), MAGIC_EFFECT_WRAPS_BLUE);
	}
	else
	{
		player->sendCancelMessage(RET_NOTPOSSIBLE);
		g_game.addMagicEffect(player->getPosition(), MAGIC_EFFECT_POFF);
	}

	return false;
}

bool TalkAction::houseGuestList(Creature* creature, const std::string& cmd, const std::string& param)
{
	Player* player = creature->getPlayer();
	if(!player)
		return false;

	House* house = Houses::getInstance()->getHouseByPlayer(player);
	if(house && house->canEditAccessList(GUEST_LIST, player))
	{
		player->setEditHouse(house, GUEST_LIST);
		player->sendHouseWindow(house, GUEST_LIST);
		g_game.addMagicEffect(player->getPosition(), MAGIC_EFFECT_WRAPS_BLUE);
	}
	else
	{
		player->sendCancelMessage(RET_NOTPOSSIBLE);
		g_game.addMagicEffect(player->getPosition(), MAGIC_EFFECT_POFF);
	}

	return false;
}

bool TalkAction::houseSubOwnerList(Creature* creature, const std::string& cmd, const std::string& param)
{
	Player* player = creature->getPlayer();
	if(!player)
		return false;

	House* house = Houses::getInstance()->getHouseByPlayer(player);
	if(house && house->canEditAccessList(SUBOWNER_LIST, player))
	{
		player->setEditHouse(house, SUBOWNER_LIST);
		player->sendHouseWindow(house, SUBOWNER_LIST);
		g_game.addMagicEffect(player->getPosition(), MAGIC_EFFECT_WRAPS_BLUE);
	}
	else
	{
		player->sendCancelMessage(RET_NOTPOSSIBLE);
		g_game.addMagicEffect(player->getPosition(), MAGIC_EFFECT_POFF);
	}

	return false;
}

bool TalkAction::guildJoin(Creature* creature, const std::string& cmd, const std::string& param)
{
	Player* player = creature->getPlayer();
	if(!player || !g_config.getBool(ConfigManager::INGAME_GUILD_MANAGEMENT))
		return false;

	std::string param_ = param;
	trimString(param_);
	if(!player->getGuildId())
	{
		uint32_t guildId;
		if(IOGuild::getInstance()->getGuildId(guildId, param_))
		{
			if(player->isGuildInvited(guildId))
			{
				IOGuild::getInstance()->joinGuild(player, guildId);
				player->sendTextMessage(MSG_INFO_DESCR, "You have joined the guild.");

				char buffer[80];
				sprintf(buffer, "%s has joined the guild.", player->getName().c_str());
				if(ChatChannel* guildChannel = g_chat.getChannel(player, 0x00))
					guildChannel->talk(player, SPEAK_CHANNEL_RA, buffer);
			}
			else
				player->sendCancel("You are not invited to that guild.");
		}
		else
			player->sendCancel("There's no guild with that name.");
	}
	else
		player->sendCancel("You are already in a guild.");

	return true;
}

bool TalkAction::guildCreate(Creature* creature, const std::string& cmd, const std::string& param)
{
	Player* player = creature->getPlayer();
	if(!player || !g_config.getBool(ConfigManager::INGAME_GUILD_MANAGEMENT))
		return false;

	if(player->getGuildId())
	{
		player->sendCancel("You are already in a guild.");
		return true;
	}

	std::string param_ = param;
	trimString(param_);
	if(!isValidName(param_))
	{
		player->sendCancel("That guild name contains illegal characters, please choose another name.");
		return true;
	}

	const uint32_t minLength = g_config.getNumber(ConfigManager::MIN_GUILDNAME);
	const uint32_t maxLength = g_config.getNumber(ConfigManager::MAX_GUILDNAME);
	if(param_.length() < minLength)
	{
		player->sendCancel("That guild name is too short, please select a longer name.");
		return true;
	}

	if(param_.length() > maxLength)
	{
		player->sendCancel("That guild name is too long, please select a shorter name.");
		return true;
	}

	uint32_t guildId;
	if(IOGuild::getInstance()->getGuildId(guildId, param_))
	{
		player->sendCancel("There is already a guild with that name.");
		return true;
	}

	const uint32_t levelToFormGuild = g_config.getNumber(ConfigManager::LEVEL_TO_FORM_GUILD);
	if(player->getLevel() < levelToFormGuild)
	{
		char buffer[70 + levelToFormGuild];
		sprintf(buffer, "You have to be at least Level %d to form a guild.", levelToFormGuild);
		player->sendCancel(buffer);
		return true;
	}

	const int32_t premiumDays = g_config.getNumber(ConfigManager::GUILD_PREMIUM_DAYS);
	if(player->getPremiumDays() < premiumDays)
	{
		char buffer[70 + premiumDays];
		sprintf(buffer, "You need to have at least %d premium days to form a guild.", premiumDays);
		player->sendCancel(buffer);
		return true;
	}

	player->setGuildName(param_);
	IOGuild::getInstance()->createGuild(player);

	char buffer[50 + maxLength];
	sprintf(buffer, "You have formed guild \"%s\"!", param_.c_str());
	player->sendTextMessage(MSG_INFO_DESCR, buffer);
	return true;
}

bool TalkAction::thingProporties(Creature* creature, const std::string& cmd, const std::string& param)
{
	Player* player = creature->getPlayer();
	if(!player)
		return false;

	const Position& pos = getNextPosition(player->getDirection(), player->getPosition());
	Tile* tile = g_game.getTile(pos);
	if(!tile)
	{
		player->sendTextMessage(MSG_STATUS_SMALL, "No tile found.");
		g_game.addMagicEffect(player->getPosition(), MAGIC_EFFECT_POFF);
		return true;
	}

	Thing* thing = tile->getTopVisibleThing(creature);
	if(!thing)
	{
		player->sendTextMessage(MSG_STATUS_SMALL, "No object found.");
		g_game.addMagicEffect(player->getPosition(), MAGIC_EFFECT_POFF);
		return true;
	}

	boost::char_separator<char> sep(" ");
	tokenizer tokens(param, sep);

	std::string invalid;
	for(tokenizer::iterator it = tokens.begin(); it != tokens.end();)
	{
		std::string action = parseParams(it, tokens.end());
		toLowerCaseString(action);
		if(Item* item = thing->getItem())
		{
			if(action == "set")
			{
				std::string key = parseParams(it, tokens.end()), value = parseParams(it, tokens.end());
				if(atoi(value.c_str()) || value == "0")
					item->setAttribute(key, atoi(value.c_str()));
				else
					item->setAttribute(key, value);
			}
			else if(action == "erase" || action == "remove")
				item->eraseAttribute(parseParams(it, tokens.end()));
			else if(action == "action" || action == "actionid" || action == "aid")
			{
				int32_t tmp = atoi(parseParams(it, tokens.end()).c_str());
				if(tmp > 0)
					item->setActionId(tmp);
				else
					item->resetActionId();
			}
			else if(action == "unique" || action == "uniqueid" || action == "uid")
			{
				int32_t tmp = atoi(parseParams(it, tokens.end()).c_str());
				if(tmp >= 1000 || tmp <= 0xFFFF)
					item->setUniqueId(tmp);
			}
			else if(action == "destination" || action == "position"
				|| action == "pos" || action == "dest") //TODO: doesn't work
			{
				if(Teleport* teleport = item->getTeleport())
					teleport->setDestination(Position(atoi(parseParams(it,
						tokens.end()).c_str()), atoi(parseParams(it, tokens.end()).c_str()),
						atoi(parseParams(it, tokens.end()).c_str())));
			}
			else
			{
				std::stringstream s;
				s << action << " (" << parseParams(it, tokens.end()) << ")";
				invalid += s.str();
				break;
			}
		}
		else if(Creature* _creature = thing->getCreature())
		{
			if(action == "health")
				_creature->changeHealth(atoi(parseParams(it, tokens.end()).c_str()));
			else if(action == "maxhealth")
				_creature->changeMaxHealth(atoi(parseParams(it, tokens.end()).c_str()));
			else if(action == "mana")
				_creature->changeMana(atoi(parseParams(it, tokens.end()).c_str()));
			else if(action == "maxmana")
				_creature->changeMaxMana(atoi(parseParams(it, tokens.end()).c_str()));
			else if(action == "basespeed")
				_creature->setBaseSpeed(atoi(parseParams(it, tokens.end()).c_str()));
			else if(action == "droploot")
				_creature->setDropLoot((lootDrop_t)atoi(parseParams(it, tokens.end()).c_str()));
			else if(action == "lossskill")
				_creature->setLossSkill(booleanString(parseParams(it, tokens.end())));
			else if(action == "cannotmove")
				_creature->setNoMove(booleanString(parseParams(it, tokens.end())));
			else if(action == "skull")
			{
				_creature->setSkull(getSkull(parseParams(it, tokens.end())));
				g_game.updateCreatureSkull(_creature);
			}
			else if(action == "speaktype")
				_creature->setSpeakType((SpeakClasses)atoi(parseParams(it, tokens.end()).c_str()));
			else if(Player* _player = _creature->getPlayer())
			{
				if(action == "fyi")
					_player->sendFYIBox(parseParams(it, tokens.end()).c_str());
				else if(action == "tutorial")
					_player->sendTutorial(atoi(parseParams(it, tokens.end()).c_str()));
				else if(action == "guildlevel")
					_player->setGuildLevel((GuildLevel_t)atoi(parseParams(it, tokens.end()).c_str()));
				else if(action == "guildrank")
					_player->setRankId(atoi(parseParams(it, tokens.end()).c_str()));
				else if(action == "guildnick")
					_player->setGuildNick(parseParams(it, tokens.end()).c_str());
				else if(action == "group")
					_player->setGroupId(atoi(parseParams(it, tokens.end()).c_str()));
				else if(action == "vocation")
					_player->setVocation(atoi(parseParams(it, tokens.end()).c_str()));
				else if(action == "sex" || action == "gender")
					_player->setSex(atoi(parseParams(it, tokens.end()).c_str()));
				else if(action == "stamina")
					_player->setStaminaMinutes(atoi(parseParams(it, tokens.end()).c_str()));
				else if(action == "town" || action == "temple")
				{
					if(Town* town = Towns::getInstance()->getTown(parseParams(it, tokens.end())))
					{
						_player->setMasterPosition(town->getPosition());
						_player->setTown(town->getID());
					}
				}
				else if(action == "balance")
					_player->balance = atoi(parseParams(it, tokens.end()).c_str());
				else if(action == "marriage" || action == "partner")
					_player->marriage = atoi(parseParams(it, tokens.end()).c_str());
				else if(action == "rates")
					_player->rates[atoi(parseParams(it, tokens.end()).c_str())] = atof(
						parseParams(it, tokens.end()).c_str());
				else if(action == "idle")
					_player->setIdleTime(atoi(parseParams(it, tokens.end()).c_str()));
				else if(action == "capacity" || action == "cap")
					_player->setCapacity(atoi(parseParams(it, tokens.end()).c_str()));
				else if(action == "execute")
					g_talkActions->onPlayerSay(_player, atoi(parseParams(it, tokens.end()).c_str()),
						parseParams(it, tokens.end()), booleanString(parseParams(it, tokens.end())));
				else if(action == "saving" || action == "save")
					_player->switchSaving();
				else
				{
					std::stringstream s;
					s << action << " (" << parseParams(it, tokens.end()) << ")";
					invalid += s.str();
					break;
				}
			}
			else
			{
				std::stringstream s;
				s << action << " (" << parseParams(it, tokens.end()) << ")";
				invalid += s.str();
				break;
			}
		}
	}

	const SpectatorVec& list = g_game.getSpectators(pos);
	SpectatorVec::const_iterator it;

	Player* tmpPlayer = NULL;
	for(it = list.begin(); it != list.end(); ++it)
	{
		if((tmpPlayer = (*it)->getPlayer()))
			tmpPlayer->sendUpdateTile(tile, pos);
	}

	for(it = list.begin(); it != list.end(); ++it)
		(*it)->onUpdateTile(tile, pos);

	g_game.addMagicEffect(pos, MAGIC_EFFECT_WRAPS_GREEN);
	if(invalid.empty())
		return true;

	std::string tmp = "Following action was invalid: " + invalid;
	player->sendTextMessage(MSG_STATUS_CONSOLE_BLUE, tmp.c_str());
	return true;
}

bool TalkAction::banishmentInfo(Creature* creature, const std::string& cmd, const std::string& param)
{
	Player* player = creature->getPlayer();
	if(!player)
		return false;

	StringVec params = explodeString(param, ",");
	std::string what = "Account";
	trimString(params[0]);

	Ban ban;
	ban.type = BAN_ACCOUNT;
	if(params.size() > 1)
	{
		trimString(params[1]);
		if(params[0].substr(0, 1) == "p")
		{
			what = "Character";
			ban.type = BAN_PLAYER;
			ban.param = PLAYERBAN_BANISHMENT;

			ban.value = atoi(params[1].c_str());
			if(!ban.value)
			{
				IOLoginData::getInstance()->getGuidByName(ban.value, params[1], true);
				if(!ban.value)
					ban.value = IOLoginData::getInstance()->getAccountIdByName(params[1]);
			}
		}
		else
		{
			ban.value = atoi(params[1].c_str());
			if(!ban.value)
			{
				IOLoginData::getInstance()->getAccountId(params[1], ban.value);
				if(!ban.value)
					ban.value = IOLoginData::getInstance()->getAccountIdByName(params[1]);
			}
		}
	}
	else
	{
		ban.value = atoi(params[0].c_str());
		if(!ban.value)
		{
			IOLoginData::getInstance()->getAccountId(params[0], ban.value);
			if(!ban.value)
				ban.value = IOLoginData::getInstance()->getAccountIdByName(params[0]);
		}
	}

	if(!ban.value)
	{
		toLowerCaseString(what);
		player->sendCancel("Invalid " + what + (std::string)" name or id.");
		return true;
	}

	if(!IOBan::getInstance()->getData(ban))
	{
		player->sendCancel("That player or account is not banished or deleted.");
		return true;
	}

	bool deletion = ban.expires < 0;
	std::string admin = "Automatic ";
	if(!ban.adminId)
		admin += (deletion ? "deletion" : "banishment");
	else
		IOLoginData::getInstance()->getNameByGuid(ban.adminId, admin, true);

	std::string end = "Banishment will be lifted at:\n";
	if(deletion)
		end = what + (std::string)" won't be undeleted";

	char buffer[500 + ban.comment.length()];
	sprintf(buffer, "%s has been %s at:\n%s by: %s,\nfor the following reason:\n%s.\nThe action taken was:\n%s.\nThe comment given was:\n%s.\n%s%s.",
		what.c_str(), (deletion ? "deleted" : "banished"), formatDateShort(ban.added).c_str(), admin.c_str(), getReason(ban.reason).c_str(),
		getAction(ban.action, false).c_str(), ban.comment.c_str(), end.c_str(), (deletion ? "." : formatDateShort(ban.expires, true).c_str()));

	player->sendFYIBox(buffer);
	return true;
}

bool TalkAction::diagnostics(Creature* creature, const std::string& cmd, const std::string& param)
{
	Player* player = creature->getPlayer();
	if(!player)
		return false;

#ifdef __ENABLE_SERVER_DIAGNOSTIC__
	std::stringstream text;
	text << "Server diagonostic:\n";
	player->sendTextMessage(MSG_STATUS_CONSOLE_BLUE, text.str().c_str());

	text.str("");
	text << "World:" << "\n";
	text << "--------------------\n";
	text << "Player: " << g_game.getPlayersOnline() << " (" << Player::playerCount << ")" << std::endl;
	text << "Npc: " << g_game.getNpcsOnline() << " (" << Npc::npcCount << ")" << std::endl;
	text << "Monster: " << g_game.getMonstersOnline() << " (" << Monster::monsterCount << ")" << std::endl << std::endl;
	player->sendTextMessage(MSG_STATUS_CONSOLE_BLUE, text.str().c_str());

	text.str("");
	text << "Protocols:" << "\n";
	text << "--------------------\n";
	text << "ProtocolGame: " << ProtocolGame::protocolGameCount << std::endl;
	text << "ProtocolLogin: " << ProtocolLogin::protocolLoginCount << std::endl;
#ifdef __REMOTE_CONTROL__
	text << "ProtocolAdmin: " << ProtocolAdmin::protocolAdminCount << std::endl;
#endif
	text << "ProtocolStatus: " << ProtocolStatus::protocolStatusCount << std::endl;
	text << "ProtocolOld: " << ProtocolOld::protocolOldCount << std::endl << std::endl;
	player->sendTextMessage(MSG_STATUS_CONSOLE_BLUE, text.str().c_str());

	text.str("");
	text << "Connections:\n";
	text << "--------------------\n";
	text << "Active connections: " << Connection::connectionCount << "\n";
	text << "Total message pool: " << OutputMessagePool::getInstance()->getTotalMessageCount() << std::endl;
	text << "Auto message pool: " << OutputMessagePool::getInstance()->getAutoMessageCount() << std::endl;
	text << "Queued message pool: " << OutputMessagePool::getInstance()->getQueuedMessageCount() << std::endl;
	text << "Free message pool: " << OutputMessagePool::getInstance()->getAvailableMessageCount() << std::endl << std::endl;
	player->sendTextMessage(MSG_STATUS_CONSOLE_BLUE, text.str().c_str());

	text.str("");
	text << "Libraries:\n";
	text << "--------------------\n";
	text << "Platform: " << BOOST_PLATFORM << std::endl;
	text << "Compiler: " << BOOST_COMPILER << std::endl;
	text << "Boost: " << BOOST_VERSION << std::endl;
	text << "ASIO: " << BOOST_ASIO_VERSION << std::endl;
	text << "XML: " << XML_DEFAULT_VERSION << std::endl;
	text << "Lua: " << LUA_VERSION << std::endl;
	player->sendTextMessage(MSG_STATUS_CONSOLE_BLUE, text.str().c_str());

#endif
	return true;
}

bool TalkAction::addSkill(Creature* creature, const std::string& cmd, const std::string& param)
{
	Player* player = creature->getPlayer();
	if(!player)
		return false;

	StringVec params = explodeString(param, ",");
	if(params.size() < 2)
	{
		player->sendTextMessage(MSG_STATUS_SMALL, "Command requires at least 2 parameters.");
		return true;
	}

	uint32_t amount = 1;
	if(params.size() > 2)
	{
		std::string tmp = params[2];
		trimString(tmp);
		amount = (uint32_t)std::max(1, atoi(tmp.c_str()));
	}

	std::string name = params[0], skill = params[1];
	trimString(name);
	trimString(skill);

	Player* target = NULL;
	ReturnValue ret = g_game.getPlayerByNameWildcard(name, target);
	if(ret != RET_NOERROR)
	{
		player->sendCancelMessage(ret);
		return true;
	}

	if(skill[0] == 'l' || skill[0] == 'e')
		target->addExperience(uint64_t(Player::getExpForLevel(target->getLevel() + amount) - target->getExperience()));
	else if(skill[0] == 'm')
		target->addManaSpent((uint64_t)(target->getVocation()->getReqMana(target->getMagicLevel() +
			amount) - target->getSpentMana()), false);
	else
	{
		skills_t skillId = getSkillId(skill);
		target->addSkillAdvance(skillId, (uint32_t)(target->getVocation()->getReqSkillTries(skillId, target->getSkill(skillId,
			SKILL_LEVEL) + amount) - target->getSkill(skillId, SKILL_TRIES)), false);
	}

	return true;
}

bool TalkAction::ghost(Creature* creature, const std::string& cmd, const std::string& param)
{
	Player* player = creature->getPlayer();
	if(!player)
		return false;

	if(player->hasFlag(PlayerFlag_CannotBeSeen))
	{
		player->sendTextMessage(MSG_INFO_DESCR, "Command disabled for players with special, invisibility flag.");
		return true;
	}

	SpectatorVec::iterator it;
	SpectatorVec list = g_game.getSpectators(player->getPosition());
	Player* tmpPlayer = NULL;

	Condition* condition = NULL;
	if((condition = player->getCondition(CONDITION_GAMEMASTER, CONDITIONID_DEFAULT, GAMEMASTER_INVISIBLE)))
	{
		player->sendTextMessage(MSG_INFO_DESCR, "You are visible again.");
		IOLoginData::getInstance()->updateOnlineStatus(player->getGUID(), true);
		for(AutoList<Player>::iterator pit = Player::autoList.begin(); pit != Player::autoList.end(); ++pit)
		{
			if(!pit->second->canSeeCreature(player))
				pit->second->notifyLogIn(player);
		}

		for(it = list.begin(); it != list.end(); ++it)
		{
			if((tmpPlayer = (*it)->getPlayer()) && !tmpPlayer->canSeeCreature(player))
				tmpPlayer->sendMagicEffect(player->getPosition(), MAGIC_EFFECT_TELEPORT);
		}

		player->removeCondition(condition);
		g_game.internalCreatureChangeVisible(creature, VISIBLE_GHOST_APPEAR);
	}
	else if((condition = Condition::createCondition(CONDITIONID_DEFAULT, CONDITION_GAMEMASTER, -1, 0, false, GAMEMASTER_INVISIBLE)))
	{
		player->addCondition(condition);
		g_game.internalCreatureChangeVisible(creature, VISIBLE_GHOST_DISAPPEAR);
		for(it = list.begin(); it != list.end(); ++it)
		{
			if((tmpPlayer = (*it)->getPlayer()) && !tmpPlayer->canSeeCreature(player))
				tmpPlayer->sendMagicEffect(player->getPosition(), MAGIC_EFFECT_POFF);
		}

		for(AutoList<Player>::iterator pit = Player::autoList.begin(); pit != Player::autoList.end(); ++pit)
		{
			if(!pit->second->canSeeCreature(player))
				pit->second->notifyLogOut(player);
		}

		IOLoginData::getInstance()->updateOnlineStatus(player->getGUID(), false);
		if(player->isTrading())
			g_game.internalCloseTrade(player);

		player->clearPartyInvitations();
		if(player->getParty())
			player->getParty()->leave(player);

		player->sendTextMessage(MSG_INFO_DESCR, "You are now invisible.");
	}

	return true;
}


bool TalkAction::setWorldType(Creature* creature, const std::string &cmd, const std::string &param)
{
	Player* player = creature->getPlayer();

	if(!player)
	{
		return false;
	}	

	    if (player->isRemoved())
		{ 
		    return false; 
	    }
	    
		if(param == "")
		{
			player->sendTextMessage(MSG_STATUS_CONSOLE_BLUE, "Command requires param.");
		 }

		if(param == "nopvp" || param == "no-pvp" || 
				 param == "non-pvp" || param == "nonpvp" || 
				 param == "safe" || param == "optional" || 
				 param == "optionalpvp" || param == "optional-pvp")
		{
			g_game.setWorldType(WORLD_TYPE_NO_PVP);
			player->sendTextMessage(MSG_STATUS_WARNING, "Gameworld type set to: Optional-PvP.");
		 }
		if(param == "pvp" || param == "normal" || 
				 param == "open" || param == "openpvp" || 
				 param == "open-pvp")
		{
			g_game.setWorldType(WORLD_TYPE_NO_PVP);
			player->sendTextMessage(MSG_STATUS_WARNING, "Gameworld type set to: Open-PvP.");
		 }
		if(param == "enforced" || param == "pvp-enforced" || 
				 param == "pvpe" || param == "pvpenforced" || 
				 param == "war" || param == "hardcore" || 
				 param == "hardcore-pvp" || param == "hardcorepvp")
		{
			g_game.setWorldType(WORLD_TYPE_PVP_ENFORCED);
			player->sendTextMessage(MSG_STATUS_WARNING, "Gameworld type set to: Hardcore-PvP.");
		 }
	return true;
}

bool TalkAction::addPlayerPremium(Creature* creature, const std::string& cmd, const std::string& param)
{
	uint32_t premiumTime = 0;
	std::string name;
	std::istringstream in(param.c_str());

	std::getline(in, name, ',');
	in >> premiumTime;	
	
	Player* player = g_game.getPlayerByName(name);
	if(player){
		if(premiumTime < 0 || premiumTime > 999)
		{
			premiumTime = 1;
		}
		
	uint32_t days = premiumTime;
	    
     Account account = IOLoginData::getInstance()->loadAccount(player->getAccount());
		if(player->premiumDays < 65535)
		{
			if(player->premiumDays <= 50000 && days <= 10000)
			{
				account.premiumDays += days;
				player->premiumDays += days;
			}
			IOLoginData::getInstance()->saveAccount(account);
			g_game.addMagicEffect(player->getPosition(), MAGIC_EFFECT_WRAPS_BLUE);
			return true;
		}
	}
    
	return false;
}

bool TalkAction::openServer(Creature* creature, const std::string &cmd, const std::string &param)
{
 	 Player* player = creature->getPlayer();
	if(!player){
		return false;
	}
	
	g_game.setGameState(GAME_STATE_NORMAL);
	player->sendTextMessage(MSG_STATUS_CONSOLE_BLUE, "Server has been opened successfully.");

	return true;
}

bool TalkAction::closeServer(Creature* creature, const std::string &cmd, const std::string &param)
{
 	 Player* player = creature->getPlayer();
	if(!player){
		return false;
	}
	
	g_game.setGameState(GAME_STATE_CLOSED);
	
	for(AutoList<Player>::iterator it = Player::autoList.begin(); it != Player::autoList.end(); ++it)
       if(dynamic_cast<Player*>(it->second))
		if(!(*it).second->hasCustomFlag(PlayerCustomFlag_GamemasterPrivileges)){
			(*it).second->kickPlayer(true, true);
		}

	bool payHouses = (param == "serversave");
	g_game.saveGameState(payHouses);
	player->sendTextMessage(MSG_STATUS_CONSOLE_BLUE, "Server has been closed successfully.");

	return true;
}



bool TalkAction::broadcastMessage(Creature* creature, const std::string& cmd, const std::string& param)
{
	Player* player = creature->getPlayer();
	if(!player)
		return false;
		
		if(param == "")
		{
			player->sendTextMessage(MSG_STATUS_CONSOLE_BLUE, "Command requires param.");
		}

	return g_game.gmBroadcastMessage(player, param);
}

bool TalkAction::broadcastClass(Creature* creature, const std::string &cmd, const std::string &param)
{
    int a;
    int colorInt;
    Player* player = creature->getPlayer();
    std::string message = param.c_str();
    std::stringstream fullMessage;
    std::string color;
    MessageClasses mclass;
    
    for(a=0; a<param.length(); ++a)
	{
       if(param[a] > 3 && param[a] == ' ')
	   {
         color = param;
         color.erase(a,1-param.length());
         message.erase(0,1+a);
         break;
       }
       else
          message = param.c_str();       
    }
    
    std::transform(color.begin(), color.end(), color.begin(), tolower);
    fullMessage << message.c_str() <<std::endl; //Name: Message
    
    if(color == "blue")
       mclass = MSG_STATUS_CONSOLE_BLUE;
    else if(color == "red_warning")
	{
       g_game.gmBroadcastMessage(player, fullMessage.str().c_str());
       return false;
    }
    else if(color == "red")
       mclass = MSG_STATUS_CONSOLE_RED;
    else if(color == "advance")
       mclass = MSG_EVENT_ADVANCE; //Invasion
    else if(color == "event")
       mclass = MSG_EVENT_ADVANCE; //Invasion
    else if(color == "white")
       mclass = MSG_EVENT_DEFAULT;
    else if(color == "green")
       mclass = MSG_INFO_DESCR;
    else if(color == "info")
       mclass = MSG_INFO_DESCR;
    else if(color == "small")
       mclass = MSG_STATUS_SMALL;                                      
    else if(color == "warning")
        mclass = MSG_STATUS_WARNING;
    else if(color == "orange_event")
        mclass = MSG_EVENT_ORANGE;
    else if(color == "orange")
        mclass = MSG_STATUS_CONSOLE_ORANGE;
        
    else{
       player->sendTextMessage(MSG_STATUS_CONSOLE_BLUE, "The options to colors are: blue, red, advance, event, white, green, info, small, warning, orange and orange_event.");
       return false;
    }
                      
	for(AutoList<Player>::iterator it = Player::autoList.begin(); it != Player::autoList.end(); ++it)
       if(dynamic_cast<Player*>(it->second))
         (*it).second->sendTextMessage(mclass, fullMessage.str().c_str());
    
    return true;
}

bool TalkAction::placeNpc(Creature* creature, const std::string& cmd, const std::string& param)
{
	Npc* npc = Npc::createNpc(param);
	if(!npc)
		return false;

	// Place the npc
	if(g_game.placeCreature(npc, creature->getPosition()))
	{
		g_game.addMagicEffect(creature->getPosition(), MAGIC_EFFECT_BLOODYSTEPS);
		npc->setMasterPos(npc->getPosition());
		return true;
	}
	else
	{
		delete npc;
		Player* player = creature->getPlayer();
		if(player)
		{
			player->sendCancelMessage(RET_NOTENOUGHROOM);
			g_game.addMagicEffect(creature->getPosition(), MAGIC_EFFECT_POFF);
		}
		return true;
	}
	return false;
}

bool TalkAction::placeMonster(Creature* creature, const std::string& cmd, const std::string& param)
{
	Player* player = creature->getPlayer();

	Monster* monster = Monster::createMonster(param);
	if(!monster)
	{
		if(player)
		{
			player->sendCancelMessage(RET_NOTPOSSIBLE);
			g_game.addMagicEffect(player->getPosition(), MAGIC_EFFECT_POFF);
		}
		return false;
	}

	// Place the monster
	if(g_game.placeCreature(monster, creature->getPosition()))
	{
		g_game.addMagicEffect(creature->getPosition(), MAGIC_EFFECT_BLOODYSTEPS);
		return true;
	}
	else
	{
		delete monster;
		if(player)
		{
			player->sendCancelMessage(RET_NOTENOUGHROOM);
			g_game.addMagicEffect(player->getPosition(), MAGIC_EFFECT_POFF);
		}
	}

	return false;
}

ReturnValue TalkAction::placeSummon(Creature* creature, const std::string& name)
{
	Monster* monster = Monster::createMonster(name);
	if(!monster)
	{
		return RET_NOTPOSSIBLE;
	}
	// Place the monster
	creature->addSummon(monster);
	if(!g_game.placeCreature(monster, creature->getPosition()))
	{
		creature->removeSummon(monster);
		return RET_NOTENOUGHROOM;
	}

	return RET_NOERROR;
}

bool TalkAction::placeSummon(Creature* creature, const std::string& cmd, const std::string& param)
{
	ReturnValue ret = placeSummon(creature, param);

	if(ret != RET_NOERROR)
	{
		if(Player* player = creature->getPlayer())
		{
			player->sendCancelMessage(ret);
			g_game.addMagicEffect(player->getPosition(), MAGIC_EFFECT_POFF);
		}
	}
	return (ret == RET_NOERROR);
}

bool TalkAction::cleanMap(Creature* creature, const std::string &cmd, const std::string &param)
{
	uint32_t count = 0;
	g_game.cleanMap(count);
	
	char* buffer = new char[128];
	sprintf(buffer, "Game map cleaned: Cleaned %d items from the map.", count);
	
	for(AutoList<Player>::iterator it = Player::autoList.begin(); it != Player::autoList.end(); ++it)
       if(dynamic_cast<Player*>(it->second))
         (*it).second->sendTextMessage(MSG_STATUS_CONSOLE_BLUE, std::string(buffer));
	delete [] buffer;
	return true;
}


bool TalkAction::multiClientCheck(Creature* creature, const std::string& cmd, const std::string& param)
{
	Player* player = creature->getPlayer();
	if(!player)
		return false;

	std::list<uint32_t> ipList;

	std::stringstream text;
	text << "Multiclient List:";
	player->sendTextMessage(MSG_STATUS_CONSOLE_BLUE, text.str().c_str());
	text.str("");

	for(AutoList<Player>::iterator it = Player::autoList.begin(); it != Player::autoList.end(); ++it)
	{
		if(it->second->isRemoved() || it->second->getIP() == 0 || std::find(ipList.begin(), ipList.end(), it->second->getIP()) != ipList.end())
			continue;

		std::list< std::pair<std::string, uint32_t> > playerList;
		for(AutoList<Player>::iterator it2 = Player::autoList.begin(); it2 != Player::autoList.end(); ++it2)
		{
			if(it->second == it2->second || it2->second->isRemoved())
				continue;

			if(it->second->getIP() == it2->second->getIP())
				playerList.push_back(make_pair(it2->second->getName(), it2->second->getLevel()));
		}

		if(!playerList.empty())
		{
			text << convertIPAddress(it->second->getIP()) << ":\n"
			<< it->second->getName() << " [" << it->second->getLevel() << "], ";
			uint32_t tmp = 0;
			for(std::list< std::pair<std::string, uint32_t> >::const_iterator p = playerList.begin(); p != playerList.end(); p++)
			{
				tmp++;
				if(tmp != playerList.size())
					text << p->first << " [" << p->second << "], ";
				else
					text << p->first << " [" << p->second << "].";
			}

			ipList.push_back(it->second->getIP());
		}

		if(text.str() != "")
		{
			player->sendTextMessage(MSG_STATUS_CONSOLE_BLUE, text.str().c_str());
			text.str("");
		}
	}
	return true;
}

bool TalkAction::kickPlayer(Creature* creature, const std::string& cmd, const std::string& param)
{
	Player* playerKick = g_game.getPlayerByName(param);
	if(playerKick)
	{
		Player* player = creature->getPlayer();
		if(player && playerKick->getAccess() > 2)
		{
			player->sendTextMessage(MSG_STATUS_CONSOLE_BLUE, "You cannot kick this player.");
			return false;
		}

		playerKick->kickPlayer(true, true);
		return true;
	}
	return false;
}

bool TalkAction::newType(Creature* creature, const std::string& cmd, const std::string& param)
{
	Player* player = creature->getPlayer();
	if(player)
	{
		int32_t lookType = atoi(param.c_str());
		if(lookType >= 0 && lookType != 1 && lookType != 135 && (lookType <= 160 || lookType >= 192) && lookType <= 351)
		{
			g_game.internalCreatureChangeOutfit(creature, (const Outfit_t&)lookType);
			return true;
		}
		else
			player->sendTextMessage(MSG_STATUS_SMALL, "This outfit does not exist.");
	}
	return false;
}

bool TalkAction::testCommand(Creature* creature, const std::string& cmd, const std::string& param)
{
	Player* player = creature->getPlayer();
	int32_t effect = atoi(param.c_str());

    if(effect < 0 || effect > 68)
        player->sendCancel("Sorry, the effect can be 0 to 68 only.");
        else
		player->sendMagicEffect(player->getPosition(), effect);


	return true;
}

bool TalkAction::testTutorialCommand(Creature* creature, const std::string& cmd, const std::string& param)
{
	Player* player = creature->getPlayer();
	int32_t color = atoi(param.c_str());

    if(color < 0 || color > 6)
        player->sendCancel("Sorry, the tutorials test can be 0 to 6 only.");
        else
		player->sendTutorial(color);

	return true;
}

bool TalkAction::creatorServer(Creature* creature, const std::string& cmd, const std::string& param)
{
	Player* player = creature->getPlayer();
	if(player)
	{
		player->sendTextMessage(MSG_STATUS_CONSOLE_BLUE, CREATOR_INFO);
	}
	return true;
}

bool TalkAction::showExpForLevel(Creature* creature, const std::string &cmd, const std::string &param)
{
	if(Player* player = creature->getPlayer())
	{
		std::stringstream msg;
	msg << "You need " << player->getExpForLevel(player->getLevel() + 1) - player->getExperience() << " experience points to gain level" << std::endl;
		player->sendTextMessage(MSG_STATUS_CONSOLE_BLUE, msg.str().c_str());
	}
	
	return true;
}

bool TalkAction::showManaForLevel(Creature* creature, const std::string &cmd, const std::string &param)
{
	if(Player* player = creature->getPlayer())
	{
               std::stringstream msg;
               msg << "You need to spent " << (long)player->vocation->getReqMana(player->getMagicLevel()+1) - player->getSpentMana() / g_config.getDouble(ConfigManager::RATE_MAGIC) << " mana to gain magic level" << std::endl;
		player->sendTextMessage(MSG_STATUS_CONSOLE_BLUE, msg.str().c_str());
	}

	return true;
}

bool TalkAction::serverInfo(Creature* creature, const std::string& cmd, const std::string& param)
{
	Player* player = creature->getPlayer();
	if(!player)
		return false;

	std::stringstream text;
	text << "Server Info:";
	text << "\nExp Rate: " << g_game.getExperienceStage(player->level);
	text << "\nExp Rate PVP-E: " << g_config.getDouble(ConfigManager::RATE_PVP_EXPERIENCE);
	text << "\nSkill Rate: " << g_config.getDouble(ConfigManager::RATE_SKILL);
	text << "\nMagic Rate: " << g_config.getDouble(ConfigManager::RATE_MAGIC);
	text << "\nLoot Rate: " << g_config.getDouble(ConfigManager::RATE_LOOT);
	text << "\nProtection Level: " << g_config.getNumber(ConfigManager::PROTECTION_LEVEL);
    player->sendFYIBox(text.str().c_str());
	return true;
}

bool TalkAction::pvpInformation(Creature* creature, const std::string &cmd, const std::string &param)
{
	Player* player = creature->getPlayer();

	if(!player)
	{
		return false;
	}	

		int type = g_game.getWorldType();

		if (type == WORLD_TYPE_NO_PVP)
		{
			player->sendTextMessage(MSG_STATUS_CONSOLE_BLUE, "World type is currently set to: Optional-PvP.");
		}
		else if (type == WORLD_TYPE_PVP)
		{
			player->sendTextMessage(MSG_STATUS_CONSOLE_BLUE, "World type is currently set to: Open-PvP.");
		}
		else if (type == WORLD_TYPE_PVP_ENFORCED)
		{
			player->sendTextMessage(MSG_STATUS_CONSOLE_BLUE, "World type is currently set to: Hardcore-PvP.");
		}
			
	return true;
}

bool TalkAction::checkMoney(Creature* creature, const std::string& cmd, const std::string& param)
{
	Player* player = creature->getPlayer();
	if(!player)
		return false;

	int32_t count = atoi(param.c_str());
	uint32_t money = g_game.getMoney(player);
	if(!count)
	{
		char info[50];
		sprintf(info, "Money Information\n\nYou have %u gold.", money);
	    player->sendFYIBox(info);
		return true;
	}
	else if(count > (int32_t)money)
	{
		char info[80];
		sprintf(info, "Money Information\n\nYou have %u gold and is not sufficient.", money);
		player->sendTextMessage(MSG_STATUS_CONSOLE_BLUE, info);
		return true;
	}

	if(!g_game.removeMoney(player, count))
		player->sendCancel("Can not subtract money!");

	return true;
}

bool TalkAction::showWorldUpTime(Creature* creature, const std::string &cmd, const std::string &param)
{
	Player* player = creature->getPlayer();

		if(!player){
		return false;
	}	
		
    if (player->isRemoved())
	{ 
      return false; 
    }
	
	if (player)
	{
		uint64_t uptime = (OTSYS_TIME() - Status::getInstance()->m_start)/1000;
		int h = (int)floor(uptime / 3600.0);
		int m = (int)floor((uptime - h*3600) / 60.0);
		int s = (int)(uptime - h*3600 - m*60);

		std::stringstream msg;
		msg << "This server has been running for " << h << (h != 1? " hours " : " hour ") <<
			m << (m != 1? " minutes " : " minute ") << s << (s != 1? " seconds. " : " second.") << std::ends;

		player->sendTextMessage(MSG_STATUS_CONSOLE_BLUE, msg.str().c_str());
	}
	return true;
}

bool TalkAction::showNotices(Creature* creature, const std::string &cmd, const std::string &param)
{
 	 Player* player = creature->getPlayer();

	    if(!player)
		    return false;

			g_game.sendNoticeBox(g_config.getString(ConfigManager::DATA_DIRECTORY), player);
  return true;
}


bool TalkAction::whoIsOnline(Creature* creature, const std::string &cmd, const std::string &param)
{
	Player* player = creature->getPlayer();
	if(player)
	{
		std::stringstream ss;
		ss << "Players online:" << std::endl;

		uint32_t i = 0;
		AutoList<Player>::iterator it = Player::autoList.begin();
		if(!g_config.getBool(ConfigManager::SHOW_GAMEMASTERS_ONLINE))
		{
			while(it != Player::autoList.end())
			{
				if(!(*it).second->getAccess() || player->getAccess() > 2)
				{
					ss << (i > 0 ? ", " : "") << (*it).second->name << " [" << (*it).second->level << "]";
					++i;
				}
				++it;

				if(i == 10)
				{
					ss << (it != Player::autoList.end() ? "," : ".");
					player->sendTextMessage(MSG_STATUS_CONSOLE_BLUE, ss.str());
					ss.str("");
					i = 0;
				}
			}
		}
		else
		{
			while(it != Player::autoList.end())
			{
				ss << (i > 0 ? ", " : "") << (*it).second->name << " [" << (*it).second->level << "]";
				++it;
				++i;

				if(i == 10)
				{
					ss << (it != Player::autoList.end() ? "," : ".");
					player->sendTextMessage(MSG_STATUS_CONSOLE_BLUE, ss.str());
					ss.str("");
					i = 0;
				}
			}
		}

		if(i > 0)
		{
			ss << ".";
			player->sendTextMessage(MSG_STATUS_CONSOLE_BLUE, ss.str());
		}
	}
	return true;
}

bool TalkAction::goUp(Creature* creature, const std::string &cmd, const std::string &param)
{
	 	Position oldPos = creature->getPosition();
		Position newPos = creature->getPosition();
	newPos.z--;
	if(g_game.internalTeleport(creature, newPos, true) == RET_NOERROR)
	{
			g_game.addMagicEffect(oldPos, MAGIC_EFFECT_POFF);							 
			g_game.addMagicEffect(newPos, MAGIC_EFFECT_ENERGY_AREA);

	return true;
    }
 return false;
}

bool TalkAction::goDown(Creature* creature, const std::string &cmd, const std::string &param)
{
	 	Position oldPos = creature->getPosition();
		Position newPos = creature->getPosition();
	newPos.z++;
	if(g_game.internalTeleport(creature, newPos, true) == RET_NOERROR)
	{
			g_game.addMagicEffect(oldPos, MAGIC_EFFECT_POFF);							 
			g_game.addMagicEffect(newPos, MAGIC_EFFECT_ENERGY_AREA);

	return true;
    }
 return false;
}

bool TalkAction::teleportToTemple(Creature* creature, const std::string& cmd, const std::string& param)
{
	 	Position oldPos = creature->getPosition();
		Position newPos = creature->getPosition();
	
	if(g_game.internalTeleport(creature, creature->masterPosition, true) == RET_NOERROR)
	{
			g_game.addMagicEffect(oldPos, MAGIC_EFFECT_POFF);							 
			g_game.addMagicEffect(newPos, MAGIC_EFFECT_ENERGY_AREA);
		return true;
	}

	return false;
}

bool TalkAction::pushPlayer(Creature* creature, const std::string& cmd, const std::string& param)
{
	Creature* paramCreature = g_game.getCreatureByName(param);
	if(paramCreature)
	{

	 	Position oldPos = paramCreature->getPosition();
		Position newPos = paramCreature->getPosition();
		if(g_game.internalTeleport(paramCreature, creature->getPosition(), true) == RET_NOERROR)
		{
			g_game.addMagicEffect(oldPos, MAGIC_EFFECT_POFF);							 
			g_game.addMagicEffect(newPos, MAGIC_EFFECT_ENERGY_AREA);
			return true;
		}
	}

	return false;
}

bool TalkAction::teleportGoto(Creature* creature, const std::string& cmd, const std::string& param)
{
	Creature* paramCreature = g_game.getCreatureByName(param);
	if(paramCreature)
	{
	 	Position oldPos = creature->getPosition();
		Position newPos = creature->getPosition();
		if(g_game.internalTeleport(creature, paramCreature->getPosition(), true) == RET_NOERROR)
		{
			g_game.addMagicEffect(oldPos, MAGIC_EFFECT_POFF);							 
			g_game.addMagicEffect(newPos, MAGIC_EFFECT_ENERGY_AREA);
			return true;
		}
	}

	return false;
}

bool TalkAction::teleportNTiles(Creature* creature, const std::string& cmd, const std::string& param)
{
	int ntiles = atoi(param.c_str());
	if(ntiles != 0)
	{
	 	Position oldPos = creature->getPosition();
		Position newPos = creature->getPosition();
	switch(creature->getDirection())
		{
		case NORTH:
			newPos.y = newPos.y - ntiles;
			break;
		case SOUTH:
			newPos.y = newPos.y + ntiles;
			break;
		case EAST:
			newPos.x = newPos.x + ntiles;
			break;
		case WEST:
			newPos.x = newPos.x - ntiles;
			break;
		default:
			break;
		}

		if(g_game.internalTeleport(creature, newPos, true) == RET_NOERROR)
		{
			g_game.addMagicEffect(oldPos, MAGIC_EFFECT_POFF);							 
			g_game.addMagicEffect(newPos, MAGIC_EFFECT_ENERGY_AREA);
		}
	}

	return true;
}

bool TalkAction::teleportToTown(Creature* creature, const std::string& cmd, const std::string& param)
{
	std::string tmp = param;
	Player* player = creature->getPlayer();

	if(!player)
	{
		return false;
	}

	Town* town = Towns::getInstance()->getTown(tmp);
	if(town)
	{
		if(g_game.internalTeleport(creature, town->getTemplePosition(), true) == RET_NOERROR) {
			g_game.addMagicEffect(town->getTemplePosition(), MAGIC_EFFECT_ENERGY_AREA);
			return true;
		}
	}

	player->sendCancel("Could not find the town.");

	return false;
}
