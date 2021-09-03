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
#include "scriptmanager.h"

#include <boost/filesystem.hpp>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#include "actions.h"
#include "movement.h"
#include "spells.h"
#include "talkaction.h"
#include "creatureevent.h"
#include "globalevent.h"
#include "weapons.h"

#include "monsters.h"
#include "spawn.h"
#include "raids.h"
#include "group.h"
#include "vocation.h"
#include "outfit.h"
#include "quests.h"
#include "items.h"
#include "chat.h"

#include "configmanager.h"
#include "luascript.h"

Actions* g_actions = NULL;
CreatureEvents* g_creatureEvents = NULL;
Spells* g_spells = NULL;
TalkActions* g_talkActions = NULL;
MoveEvents* g_moveEvents = NULL;
Weapons* g_weapons = NULL;
GlobalEvents* g_globalEvents = NULL;

extern Chat g_chat;
extern ConfigManager g_config;
extern Monsters g_monsters;

ScriptManager::ScriptManager()
{
	g_weapons = new Weapons();
	g_spells = new Spells();
	g_actions = new Actions();
	g_talkActions = new TalkActions();
	g_moveEvents = new MoveEvents();
	g_creatureEvents = new CreatureEvents();
	g_globalEvents = new GlobalEvents();
}

bool ScriptManager::loadSystem()
{
	std::clog << "Loading weapons... ";
	if(!g_weapons->loadFromXml())
	{
		std::clog << "failed!" << std::endl;
		return false;
	}

	std::clog << "done." << std::endl << "Preparing weapons... ";
	if(!g_weapons->loadDefaults())
	{
		std::clog << "failed!" << std::endl;
		return false;
	}

	std::clog << "done." << std::endl << "Loading spells... ";
	if(!g_spells->loadFromXml())
	{
		std::clog << "failed!" << std::endl;
		return false;
	}

	std::clog << "done." << std::endl << "Loading actions... ";
	if(!g_actions->loadFromXml())
	{
		std::clog << "failed!" << std::endl;
		return false;
	}

	std::clog << "done." << std::endl << "Loading talkactions... ";
	if(!g_talkActions->loadFromXml())
	{
		std::clog << "failed!" << std::endl;
		return false;
	}

	std::clog << "done." << std::endl << "Loading movements... ";
	if(!g_moveEvents->loadFromXml())
	{
		std::clog << "failed!" << std::endl;
		return false;
	}

	std::clog << "done." << std::endl << "Loading creaturescripts... ";
	if(!g_creatureEvents->loadFromXml())
	{
		std::clog << "failed!" << std::endl;
		return false;
	}

	std::clog << "done." << std::endl << "Loading globalscripts... ";
	if(!g_globalEvents->loadFromXml())
	{
		std::clog << "failed!" << std::endl;
		return false;
	}

	std::clog << "done." << std::endl;
	return true;
}
