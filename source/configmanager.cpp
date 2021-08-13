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
#include <iostream>

#include "configmanager.h"
#include "house.h"
#include "tools.h"

ConfigManager::ConfigManager()
{
	L = NULL;
	m_loaded = false;
	m_startup = true;

	integer[ENCRYPTION] = ENCRYPTION_SHA1;
	string[CONFIG_FILE] = getFilePath(FILE_TYPE_CONFIG, "config.lua");

	integer[LOGIN_PORT] = integer[GAME_PORT] = integer[STATUS_PORT] = 0;
	string[DATA_DIRECTORY] = string[LOGS_DIRECTORY] = string[IP] = string[RUNFILE] = string[OUTPUT_LOG] = string[ENCRYPTION_KEY] = "";
	boolean[LOGIN_ONLY_LOGINSERVER] = boolean[START_CLOSED] = false;
	boolean[SCRIPT_SYSTEM] = true;
}

bool ConfigManager::load()
{
	if(L)
		lua_close(L);

	L = luaL_newstate();
	if(!L)
		return false;

	luaL_openlibs(L);
	if(luaL_dofile(L, string[CONFIG_FILE].c_str()))
	{
		lua_close(L);
		L = NULL;
		return false;
	}

	if(!m_loaded) //info that must be loaded one time (unless we reset the modules involved)
	{
		if(string[DATA_DIRECTORY] == "")
			string[DATA_DIRECTORY] = getGlobalString("dataDirectory", "data/");

		if(string[LOGS_DIRECTORY] == "")
			string[LOGS_DIRECTORY] = getGlobalString("logsDirectory", "logs/");

		if(string[IP] == "")
			string[IP] = getGlobalString("ip", "127.0.0.1");

		if(string[RUNFILE] == "")
			string[RUNFILE] = getGlobalString("runFile", "");

		if(string[OUTPUT_LOG] == "")
			string[OUTPUT_LOG] = getGlobalString("outputLog", "");

		if(integer[LOGIN_PORT] == 0)
			integer[LOGIN_PORT] = getGlobalNumber("loginPort", 7171);

		if(integer[GAME_PORT] == 0)
			integer[GAME_PORT] = getGlobalNumber("gamePort", 7172);

		if(integer[STATUS_PORT] == 0)
			integer[STATUS_PORT] = getGlobalNumber("statusPort", 7171);

		#ifdef MULTI_SQL_DRIVERS
		string[SQL_TYPE] = getGlobalString("sqlType", "sqlite");
		#endif
		string[SQL_HOST] = getGlobalString("sqlHost", "localhost");
		string[SQL_DB] = getGlobalString("sqlDatabase", "crystalserver");
		string[SQL_USER] = getGlobalString("sqlUser", "root");
		string[SQL_PASS] = getGlobalString("sqlPass", "");
		string[SQL_FILE] = getGlobalString("sqlFile", "crystalserver.s3db");
		string[MAP_NAME] = getGlobalString("mapName", "DnSend");
		string[HOUSE_RENT_PERIOD] = getGlobalString("houseRentPeriod", "monthly");
		string[ENCRYPTION_TYPE] = getGlobalString("encryptionType", "sha1");
		string[RSA_PRIME1] = getGlobalString("rsaPrime1", "14299623962416399520070177382898895550795403345466153217470516082934737582776038882967213386204600674145392845853859217990626450972452084065728686565928113");
		string[RSA_PRIME2] = getGlobalString("rsaPrime2", "7630979195970404721891201847792002125535401292779123937207447574596692788513647179235335529307251350570728407373705564708871762033017096809910315212884101");
		string[RSA_PUBLIC] = getGlobalString("rsaPublic", "65537");
		string[RSA_MODULUS] = getGlobalString("rsaModulus", "109120132967399429278860960508995541528237502902798129123468757937266291492576446330739696001110603907230888610072655818825358503429057592827629436413108566029093628212635953836686562675849720620786279431090218017681061521755056710823876476444260558147179707119674283982419152118103759076030616683978566631413");
		string[RSA_PRIVATE] = getGlobalString("rsaPrivate", "46730330223584118622160180015036832148732986808519344675210555262940258739805766860224610646919605860206328024326703361630109888417839241959507572247284807035235569619173792292786907845791904955103601652822519121908367187885509270025388641700821735345222087940578381210879116823013776808975766851829020659073");
		string[DEFAULT_PRIORITY] = getGlobalString("defaultPriority", "high");

		integer[GLOBALSAVE_H] = getGlobalNumber("globalSaveHour", 8);
		integer[AUTO_SAVE_EACH_MINUTES] = getGlobalNumber("autoSaveEachMinutes", 0);
		integer[SQL_PORT] = getGlobalNumber("sqlPort", 3306);
		integer[SQL_KEEPALIVE] = getGlobalNumber("sqlKeepAlive", 0);
		integer[MYSQL_READ_TIMEOUT] = getGlobalNumber("mysqlReadTimeout", 10);
		integer[MYSQL_WRITE_TIMEOUT] = getGlobalNumber("mysqlWriteTimeout", 10);
		integer[WORLD_ID] = getGlobalNumber("worldId", 0);

		#ifndef __LOGIN_SERVER__
		boolean[LOGIN_ONLY_LOGINSERVER] = getGlobalBool("loginOnlyWithLoginServer", false);
		#endif
		boolean[GLOBALSAVE_ENABLED] = getGlobalBool("globalSaveEnabled", true);
		boolean[TRUNCATE_LOGS] = getGlobalBool("truncateLogsOnStartup", true);
		boolean[OPTIMIZE_DATABASE] = getGlobalBool("optimizeDatabaseAtStartup", true);
		boolean[RANDOMIZE_TILES] = getGlobalBool("randomizeTiles", true);
		boolean[STORE_TRASH] = getGlobalBool("storeTrash", true);
		boolean[EXPERIENCE_STAGES] = getGlobalBool("experienceStages", false);
		boolean[GUILD_HALLS] = getGlobalBool("guildHalls", false);
		boolean[BIND_ONLY_GLOBAL_ADDRESS] = getGlobalBool("bindOnlyGlobalAddress", false);
	}

	string[MAP_AUTHOR] = getGlobalString("mapAuthor", "Unknown");
	string[SERVER_NAME] = getGlobalString("serverName");
	string[OWNER_NAME] = getGlobalString("ownerName");
	string[OWNER_EMAIL] = getGlobalString("ownerEmail");
	string[URL] = getGlobalString("url");
	string[LOCATION] = getGlobalString("location");
	string[MOTD] = getGlobalString("motd");
	string[WORLD_TYPE] = getGlobalString("worldType", "open");
	string[HOUSE_STORAGE] = getGlobalString("houseDataStorage", "binary");
	string[PREFIX_CHANNEL_LOGS] = getGlobalString("prefixChannelLogs", "");
	string[CORES_USED] = getGlobalString("coresUsed", "-1");
	string[MAILBOX_DISABLED_TOWNS] = getGlobalString("mailboxDisabledTowns", "-1");

	integer[LOGIN_TRIES] = getGlobalNumber("loginTries", 3);
	integer[RETRY_TIMEOUT] = getGlobalNumber("retryTimeout", 30 * 1000);
	integer[LOGIN_TIMEOUT] = getGlobalNumber("loginTimeout", 5 * 1000);
	integer[MAX_MESSAGEBUFFER] = getGlobalNumber("maxMessageBuffer", 4);
	integer[MAX_PLAYERS] = getGlobalNumber("maxPlayers");
	integer[DEFAULT_DESPAWNRANGE] = getGlobalNumber("deSpawnRange", 2);
	integer[DEFAULT_DESPAWNRADIUS] = getGlobalNumber("deSpawnRadius", 50);
	integer[PZ_LOCKED] = getGlobalNumber("pzLocked", 60 * 1000);
	integer[HUNTING_DURATION] = getGlobalNumber("huntingDuration", 60 * 1000);
	integer[ALLOW_CLONES] = getGlobalNumber("allowClones", 0);
	integer[RATE_SPAWN] = getGlobalNumber("rateSpawn", 1);
	integer[PARTY_RADIUS_X] = getGlobalNumber("experienceShareRadiusX", 30);
	integer[PARTY_RADIUS_Y] = getGlobalNumber("experienceShareRadiusY", 30);
	integer[PARTY_RADIUS_Z] = getGlobalNumber("experienceShareRadiusZ", 1);
	integer[SPAWNPOS_X] = getGlobalNumber("newPlayerSpawnPosX", 100);
	integer[SPAWNPOS_Y] = getGlobalNumber("newPlayerSpawnPosY", 100);
	integer[SPAWNPOS_Z] = getGlobalNumber("newPlayerSpawnPosZ", 7);
	integer[SPAWNTOWN_ID] = getGlobalNumber("newPlayerTownId", 1);
	integer[START_LEVEL] = getGlobalNumber("newPlayerLevel", 1);
	integer[START_MAGICLEVEL] = getGlobalNumber("newPlayerMagicLevel", 0);
	integer[HOUSE_PRICE] = getGlobalNumber("housePriceEachSquare", 1000);
	integer[WHITE_SKULL_TIME] = getGlobalNumber("whiteSkullTime", 15 * 60 * 1000);
	integer[HIGHSCORES_TOP] = getGlobalNumber("highscoreDisplayPlayers", 10);
	integer[HIGHSCORES_UPDATETIME] = getGlobalNumber("updateHighscoresAfterMinutes", 60);
	integer[ACTIONS_DELAY_INTERVAL] = getGlobalNumber("timeBetweenActions", 200);
	integer[EX_ACTIONS_DELAY_INTERVAL] = getGlobalNumber("timeBetweenExActions", 1000);
	integer[PROTECTION_LEVEL] = getGlobalNumber("protectionLevel", 1);
	integer[STATUSQUERY_TIMEOUT] = getGlobalNumber("statusTimeout", 5 * 60 * 1000);
	integer[LEVEL_TO_FORM_GUILD] = getGlobalNumber("levelToFormGuild", 8);
	integer[MIN_GUILDNAME] = getGlobalNumber("minGuildNameLength", 4);
	integer[MAX_GUILDNAME] = getGlobalNumber("maxGuildNameLength", 20);
	integer[LEVEL_TO_BUY_HOUSE] = getGlobalNumber("levelToBuyHouse", 1);
	integer[HOUSES_PER_ACCOUNT] = getGlobalNumber("housesPerAccount", 0);
	integer[FIELD_OWNERSHIP] = getGlobalNumber("fieldOwnershipDuration", 5 * 1000);
	integer[RED_SKULL_LENGTH] = getGlobalNumber("redSkullLength", 30 * 24 * 60 * 60);
	integer[BLACK_SKULL_LENGTH] = getGlobalNumber("blackSkullLength", 45 * 24 * 60 * 60);
	integer[MAX_VIOLATIONCOMMENT_SIZE] = getGlobalNumber("maxViolationCommentSize", 60);
	integer[NOTATIONS_TO_BAN] = getGlobalNumber("notationsToBan", 3);
	integer[WARNINGS_TO_FINALBAN] = getGlobalNumber("warningsToFinalBan", 4);
	integer[WARNINGS_TO_DELETION] = getGlobalNumber("warningsToDeletion", 5);
	integer[BAN_LENGTH] = getGlobalNumber("banLength", 7 * 24 * 60 * 60);
	integer[KILLS_BAN_LENGTH] = getGlobalNumber("killsBanLength", 7 * 24 * 60 * 60);
	integer[FINALBAN_LENGTH] = getGlobalNumber("finalBanLength", 30 * 24 * 60 * 60);
	integer[IPBANISHMENT_LENGTH] = getGlobalNumber("ipBanishmentLength", 1 * 24 * 60 * 60);
	integer[MAX_PLAYER_SUMMONS] = getGlobalNumber("maxPlayerSummons", 2);
	integer[EXTRA_PARTY_PERCENT] = getGlobalNumber("extraPartyExperiencePercent", 5);
	integer[EXTRA_PARTY_LIMIT] = getGlobalNumber("extraPartyExperienceLimit", 20);
	integer[LOGIN_PROTECTION] = getGlobalNumber("loginProtectionPeriod", 10 * 1000);
	integer[PLAYER_DEEPNESS] = getGlobalNumber("playerQueryDeepness", 1);
	integer[STAIRHOP_DELAY] = getGlobalNumber("stairhopDelay", 2 * 1000);
	integer[RATE_STAMINA_LOSS] = getGlobalNumber("rateStaminaLoss", 1);
	integer[STAMINA_LIMIT_TOP] = getGlobalNumber("staminaRatingLimitTop", 41 * 60);
	integer[STAMINA_LIMIT_BOTTOM] = getGlobalNumber("staminaRatingLimitBottom", 14 * 60);
	integer[BLESS_REDUCTION_BASE] = getGlobalNumber("blessingReductionBase", 30);
	integer[BLESS_REDUCTION_DECREAMENT] = getGlobalNumber("blessingReductionDecreament", 5);
	integer[BLESS_REDUCTION] = getGlobalNumber("eachBlessReduction", 8);
	integer[NICE_LEVEL] = getGlobalNumber("niceLevel", 5);
	integer[EXPERIENCE_COLOR] = getGlobalNumber("gainExperienceColor", COLOR_WHITE);
	integer[GUILD_PREMIUM_DAYS] = getGlobalNumber("premiumDaysToFormGuild", 0);
	integer[PUSH_CREATURE_DELAY] = getGlobalNumber("pushCreatureDelay", 2 * 1000);
	integer[DEATH_CONTAINER] = getGlobalNumber("deathContainerId", 1987);
	integer[MAXIMUM_DOOR_LEVEL] = getGlobalNumber("maximumDoorLevel", 500);
	integer[DEATH_ASSISTS] = getGlobalNumber("deathAssistCount", 1);
	integer[RED_DAILY_LIMIT] = getGlobalNumber("dailyFragsToRedSkull", 3);
	integer[RED_WEEKLY_LIMIT] = getGlobalNumber("weeklyFragsToRedSkull", 5);
	integer[RED_MONTHLY_LIMIT] = getGlobalNumber("monthlyFragsToRedSkull", 10);
	integer[BLACK_DAILY_LIMIT] = getGlobalNumber("dailyFragsToBlackSkull", integer[RED_DAILY_LIMIT]);
	integer[BLACK_WEEKLY_LIMIT] = getGlobalNumber("weeklyFragsToBlackSkull", integer[RED_WEEKLY_LIMIT]);
	integer[BLACK_MONTHLY_LIMIT] = getGlobalNumber("monthlyFragsToBlackSkull", integer[RED_MONTHLY_LIMIT]);
	integer[BAN_DAILY_LIMIT] = getGlobalNumber("dailyFragsToBanishment", integer[RED_DAILY_LIMIT]);
	integer[BAN_WEEKLY_LIMIT] = getGlobalNumber("weeklyFragsToBanishment", integer[RED_WEEKLY_LIMIT]);
	integer[BAN_MONTHLY_LIMIT] = getGlobalNumber("monthlyFragsToBanishment", integer[RED_MONTHLY_LIMIT]);
	integer[BLACK_SKULL_DEATH_HEALTH] = getGlobalNumber("blackSkulledDeathHealth", 40);
	integer[BLACK_SKULL_DEATH_MANA] = getGlobalNumber("blackSkulledDeathMana", 0);
	integer[DEATHLIST_REQUIRED_TIME] = getGlobalNumber("deathListRequiredTime", 1 * 60 * 1000);
	integer[EXPERIENCE_SHARE_ACTIVITY] = getGlobalNumber("experienceShareActivity", 2 * 60 * 1000);
	integer[TILE_LIMIT] = getGlobalNumber("tileLimit", 0);
	integer[PROTECTION_TILE_LIMIT] = getGlobalNumber("protectionTileLimit", 0);
	integer[HOUSE_TILE_LIMIT] = getGlobalNumber("houseTileLimit", 0);
	integer[SQUARE_COLOR] = getGlobalNumber("squareColor", 0);
	integer[LOOT_MESSAGE] = getGlobalNumber("monsterLootMessage", 3);
	integer[LOOT_MESSAGE_TYPE] = getGlobalNumber("monsterLootMessageType", 25);
	integer[NAME_REPORT_TYPE] = getGlobalNumber("violationNameReportActionType", 2);
	integer[HOUSE_CLEAN_OLD] = getGlobalNumber("houseCleanOld", 0);
	integer[MANAGER_PASS_LENGTH] = getGlobalNumber("minPasswordLength", 6);
	integer[MANAGER_ACCNAME_MIN_LENGTH] = getGlobalNumber("minAccountNameLength", 3);
	integer[MANAGER_ACCNAME_MAX_LENGTH] = getGlobalNumber("maxAccountNameLength", 25);
	integer[MANAGER_MIN_PLAYER_NAME_LENGTH] = getGlobalNumber("minNewCharacterNameLength", 3);
	integer[MANAGER_MAX_PLAYER_NAME_LENGTH] = getGlobalNumber("maxNewCharacterNameLength", 25);
	integer[CRITICAL_HIT_CHANCE] = getGlobalNumber("criticalHitChance", 5);
	integer[CRITICAL_COLOR] = getGlobalNumber("criticalHitColor", COLOR_TEAL);
	integer[MIN_GUILD_NICK] = getGlobalNumber("minGuildNickLength", 2);
	integer[MAX_GUILD_NICK] = getGlobalNumber("maxGuildNickLength", 25);
	integer[STAMINA_DESTROY_LOOT] = getGlobalNumber("staminaLootLimit", 14 * 60);
	integer[VIPLIST_DEFAULT_LIMIT] = getGlobalNumber("vipListDefaultLimit", 20);
	integer[VIPLIST_DEFAULT_PREMIUM_LIMIT] = getGlobalNumber("vipListDefaultPremiumLimit", 100);
	integer[FIST_BASE_ATTACK] = getGlobalNumber("fistBaseAttack", 7);

	m_confDouble[RATE_EXPERIENCE] = getGlobalDouble("rateExperience", 1);
	m_confDouble[RATE_SKILL] = getGlobalDouble("rateSkill", 1);
	m_confDouble[RATE_MAGIC] = getGlobalDouble("rateMagic", 1);
	m_confDouble[RATE_LOOT] = getGlobalDouble("rateLoot", 1);
	m_confDouble[PARTY_DIFFERENCE] = getGlobalDouble("experienceShareLevelDifference", (double)2 / 3);
	m_confDouble[RATE_PVP_EXPERIENCE] = getGlobalDouble("rateExperienceFromPlayers", 0);
	m_confDouble[EFP_MIN_THRESHOLD] = getGlobalDouble("minLevelThresholdForKilledPlayer", 0.9f);
	m_confDouble[EFP_MAX_THRESHOLD] = getGlobalDouble("maxLevelThresholdForKilledPlayer", 1.1f);
	m_confDouble[RATE_STAMINA_GAIN] = getGlobalDouble("rateStaminaGain", 3);
	m_confDouble[RATE_STAMINA_THRESHOLD] = getGlobalDouble("rateStaminaThresholdGain", 12);
	m_confDouble[RATE_STAMINA_ABOVE] = getGlobalDouble("rateStaminaAboveNormal", 1.5f);
	m_confDouble[RATE_STAMINA_UNDER] = getGlobalDouble("rateStaminaUnderNormal", 0.5f);
	m_confDouble[FORMULA_LEVEL] = getGlobalDouble("formulaLevel", 5.0);
	m_confDouble[FORMULA_MAGIC] = getGlobalDouble("formulaMagic", 1.0);
	m_confDouble[RATE_MONSTER_HEALTH] = getGlobalDouble("rateMonsterHealth", 1);
	m_confDouble[RATE_MONSTER_MANA] = getGlobalDouble("rateMonsterMana", 1);
	m_confDouble[RATE_MONSTER_ATTACK] = getGlobalDouble("rateMonsterAttack", 1);
	m_confDouble[RATE_MONSTER_DEFENSE] = getGlobalDouble("rateMonsterDefense", 1);
	m_confDouble[CRITICAL_HIT_MUL] = getGlobalDouble("criticalHitMultiplier", 1);

	boolean[ACCOUNT_MANAGER] = getGlobalBool("accountManager", true);
	boolean[NAMELOCK_MANAGER] = getGlobalBool("namelockManager", false);
	boolean[START_CHOOSEVOC] = getGlobalBool("newPlayerChooseVoc", false);
	boolean[ON_OR_OFF_CHARLIST] = getGlobalBool("displayOnOrOffAtCharlist", false);
	boolean[ALLOW_CHANGEOUTFIT] = getGlobalBool("allowChangeOutfit", true);
	boolean[ONE_PLAYER_ON_ACCOUNT] = getGlobalBool("onePlayerOnlinePerAccount", true);
	boolean[CANNOT_ATTACK_SAME_LOOKFEET] = getGlobalBool("noDamageToSameLookfeet", false);
	boolean[AIMBOT_HOTKEY_ENABLED] = getGlobalBool("hotkeyAimbotEnabled", true);
	boolean[REMOVE_WEAPON_AMMO] = getGlobalBool("removeWeaponAmmunition", true);
	boolean[REMOVE_WEAPON_CHARGES] = getGlobalBool("removeWeaponCharges", true);
	boolean[REMOVE_RUNE_CHARGES] = getGlobalBool("removeRuneCharges", true);
	boolean[SHUTDOWN_AT_GLOBALSAVE] = getGlobalBool("shutdownAtGlobalSave", false);
	boolean[CLEAN_MAP_AT_GLOBALSAVE] = getGlobalBool("cleanMapAtGlobalSave", true);
	boolean[FREE_PREMIUM] = getGlobalBool("freePremium", false);
	boolean[BROADCAST_BANISHMENTS] = getGlobalBool("broadcastBanishments", true);
	boolean[GENERATE_ACCOUNT_NUMBER] = getGlobalBool("generateAccountNumber", true);
	boolean[GENERATE_ACCOUNT_SALT] = getGlobalBool("generateAccountSalt", false);
	boolean[INGAME_GUILD_MANAGEMENT] = getGlobalBool("ingameGuildManagement", true);
	boolean[HOUSE_BUY_AND_SELL] = getGlobalBool("buyableAndSellableHouses", true);
	boolean[REPLACE_KICK_ON_LOGIN] = getGlobalBool("replaceKickOnLogin", true);
	boolean[HOUSE_NEED_PREMIUM] = getGlobalBool("houseNeedPremium", true);
	boolean[HOUSE_RENTASPRICE] = getGlobalBool("houseRentAsPrice", false);
	boolean[HOUSE_PRICEASRENT] = getGlobalBool("housePriceAsRent", false);
	boolean[BANK_SYSTEM] = getGlobalBool("bankSystem", true);
	boolean[PREMIUM_FOR_PROMOTION] = getGlobalBool("premiumForPromotion", true);
	boolean[REMOVE_PREMIUM_ON_INIT] = getGlobalBool("removePremiumOnInit", true);
	boolean[SHOW_HEALING_DAMAGE] = getGlobalBool("showHealingDamage", false);
	boolean[TELEPORT_SUMMONS] = getGlobalBool("teleportAllSummons", false);
	boolean[TELEPORT_PLAYER_SUMMONS] = getGlobalBool("teleportPlayerSummons", false);
	boolean[PVP_TILE_IGNORE_PROTECTION] = getGlobalBool("pvpTileIgnoreLevelAndVocationProtection", true);
	boolean[ADVANCING_SKILL_LEVEL] = getGlobalBool("displaySkillLevelOnAdvance", false);
	boolean[CLEAN_PROTECTED_ZONES] = getGlobalBool("cleanProtectedZones", true);
	boolean[SPELL_NAME_INSTEAD_WORDS] = getGlobalBool("spellNameInsteadOfWords", false);
	boolean[EMOTE_SPELLS] = getGlobalBool("emoteSpells", false);
	boolean[UNIFIED_SPELLS] = getGlobalBool("unifiedSpells", true);
	boolean[SAVE_GLOBAL_STORAGE] = getGlobalBool("saveGlobalStorage", true);
	boolean[FORCE_CLOSE_SLOW_CONNECTION] = getGlobalBool("forceSlowConnectionsToDisconnect", false);
	boolean[BLESSING_ONLY_PREMIUM] = getGlobalBool("blessingOnlyPremium", true);
	boolean[BED_REQUIRE_PREMIUM] = getGlobalBool("bedsRequirePremium", true);
	boolean[ALLOW_CHANGECOLORS] = getGlobalBool("allowChangeColors", true);
	boolean[STOP_ATTACK_AT_EXIT] = getGlobalBool("stopAttackingAtExit", false);
	boolean[DISABLE_OUTFITS_PRIVILEGED] = getGlobalBool("disableOutfitsForPrivilegedPlayers", false);
	boolean[OLD_CONDITION_ACCURACY] = getGlobalBool("oldConditionAccuracy", false);
	boolean[TRACER_BOX] = getGlobalBool("promptExceptionTracerErrorBox", true);
	boolean[STORE_DIRECTION] = getGlobalBool("storePlayerDirection", false);
	boolean[DISPLAY_LOGGING] = getGlobalBool("displayPlayersLogging", true);
	boolean[STAMINA_BONUS_PREMIUM] = getGlobalBool("staminaThresholdOnlyPremium", true);
	boolean[BAN_UNKNOWN_BYTES] = getGlobalBool("autoBanishUnknownBytes", false);
	boolean[ALLOW_CHANGEADDONS] = getGlobalBool("allowChangeAddons", true);
	boolean[GHOST_INVISIBLE_EFFECT] = getGlobalBool("ghostModeInvisibleEffect", false);
	boolean[SHOW_HEALING_DAMAGE_MONSTER] = getGlobalBool("showHealingDamageForMonsters", false);
	boolean[CHECK_CORPSE_OWNER] = getGlobalBool("checkCorpseOwner ", true);
	boolean[BUFFER_SPELL_FAILURE] = getGlobalBool("bufferMutedOnSpellFailure", false);
	boolean[PREMIUM_SKIP_WAIT] = getGlobalBool("premiumPlayerSkipWaitList", false);
	boolean[DEATH_LIST] = getGlobalBool("deathListEnabled", true);
	boolean[GHOST_SPELL_EFFECTS] = getGlobalBool("ghostModeSpellEffects", true);
	boolean[PVPZONE_ADDMANASPENT] = getGlobalBool("addManaSpentInPvPZone", true);
	boolean[USE_BLACK_SKULL] = getGlobalBool("useBlackSkull", false);
	boolean[USE_FRAG_HANDLER] = getGlobalBool("useFragHandler", true);
	boolean[ALLOW_FIGHTBACK] = getGlobalBool("allowFightback", true);
	boolean[VIPLIST_PER_PLAYER] = getGlobalBool("separateViplistPerCharacter", false);
	boolean[ADDONS_PREMIUM] = getGlobalBool("addonsOnlyPremium", true);
	boolean[DISPLAY_CRITICAL_HIT] = getGlobalBool("displayCriticalHitNotify", false);
	boolean[USE_CAPACITY] = getGlobalBool("useCapSystem", true);
	boolean[SHOW_DESCR] = getGlobalBool("showDescriptionItems", false);
	boolean[REMOVE_BREAK] = getGlobalBool("removeBreakWeaponsCharges", true);
	boolean[SHOW_GAMEMASTERS_ONLINE] = getGlobalBool("displayGamemastersWithOnlineCommand", false);
	boolean[SKIP_ITEMS_VERSION] = getGlobalBool("skipItemsVersionCheck", true);
	boolean[OPTIONAL_WAR_ATTACK_ALLY] = getGlobalBool("optionalWarAttackableAlly", false);
	boolean[EXTERNAL_GUILD_WARS_MANAGEMENT] = getGlobalBool("externalGuildWarsManagement", false);
	boolean[CLASSIC_EQUIPMENT_SLOTS] = getGlobalBool("classicEquipmentSlots", false);
	boolean[EXP_COLOR_RANDOM] = getGlobalBool("randomExperienceColor", false);
	boolean[HEAL_PLAYER_ON_LEVEL] = getGlobalBool("healPlayersOnLevelAdvance", true);
	boolean[ALWAYS_SHOW_MOTD] = getGlobalBool("alwaysShowMessageOfTheDay", false);

	m_loaded = true;
	return true;
}

