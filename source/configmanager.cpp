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

	m_integer[ENCRYPTION] = ENCRYPTION_SHA1;
	m_string[CONFIG_FILE] = getFilePath(FILE_TYPE_CONFIG, "config.lua");

	m_integer[LOGIN_PORT] = m_integer[GAME_PORT] = m_integer[STATUS_PORT] = 0;
	m_string[DATA_DIRECTORY] = m_string[LOGS_DIRECTORY] = m_string[IP_STRING] = m_string[RUNFILE] = m_string[OUTPUT_LOG] = m_string[ENCRYPTION_KEY] = "";
	m_boolean[LOGIN_ONLY_LOGINSERVER] = m_boolean[START_CLOSED] = false;
	m_boolean[SCRIPT_SYSTEM] = true;
}

bool ConfigManager::load()
{
	if (L)
		lua_close(L);

	L = luaL_newstate();
	if (!L)
		return false;

	luaL_openlibs(L);
	if (luaL_dofile(L, m_string[CONFIG_FILE].c_str()))
	{
		lua_close(L);
		L = NULL;
		return false;
	}

	if (!m_loaded) //info that must be loaded one time (unless we reset the modules involved)
	{
		if (m_string[DATA_DIRECTORY] == "")
			m_string[DATA_DIRECTORY] = getGlobalString("dataDirectory", "data/");

		if (m_string[LOGS_DIRECTORY] == "")
			m_string[LOGS_DIRECTORY] = getGlobalString("logsDirectory", "logs/");

		if (m_string[IP_STRING] == "")
			m_string[IP_STRING] = getGlobalString("ip", "127.0.0.1");

		if (m_string[RUNFILE] == "")
			m_string[RUNFILE] = getGlobalString("runFile", "");

		if (m_string[OUTPUT_LOG] == "")
			m_string[OUTPUT_LOG] = getGlobalString("outputLog", "");

		if (m_integer[LOGIN_PORT] == 0)
			m_integer[LOGIN_PORT] = getGlobalNumber("loginPort", 7171);

		if (m_integer[GAME_PORT] == 0)
			m_integer[GAME_PORT] = getGlobalNumber("gamePort", 7172);

		if (m_integer[STATUS_PORT] == 0)
			m_integer[STATUS_PORT] = getGlobalNumber("statusPort", 7171);

		#ifdef MULTI_SQL_DRIVERS
		m_string[SQL_TYPE] = getGlobalString("sqlType", "sqlite");
		#endif
		m_string[SQL_HOST] = getGlobalString("sqlHost", "localhost");
		m_string[SQL_DB] = getGlobalString("sqlDatabase", "crystalserver");
		m_string[SQL_USER] = getGlobalString("sqlUser", "root");
		m_string[SQL_PASS] = getGlobalString("sqlPass", "");
		m_string[SQL_FILE] = getGlobalString("sqlFile", "crystalserver.s3db");
		m_string[MAP_NAME] = getGlobalString("mapName", "DnSend");
		m_string[HOUSE_RENT_PERIOD] = getGlobalString("houseRentPeriod", "monthly");
		m_string[ENCRYPTION_TYPE] = getGlobalString("encryptionType", "sha1");
		m_string[RSA_PRIME1] = getGlobalString("rsaPrime1", "14299623962416399520070177382898895550795403345466153217470516082934737582776038882967213386204600674145392845853859217990626450972452084065728686565928113");
		m_string[RSA_PRIME2] = getGlobalString("rsaPrime2", "7630979195970404721891201847792002125535401292779123937207447574596692788513647179235335529307251350570728407373705564708871762033017096809910315212884101");
		m_string[RSA_PUBLIC] = getGlobalString("rsaPublic", "65537");
		m_string[RSA_MODULUS] = getGlobalString("rsaModulus", "109120132967399429278860960508995541528237502902798129123468757937266291492576446330739696001110603907230888610072655818825358503429057592827629436413108566029093628212635953836686562675849720620786279431090218017681061521755056710823876476444260558147179707119674283982419152118103759076030616683978566631413");
		m_string[RSA_PRIVATE] = getGlobalString("rsaPrivate", "46730330223584118622160180015036832148732986808519344675210555262940258739805766860224610646919605860206328024326703361630109888417839241959507572247284807035235569619173792292786907845791904955103601652822519121908367187885509270025388641700821735345222087940578381210879116823013776808975766851829020659073");
		m_string[DEFAULT_PRIORITY] = getGlobalString("defaultPriority", "high");

		m_integer[GLOBALSAVE_H] = getGlobalNumber("globalSaveHour", 8);
		m_integer[GLOBALSAVE_M] = getGlobalNumber("globalSaveMinute", 0);
		m_integer[AUTO_SAVE_EACH_MINUTES] = getGlobalNumber("autoSaveEachMinutes", 0);
		m_integer[SQL_PORT] = getGlobalNumber("sqlPort", 3306);
		m_integer[SQL_KEEPALIVE] = getGlobalNumber("sqlKeepAlive", 0);
		m_integer[MYSQL_READ_TIMEOUT] = getGlobalNumber("mysqlReadTimeout", 10);
		m_integer[MYSQL_WRITE_TIMEOUT] = getGlobalNumber("mysqlWriteTimeout", 10);
		m_integer[WORLD_ID] = getGlobalNumber("worldId", 0);

		#ifndef __LOGIN_SERVER__
		m_boolean[LOGIN_ONLY_LOGINSERVER] = getGlobalBool("loginOnlyWithLoginServer", false);
		#endif
		m_boolean[GLOBALSAVE_ENABLED] = getGlobalBool("globalSaveEnabled", true);
		m_boolean[TRUNCATE_LOGS] = getGlobalBool("truncateLogsOnStartup", true);
		m_boolean[OPTIMIZE_DATABASE] = getGlobalBool("optimizeDatabaseAtStartup", true);
		m_boolean[RANDOMIZE_TILES] = getGlobalBool("randomizeTiles", true);
		m_boolean[STORE_TRASH] = getGlobalBool("storeTrash", true);
		m_boolean[EXPERIENCE_STAGES] = getGlobalBool("experienceStages", false);
		m_boolean[GUILD_HALLS] = getGlobalBool("guildHalls", false);
		m_boolean[BIND_ONLY_GLOBAL_ADDRESS] = getGlobalBool("bindOnlyGlobalAddress", false);
	}

	m_string[MAP_AUTHOR] = getGlobalString("mapAuthor", "Unknown");
	m_string[SERVER_NAME] = getGlobalString("serverName");
	m_string[OWNER_NAME] = getGlobalString("ownerName");
	m_string[OWNER_EMAIL] = getGlobalString("ownerEmail");
	m_string[URL] = getGlobalString("url");
	m_string[LOCATION] = getGlobalString("location");
	m_string[MOTD] = getGlobalString("motd");
	m_string[WORLD_TYPE] = getGlobalString("worldType", "open");
	m_string[HOUSE_STORAGE] = getGlobalString("houseDataStorage", "binary");
	m_string[PREFIX_CHANNEL_LOGS] = getGlobalString("prefixChannelLogs", "");
	m_string[CORES_USED] = getGlobalString("coresUsed", "-1");
	m_string[MAILBOX_DISABLED_TOWNS] = getGlobalString("mailboxDisabledTowns", "-1");

	m_integer[LOGIN_TRIES] = getGlobalNumber("loginTries", 3);
	m_integer[RETRY_TIMEOUT] = getGlobalNumber("retryTimeout", 30 * 1000);
	m_integer[LOGIN_TIMEOUT] = getGlobalNumber("loginTimeout", 5 * 1000);
	m_integer[MAX_MESSAGEBUFFER] = getGlobalNumber("maxMessageBuffer", 4);
	m_integer[MAX_PLAYERS] = getGlobalNumber("maxPlayers");
	m_integer[DEFAULT_DESPAWNRANGE] = getGlobalNumber("deSpawnRange", 2);
	m_integer[DEFAULT_DESPAWNRADIUS] = getGlobalNumber("deSpawnRadius", 50);
	m_integer[PZ_LOCKED] = getGlobalNumber("pzLocked", 60 * 1000);
	m_integer[HUNTING_DURATION] = getGlobalNumber("huntingDuration", 60 * 1000);
	m_integer[ALLOW_CLONES] = getGlobalNumber("allowClones", 0);
	m_integer[RATE_SPAWN_MIN] = getGlobalNumber("rateSpawnMin", 1);
	m_integer[RATE_SPAWN_MAX] = getGlobalNumber("rateSpawnMax", 1);
	m_integer[PARTY_RADIUS_X] = getGlobalNumber("experienceShareRadiusX", 30);
	m_integer[PARTY_RADIUS_Y] = getGlobalNumber("experienceShareRadiusY", 30);
	m_integer[PARTY_RADIUS_Z] = getGlobalNumber("experienceShareRadiusZ", 1);
	m_integer[SPAWNPOS_X] = getGlobalNumber("newPlayerSpawnPosX", 100);
	m_integer[SPAWNPOS_Y] = getGlobalNumber("newPlayerSpawnPosY", 100);
	m_integer[SPAWNPOS_Z] = getGlobalNumber("newPlayerSpawnPosZ", 7);
	m_integer[SPAWNTOWN_ID] = getGlobalNumber("newPlayerTownId", 1);
	m_integer[START_LEVEL] = getGlobalNumber("newPlayerLevel", 1);
	m_integer[START_MAGICLEVEL] = getGlobalNumber("newPlayerMagicLevel", 0);
	m_integer[HOUSE_PRICE] = getGlobalNumber("housePriceEachSquare", 1000);
	m_integer[WHITE_SKULL_TIME] = getGlobalNumber("whiteSkullTime", 15 * 60 * 1000);
	m_integer[HIGHSCORES_TOP] = getGlobalNumber("highscoreDisplayPlayers", 10);
	m_integer[HIGHSCORES_UPDATETIME] = getGlobalNumber("updateHighscoresAfterMinutes", 60);
	m_integer[ACTIONS_DELAY_INTERVAL] = getGlobalNumber("timeBetweenActions", 200);
	m_integer[EX_ACTIONS_DELAY_INTERVAL] = getGlobalNumber("timeBetweenExActions", 1000);
	m_integer[CUSTOM_ACTIONS_DELAY_INTERVAL] = getGlobalNumber("timeBetweenCustomActions", 500);
	m_integer[PROTECTION_LEVEL] = getGlobalNumber("protectionLevel", 1);
	m_integer[STATUSQUERY_TIMEOUT] = getGlobalNumber("statusTimeout", 5 * 60 * 1000);
	m_integer[LEVEL_TO_FORM_GUILD] = getGlobalNumber("levelToFormGuild", 8);
	m_integer[MIN_GUILDNAME] = getGlobalNumber("minGuildNameLength", 4);
	m_integer[MAX_GUILDNAME] = getGlobalNumber("maxGuildNameLength", 20);
	m_integer[LEVEL_TO_BUY_HOUSE] = getGlobalNumber("levelToBuyHouse", 1);
	m_integer[HOUSES_PER_ACCOUNT] = getGlobalNumber("housesPerAccount", 0);
	m_integer[FIELD_OWNERSHIP] = getGlobalNumber("fieldOwnershipDuration", 5 * 1000);
	m_integer[RED_SKULL_LENGTH] = getGlobalNumber("redSkullLength", 30 * 24 * 60 * 60);
	m_integer[BLACK_SKULL_LENGTH] = getGlobalNumber("blackSkullLength", 45 * 24 * 60 * 60);
	m_integer[MAX_VIOLATIONCOMMENT_SIZE] = getGlobalNumber("maxViolationCommentSize", 60);
	m_integer[NOTATIONS_TO_BAN] = getGlobalNumber("notationsToBan", 3);
	m_integer[WARNINGS_TO_FINALBAN] = getGlobalNumber("warningsToFinalBan", 4);
	m_integer[WARNINGS_TO_DELETION] = getGlobalNumber("warningsToDeletion", 5);
	m_integer[BAN_LENGTH] = getGlobalNumber("banLength", 7 * 24 * 60 * 60);
	m_integer[KILLS_BAN_LENGTH] = getGlobalNumber("killsBanLength", 7 * 24 * 60 * 60);
	m_integer[FINALBAN_LENGTH] = getGlobalNumber("finalBanLength", 30 * 24 * 60 * 60);
	m_integer[IPBANISHMENT_LENGTH] = getGlobalNumber("ipBanishmentLength", 1 * 24 * 60 * 60);
	m_integer[MAX_PLAYER_SUMMONS] = getGlobalNumber("maxPlayerSummons", 2);
	m_integer[EXTRA_PARTY_PERCENT] = getGlobalNumber("extraPartyExperiencePercent", 5);
	m_integer[EXTRA_PARTY_LIMIT] = getGlobalNumber("extraPartyExperienceLimit", 20);
	m_integer[LOGIN_PROTECTION] = getGlobalNumber("loginProtectionPeriod", 10 * 1000);
	m_integer[PLAYER_DEEPNESS] = getGlobalNumber("playerQueryDeepness", 1);
	m_integer[STAIRHOP_DELAY] = getGlobalNumber("stairhopDelay", 2 * 1000);
	m_integer[RATE_STAMINA_LOSS] = getGlobalNumber("rateStaminaLoss", 1);
	m_integer[STAMINA_LIMIT_TOP] = getGlobalNumber("staminaRatingLimitTop", 41 * 60);
	m_integer[STAMINA_LIMIT_BOTTOM] = getGlobalNumber("staminaRatingLimitBottom", 14 * 60);
	m_integer[BLESS_REDUCTION_BASE] = getGlobalNumber("blessingReductionBase", 30);
	m_integer[BLESS_REDUCTION_DECREAMENT] = getGlobalNumber("blessingReductionDecreament", 5);
	m_integer[BLESS_REDUCTION] = getGlobalNumber("eachBlessReduction", 8);
	m_integer[NICE_LEVEL] = getGlobalNumber("niceLevel", 5);
	m_integer[EXPERIENCE_COLOR] = getGlobalNumber("gainExperienceColor", COLOR_WHITE);
	m_integer[GUILD_PREMIUM_DAYS] = getGlobalNumber("premiumDaysToFormGuild", 0);
	m_integer[PUSH_CREATURE_DELAY] = getGlobalNumber("pushCreatureDelay", 2 * 1000);
	m_integer[DEATH_CONTAINER] = getGlobalNumber("deathContainerId", 1987);
	m_integer[MAXIMUM_DOOR_LEVEL] = getGlobalNumber("maximumDoorLevel", 500);
	m_integer[DEATH_ASSISTS] = getGlobalNumber("deathAssistCount", 1);
	m_integer[RED_DAILY_LIMIT] = getGlobalNumber("dailyFragsToRedSkull", 3);
	m_integer[RED_WEEKLY_LIMIT] = getGlobalNumber("weeklyFragsToRedSkull", 5);
	m_integer[RED_MONTHLY_LIMIT] = getGlobalNumber("monthlyFragsToRedSkull", 10);
	m_integer[BLACK_DAILY_LIMIT] = getGlobalNumber("dailyFragsToBlackSkull", m_integer[RED_DAILY_LIMIT]);
	m_integer[BLACK_WEEKLY_LIMIT] = getGlobalNumber("weeklyFragsToBlackSkull", m_integer[RED_WEEKLY_LIMIT]);
	m_integer[BLACK_MONTHLY_LIMIT] = getGlobalNumber("monthlyFragsToBlackSkull", m_integer[RED_MONTHLY_LIMIT]);
	m_integer[BAN_DAILY_LIMIT] = getGlobalNumber("dailyFragsToBanishment", m_integer[RED_DAILY_LIMIT]);
	m_integer[BAN_WEEKLY_LIMIT] = getGlobalNumber("weeklyFragsToBanishment", m_integer[RED_WEEKLY_LIMIT]);
	m_integer[BAN_MONTHLY_LIMIT] = getGlobalNumber("monthlyFragsToBanishment", m_integer[RED_MONTHLY_LIMIT]);
	m_integer[BLACK_SKULL_DEATH_HEALTH] = getGlobalNumber("blackSkulledDeathHealth", 40);
	m_integer[BLACK_SKULL_DEATH_MANA] = getGlobalNumber("blackSkulledDeathMana", 0);
	m_integer[DEATHLIST_REQUIRED_TIME] = getGlobalNumber("deathListRequiredTime", 1 * 60 * 1000);
	m_integer[EXPERIENCE_SHARE_ACTIVITY] = getGlobalNumber("experienceShareActivity", 2 * 60 * 1000);
	m_integer[TILE_LIMIT] = getGlobalNumber("tileLimit", 0);
	m_integer[PROTECTION_TILE_LIMIT] = getGlobalNumber("protectionTileLimit", 0);
	m_integer[HOUSE_TILE_LIMIT] = getGlobalNumber("houseTileLimit", 0);
	m_integer[SQUARE_COLOR] = getGlobalNumber("squareColor", 0);
	m_integer[LOOT_MESSAGE] = getGlobalNumber("monsterLootMessage", 3);
	m_integer[LOOT_MESSAGE_TYPE] = getGlobalNumber("monsterLootMessageType", 25);
	m_integer[NAME_REPORT_TYPE] = getGlobalNumber("violationNameReportActionType", 2);
	m_integer[HOUSE_CLEAN_OLD] = getGlobalNumber("houseCleanOld", 0);
	m_integer[MANAGER_PASS_LENGTH] = getGlobalNumber("minPasswordLength", 6);
	m_integer[MANAGER_ACCNAME_MIN_LENGTH] = getGlobalNumber("minAccountNameLength", 3);
	m_integer[MANAGER_ACCNAME_MAX_LENGTH] = getGlobalNumber("maxAccountNameLength", 25);
	m_integer[MANAGER_MIN_PLAYER_NAME_LENGTH] = getGlobalNumber("minNewCharacterNameLength", 3);
	m_integer[MANAGER_MAX_PLAYER_NAME_LENGTH] = getGlobalNumber("maxNewCharacterNameLength", 25);
	m_integer[MANAGER_LOOKHEAD] = getGlobalNumber("newCharacterLookHead", 10);
	m_integer[MANAGER_LOOKBODY] = getGlobalNumber("newCharacterLookBody", 20);
	m_integer[MANAGER_LOOKLEGS] = getGlobalNumber("newCharacterLookLegs", 30);
	m_integer[MANAGER_LOOKFEET] = getGlobalNumber("newCharacterLookFeet", 40);
	m_integer[CRITICAL_HIT_CHANCE] = getGlobalNumber("criticalHitChance", 5);
	m_integer[CRITICAL_COLOR] = getGlobalNumber("criticalHitColor", COLOR_TEAL);
	m_integer[MIN_GUILD_NICK] = getGlobalNumber("minGuildNickLength", 2);
	m_integer[MAX_GUILD_NICK] = getGlobalNumber("maxGuildNickLength", 25);
	m_integer[STAMINA_DESTROY_LOOT] = getGlobalNumber("staminaLootLimit", 14 * 60);
	m_integer[VIPLIST_DEFAULT_LIMIT] = getGlobalNumber("vipListDefaultLimit", 20);
	m_integer[VIPLIST_DEFAULT_PREMIUM_LIMIT] = getGlobalNumber("vipListDefaultPremiumLimit", 100);
	m_integer[FIST_BASE_ATTACK] = getGlobalNumber("fistBaseAttack", 7);
	m_integer[DEFAULT_DEPOT_SIZE_PREMIUM] = getGlobalNumber("defaultDepotSizePremium", 2000);
	m_integer[DEFAULT_DEPOT_SIZE] = getGlobalNumber("defaultDepotSize", 2000);
	m_integer[SURPRISEBAG_PERCENT] = getGlobalNumber("surpriseBagPercent", 1);
	m_integer[CHRISTMAS_PERCENT] = getGlobalNumber("christmasDecorationPercent", 50);
	m_integer[ROOK_TOWN]	= getGlobalNumber("rookTownId", 1);
	m_integer[ROOK_LEVELTO] = getGlobalNumber("rookLevelToGetRooked", 5);
	m_integer[ROOK_TOLEVEL] = getGlobalNumber("rookLevelToLeaveRook", 8);
	m_integer[MAIL_ATTEMPTS] = getGlobalNumber("mailMaxAttempts", 20);
	m_integer[MAIL_BLOCK] = getGlobalNumber("mailBlockPeriod", 3600000);
	m_integer[MAIL_ATTEMPTS_FADE] = getGlobalNumber("mailAttemptsFadeTime", 600000);

	m_double[RATE_EXPERIENCE] = getGlobalDouble("rateExperience", 1);
	m_double[RATE_SKILL] = getGlobalDouble("rateSkill", 1);
	m_double[RATE_MAGIC] = getGlobalDouble("rateMagic", 1);
	m_double[RATE_LOOT] = getGlobalDouble("rateLoot", 1);
	m_double[PARTY_DIFFERENCE] = getGlobalDouble("experienceShareLevelDifference", (double)2 / 3);
	m_double[RATE_PVP_EXPERIENCE] = getGlobalDouble("rateExperienceFromPlayers", 0);
	m_double[EFP_MIN_THRESHOLD] = getGlobalDouble("minLevelThresholdForKilledPlayer", 0.9f);
	m_double[EFP_MAX_THRESHOLD] = getGlobalDouble("maxLevelThresholdForKilledPlayer", 1.1f);
	m_double[RATE_STAMINA_GAIN] = getGlobalDouble("rateStaminaGain", 3);
	m_double[RATE_STAMINA_THRESHOLD] = getGlobalDouble("rateStaminaThresholdGain", 12);
	m_double[RATE_STAMINA_ABOVE] = getGlobalDouble("rateStaminaAboveNormal", 1.5f);
	m_double[RATE_STAMINA_UNDER] = getGlobalDouble("rateStaminaUnderNormal", 0.5f);
	m_double[FORMULA_LEVEL] = getGlobalDouble("formulaLevel", 5.0);
	m_double[FORMULA_MAGIC] = getGlobalDouble("formulaMagic", 1.0);
	m_double[RATE_MONSTER_HEALTH] = getGlobalDouble("rateMonsterHealth", 1);
	m_double[RATE_MONSTER_MANA] = getGlobalDouble("rateMonsterMana", 1);
	m_double[RATE_MONSTER_ATTACK] = getGlobalDouble("rateMonsterAttack", 1);
	m_double[RATE_MONSTER_DEFENSE] = getGlobalDouble("rateMonsterDefense", 1);
	m_double[CRITICAL_HIT_MUL] = getGlobalDouble("criticalHitMultiplier", 1);

	m_boolean[SAVE_PLAYER_DATA] = getGlobalBool("savePlayerData", true);
	m_boolean[CLOSE_INSTANCE_ON_SHUTDOWN] = getGlobalBool("closeInstanceOnShutdown", true);
	m_boolean[ACCOUNT_MANAGER] = getGlobalBool("accountManager", true);
	m_boolean[NAMELOCK_MANAGER] = getGlobalBool("namelockManager", false);
	m_boolean[START_CHOOSEVOC] = getGlobalBool("newPlayerChooseVoc", false);
	m_boolean[ON_OR_OFF_CHARLIST] = getGlobalBool("displayOnOrOffAtCharlist", false);
	m_boolean[ALLOW_CHANGEOUTFIT] = getGlobalBool("allowChangeOutfit", true);
	m_boolean[ONE_PLAYER_ON_ACCOUNT] = getGlobalBool("onePlayerOnlinePerAccount", true);
	m_boolean[CANNOT_ATTACK_SAME_LOOKFEET] = getGlobalBool("noDamageToSameLookfeet", false);
	m_boolean[AIMBOT_HOTKEY_ENABLED] = getGlobalBool("hotkeyAimbotEnabled", true);
	m_boolean[REMOVE_WEAPON_AMMO] = getGlobalBool("removeWeaponAmmunition", true);
	m_boolean[REMOVE_WEAPON_CHARGES] = getGlobalBool("removeWeaponCharges", true);
	m_boolean[REMOVE_RUNE_CHARGES] = getGlobalBool("removeRuneCharges", true);
	m_boolean[SHUTDOWN_AT_GLOBALSAVE] = getGlobalBool("shutdownAtGlobalSave", false);
	m_boolean[CLEAN_MAP_AT_GLOBALSAVE] = getGlobalBool("cleanMapAtGlobalSave", true);
	m_boolean[FREE_PREMIUM] = getGlobalBool("freePremium", false);
	m_boolean[BROADCAST_BANISHMENTS] = getGlobalBool("broadcastBanishments", true);
	m_boolean[GENERATE_ACCOUNT_NUMBER] = getGlobalBool("generateAccountNumber", true);
	m_boolean[GENERATE_ACCOUNT_SALT] = getGlobalBool("generateAccountSalt", false);
	m_boolean[INGAME_GUILD_MANAGEMENT] = getGlobalBool("ingameGuildManagement", true);
	m_boolean[HOUSE_BUY_AND_SELL] = getGlobalBool("buyableAndSellableHouses", true);
	m_boolean[REPLACE_KICK_ON_LOGIN] = getGlobalBool("replaceKickOnLogin", true);
	m_boolean[HOUSE_NEED_PREMIUM] = getGlobalBool("houseNeedPremium", true);
	m_boolean[HOUSE_RENTASPRICE] = getGlobalBool("houseRentAsPrice", false);
	m_boolean[HOUSE_PRICEASRENT] = getGlobalBool("housePriceAsRent", false);
	m_boolean[BANK_SYSTEM] = getGlobalBool("bankSystem", true);
	m_boolean[PREMIUM_FOR_PROMOTION] = getGlobalBool("premiumForPromotion", true);
	m_boolean[REMOVE_PREMIUM_ON_INIT] = getGlobalBool("removePremiumOnInit", true);
	m_boolean[SHOW_HEALING_DAMAGE] = getGlobalBool("showHealingDamage", false);
	m_boolean[TELEPORT_SUMMONS] = getGlobalBool("teleportAllSummons", false);
	m_boolean[TELEPORT_PLAYER_SUMMONS] = getGlobalBool("teleportPlayerSummons", false);
	m_boolean[PVP_TILE_IGNORE_PROTECTION] = getGlobalBool("pvpTileIgnoreLevelAndVocationProtection", true);
	m_boolean[CLEAN_PROTECTED_ZONES] = getGlobalBool("cleanProtectedZones", true);
	m_boolean[SPELL_NAME_INSTEAD_WORDS] = getGlobalBool("spellNameInsteadOfWords", false);
	m_boolean[EMOTE_SPELLS] = getGlobalBool("emoteSpells", false);
	m_boolean[UNIFIED_SPELLS] = getGlobalBool("unifiedSpells", true);
	m_boolean[SAVE_GLOBAL_STORAGE] = getGlobalBool("saveGlobalStorage", true);
	m_boolean[FORCE_CLOSE_SLOW_CONNECTION] = getGlobalBool("forceSlowConnectionsToDisconnect", false);
	m_boolean[BLESSING_ONLY_PREMIUM] = getGlobalBool("blessingOnlyPremium", true);
	m_boolean[BED_REQUIRE_PREMIUM] = getGlobalBool("bedsRequirePremium", true);
	m_boolean[ALLOW_CHANGECOLORS] = getGlobalBool("allowChangeColors", true);
	m_boolean[STOP_ATTACK_AT_EXIT] = getGlobalBool("stopAttackingAtExit", false);
	m_boolean[DISABLE_OUTFITS_PRIVILEGED] = getGlobalBool("disableOutfitsForPrivilegedPlayers", false);
	m_boolean[OLD_CONDITION_ACCURACY] = getGlobalBool("oldConditionAccuracy", false);
	m_boolean[TRACER_BOX] = getGlobalBool("promptExceptionTracerErrorBox", true);
	m_boolean[STORE_DIRECTION] = getGlobalBool("storePlayerDirection", false);
	m_boolean[DISPLAY_LOGGING] = getGlobalBool("displayPlayersLogging", true);
	m_boolean[STAMINA_BONUS_PREMIUM] = getGlobalBool("staminaThresholdOnlyPremium", true);
	m_boolean[ALLOW_CHANGEADDONS] = getGlobalBool("allowChangeAddons", true);
	m_boolean[GHOST_INVISIBLE_EFFECT] = getGlobalBool("ghostModeInvisibleEffect", false);
	m_boolean[SHOW_HEALING_DAMAGE_MONSTER] = getGlobalBool("showHealingDamageForMonsters", false);
	m_boolean[CHECK_CORPSE_OWNER] = getGlobalBool("checkCorpseOwner ", true);
	m_boolean[BUFFER_SPELL_FAILURE] = getGlobalBool("bufferMutedOnSpellFailure", false);
	m_boolean[PREMIUM_SKIP_WAIT] = getGlobalBool("premiumPlayerSkipWaitList", false);
	m_boolean[DEATH_LIST] = getGlobalBool("deathListEnabled", true);
	m_boolean[GHOST_SPELL_EFFECTS] = getGlobalBool("ghostModeSpellEffects", true);
	m_boolean[PVPZONE_ADDMANASPENT] = getGlobalBool("addManaSpentInPvPZone", true);
	m_boolean[USE_BLACK_SKULL] = getGlobalBool("useBlackSkull", false);
	m_boolean[USE_FRAG_HANDLER] = getGlobalBool("useFragHandler", true);
	m_boolean[ALLOW_FIGHTBACK] = getGlobalBool("allowFightback", true);
	m_boolean[VIPLIST_PER_PLAYER] = getGlobalBool("separateViplistPerCharacter", false);
	m_boolean[ADDONS_PREMIUM] = getGlobalBool("addonsOnlyPremium", true);
	m_boolean[DISPLAY_CRITICAL_HIT] = getGlobalBool("displayCriticalHitNotify", false);
	m_boolean[USE_CAPACITY] = getGlobalBool("useCapSystem", true);
	m_boolean[REMOVE_BREAK] = getGlobalBool("removeBreakWeaponsCharges", true);
	m_boolean[SHOW_GAMEMASTERS_ONLINE] = getGlobalBool("displayGamemastersWithOnlineCommand", false);
	m_boolean[SKIP_ITEMS_VERSION] = getGlobalBool("skipItemsVersionCheck", true);
	m_boolean[OPTIONAL_WAR_ATTACK_ALLY] = getGlobalBool("optionalWarAttackableAlly", false);
	m_boolean[EXTERNAL_GUILD_WARS_MANAGEMENT] = getGlobalBool("externalGuildWarsManagement", false);
	m_boolean[CLASSIC_EQUIPMENT_SLOTS] = getGlobalBool("classicEquipmentSlots", false);
	m_boolean[EXP_COLOR_RANDOM] = getGlobalBool("randomExperienceColor", false);
	m_boolean[ALWAYS_SHOW_MOTD] = getGlobalBool("alwaysShowMessageOfTheDay", false);
	m_boolean[PVPZONE_RECOVERMANA] = getGlobalBool("recoverManaAfterDeathInPvPZone", false);
	m_boolean[ALLOW_BLOCK_SPAWN] = getGlobalBool("allowBlockSpawn", false);
	m_boolean[SURPRISE_BAGS] = getGlobalBool("dropSurpriseBagsFromMonsters", false);
	m_boolean[CHRISTMAS_DECO] = getGlobalBool("useChristmasDecoration", false);
	m_boolean[HOUSE_SKIP_INIT_RENT] = getGlobalBool("houseSkipInitialRent", true);
	m_boolean[ROOK_SYSTEM]	= getGlobalBool("useRookSystem", false);
	m_boolean[HOUSE_PROTECTION] = getGlobalBool("houseProtection", true);

	m_loaded = true;
	return true;
}