bool ConfigManager::reload()
{
	if(!m_loaded)
		return false;

	uint32_t tmp = integer[HOUSE_PRICE];
	if(!load())
		return false;

	if((uint32_t)integer[HOUSE_PRICE] == tmp)
		return true;

	for(HouseMap::iterator it = Houses::getInstance()->getHouseBegin();
		it != Houses::getInstance()->getHouseEnd(); ++it)
	{
		uint32_t price = it->second->getTilesCount() * integer[HOUSE_PRICE];
		if(boolean[HOUSE_RENTASPRICE])
		{
			uint32_t rent = it->second->getRent();
			if(!boolean[HOUSE_PRICEASRENT] && it->second->getPrice() != rent)
				price = rent;
		}

		it->second->setPrice(price);
		if(boolean[HOUSE_PRICEASRENT])
			it->second->setRent(price);

		if(!it->second->getOwner())
			it->second->updateDoorDescription();
	}


	return true;
}

const std::string& ConfigManager::getString(uint32_t _what) const
{
	if((m_loaded && _what < LAST_STRING_CONFIG) || _what <= CONFIG_FILE)
		return string[_what];

	if(!m_startup)
		std::clog << "[Warning - ConfigManager::getString] " << _what << std::endl;

	return string[DUMMY_STR];
}