bool ConfigManager::reload()
{
	if (!m_loaded)
		return false;

	uint32_t tmp = m_integer[HOUSE_PRICE];
	if (!load())
		return false;

	if ((uint32_t)m_integer[HOUSE_PRICE] == tmp)
		return true;

	for (HouseMap::iterator it = Houses::getInstance()->getHouseBegin();
		it != Houses::getInstance()->getHouseEnd(); ++it)
	{
		uint32_t price = it->second->getTilesCount() * m_integer[HOUSE_PRICE];
		if (m_boolean[HOUSE_RENTASPRICE])
		{
			uint32_t rent = it->second->getRent();
			if (!m_boolean[HOUSE_PRICEASRENT] && it->second->getPrice() != rent)
				price = rent;
		}

		it->second->setPrice(price);
		if (m_boolean[HOUSE_PRICEASRENT])
			it->second->setRent(price);

		if (!it->second->getOwner())
			it->second->updateDoorDescription();
	}

	return true;
}

const std::string& ConfigManager::getString(uint32_t _what) const
{
	if ((m_loaded && _what < LAST_STRING_CONFIG) || _what <= CONFIG_FILE)
		return m_string[_what];

	if (!m_startup)
		std::clog << "[Warning - ConfigManager::getString] " << _what << std::endl;

	return m_string[DUMMY_STR];
}

bool ConfigManager::getBool(uint32_t _what) const
{
	if (m_loaded && _what < LAST_BOOL_CONFIG)
		return m_boolean[_what];

	if (!m_startup)
		std::clog << "[Warning - ConfigManager::getBool] " << _what << std::endl;

	return false;
}

int32_t ConfigManager::getNumber(uint32_t _what) const
{
	if (m_loaded && _what < LAST_INTEGER_CONFIG)
		return m_integer[_what];

	if (!m_startup)
		std::clog << "[Warning - ConfigManager::getNumber] " << _what << std::endl;

	return 0;
}

double ConfigManager::getDouble(uint32_t _what) const
{
	if (m_loaded && _what < LAST_DOUBLE_CONFIG)
		return m_double[_what];

	if (!m_startup)
		std::clog << "[Warning - ConfigManager::getDouble] " << _what << std::endl;

	return 0;
}

bool ConfigManager::setString(uint32_t _what, const std::string& _value)
{
	if (_what < LAST_STRING_CONFIG)
	{
		m_string[_what] = _value;
		return true;
	}

	std::clog << "[Warning - ConfigManager::setString] " << _what << std::endl;
	return false;
}

bool ConfigManager::setNumber(uint32_t _what, int32_t _value)
{
	if (_what < LAST_INTEGER_CONFIG)
	{
		m_integer[_what] = _value;
		return true;
	}

	std::clog << "[Warning - ConfigManager::setNumber] " << _what << std::endl;
	return false;
}

bool ConfigManager::setBool(uint32_t _what, bool _value)
{
	if (_what < LAST_BOOL_CONFIG)
	{
		m_boolean[_what] = _value;
		return true;
	}

	std::clog << "[Warning - ConfigManager::setBool] " << _what << std::endl;
	return false;
}