bool ConfigManager::getBool(uint32_t _what) const
{
	if(m_loaded && _what < LAST_BOOL_CONFIG)
		return boolean[_what];

	if(!m_startup)
		std::clog << "[Warning - ConfigManager::getBool] " << _what << std::endl;

	return false;
}

int32_t ConfigManager::getNumber(uint32_t _what) const
{
	if(m_loaded && _what < LAST_INTEGER_CONFIG)
		return integer[_what];

	if(!m_startup)
		std::clog << "[Warning - ConfigManager::getNumber] " << _what << std::endl;

	return 0;
}

double ConfigManager::getDouble(uint32_t _what) const
{
	if(m_loaded && _what < LAST_DOUBLE_CONFIG)
		return m_confDouble[_what];

	if(!m_startup)
		std::clog << "[Warning - ConfigManager::getDouble] " << _what << std::endl;

	return 0;
}

bool ConfigManager::setString(uint32_t _what, const std::string& _value)
{
	if(_what < LAST_STRING_CONFIG)
	{
		string[_what] = _value;
		return true;
	}

	std::clog << "[Warning - ConfigManager::setString] " << _what << std::endl;
	return false;
}

bool ConfigManager::setNumber(uint32_t _what, int32_t _value)
{
	if(_what < LAST_INTEGER_CONFIG)
	{
		integer[_what] = _value;
		return true;
	}

	std::clog << "[Warning - ConfigManager::setNumber] " << _what << std::endl;
	return false;
}

bool ConfigManager::setBool(uint32_t _what, bool _value)
{
	if(_what < LAST_BOOL_CONFIG)
	{
		boolean[_what] = _value;
		return true;
	}

	std::clog << "[Warning - ConfigManager::setBool] " << _what << std::endl;
	return false;
}
