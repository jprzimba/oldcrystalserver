function onUse(cid, item, fromPosition, itemEx, toPosition)
-- Behemoth Quest
   	if item.uid == 5010 then
		queststatus = getPlayerStorageValue(cid, 5010)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Golden Armor.")
   			doPlayerAddItem(cid, 2466, 1)
   			setPlayerStorageValue(cid, 5010, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 5012 then
   		queststatus = getPlayerStorageValue(cid, 5012)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Guardian Halberd.")
   			doPlayerAddItem(cid, 2427, 1)
   			setPlayerStorageValue(cid, 5012, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 5013 then
   		queststatus = getPlayerStorageValue(cid,5013)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a platinum amulet.")
   			doPlayerAddItem(cid,2171,1)
   			setPlayerStorageValue(cid, 5013, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
-- Demon Helmet
   	elseif item.uid == 5049 then
   		queststatus = getPlayerStorageValue(cid,5049)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Demon Helmet.")
   			doPlayerAddItem(cid, 2493, 1)
   			setPlayerStorageValue(cid, 5049, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 5050 then
   		queststatus = getPlayerStorageValue(cid,5050)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Steel Boots.")
   			doPlayerAddItem(cid, 2645, 1)
   			setPlayerStorageValue(cid, 5050,1 )
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 5051 then
   		queststatus = getPlayerStorageValue(cid, 5051)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Demon Shield.")
   			doPlayerAddItem(cid, 2520, 1)
   			setPlayerStorageValue(cid, 5051, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
--  Karmia Quests
   	elseif item.uid == 5014 then
   		queststatus = getPlayerStorageValue(cid, 5014)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Bright Sword.")
   			doPlayerAddItem(cid, 2407, 1)
   			setPlayerStorageValue(cid, 5014, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end

	elseif item.uid == 5069 then
   		queststatus = getPlayerStorageValue(cid, 5069)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Brass Legs.")
   			doPlayerAddItem(cid, 2478, 1)
   			setPlayerStorageValue(cid, 5069, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end

   	elseif item.uid == 5019 then
   		queststatus = getPlayerStorageValue(cid, 5019)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Serpent Sword.")
   			doPlayerAddItem(cid, 2409, 1)
   			setPlayerStorageValue(cid, 5019, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 5021 then
   		queststatus = getPlayerStorageValue(cid, 5021)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Halberd.")
   			doPlayerAddItem(cid, 2381, 1)
   			setPlayerStorageValue(cid, 5021, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 5022 then
   		queststatus = getPlayerStorageValue(cid, 5022)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found an Amazon Shield.")
   			doPlayerAddItem(cid, 2537, 1)
   			setPlayerStorageValue(cid, 5022, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 5023 then
   		queststatus = getPlayerStorageValue(cid, 5023)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Broad Sword.")
   			doPlayerAddItem(cid, 2413, 1)
   			setPlayerStorageValue(cid, 5023, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 5025 then
   		queststatus = getPlayerStorageValue(cid, 5025)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Noble Armor.")
   			doPlayerAddItem(cid, 2486, 1)
   			setPlayerStorageValue(cid, 5025, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 5026 then
   		queststatus = getPlayerStorageValue(cid, 5026)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Tower Shield.")
   			doPlayerAddItem(cid, 2528, 1)
   			setPlayerStorageValue(cid, 5026, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 5029 then
   		queststatus = getPlayerStorageValue(cid, 5029)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Snakebite Rod.")
   			doPlayerAddItem(cid, 2182, 1)
   			setPlayerStorageValue(cid, 5029, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 5067 then
   		queststatus = getPlayerStorageValue(cid, 5067)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Key.\nUse it in Black Knight Quest!")
   			doPlayerAddItem(cid, 2088, 1)
   			setPlayerStorageValue(cid, 5067, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end

   	elseif item.uid == 5068 then
   		queststatus = getPlayerStorageValue(cid, 5068)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Plate armor.")
   			doPlayerAddItem(cid, 2463, 2)
   			setPlayerStorageValue(cid, 5068, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
-- Desert City
   	elseif item.uid == 5032 then
   		queststatus = getPlayerStorageValue(cid, 5032)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Blue Robe.")
   			doPlayerAddItem(cid, 2656, 2)
   			setPlayerStorageValue(cid, 5032, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 5033 then
   		queststatus = getPlayerStorageValue(cid, 5033)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Medusa Shield.")
   			doPlayerAddItem(cid, 2536, 2)
   			setPlayerStorageValue(cid, 5033, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 5034 then
   		queststatus = getPlayerStorageValue(cid, 5034)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Crystal Mace.")
   			doPlayerAddItem(cid, 2445, 1)
   			setPlayerStorageValue(cid, 5034, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 5035 then
   		queststatus = getPlayerStorageValue(cid, 5035)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Dragon Lance.")
   			doPlayerAddItem(cid, 2414, 1)
   			setPlayerStorageValue(cid, 5035, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 5036 then
   		queststatus = getPlayerStorageValue(cid, 5036)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Knight Legs.")
   			doPlayerAddItem(cid, 2477, 1)
   			setPlayerStorageValue(cid, 5036, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 5037 then
   		queststatus = getPlayerStorageValue(cid, 5037)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a 100 platinum coins.")
   			doPlayerAddItem(cid, 2152, 100)
   			setPlayerStorageValue(cid, 5037, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 5038 then
   		queststatus = getPlayerStorageValue(cid, 5038)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Rinf of Healing.")
   			doPlayerAddItem(cid, 2214, 1)
   			setPlayerStorageValue(cid, 5038, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 5039 then
   		queststatus = getPlayerStorageValue(cid, 5039)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Piece of Ancient Helmet.")
   			doPlayerAddItem(cid, 2339, 1)
   			setPlayerStorageValue(cid, 5039, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 5040 then
   		queststatus = getPlayerStorageValue(cid, 5040)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Piece of Ancient Helmet.")
   			doPlayerAddItem(cid, 2337, 1)
   			setPlayerStorageValue(cid, 5040, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 5041 then
   		queststatus = getPlayerStorageValue(cid, 5041)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Piece of Ancient Helmet.")
   			doPlayerAddItem(cid, 2336, 1)
   			setPlayerStorageValue(cid, 5041, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
	elseif item.uid == 5073 then
   		queststatus = getPlayerStorageValue(cid, 5073)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Piece of Ancient Helmet.")
   			doPlayerAddItem(cid, 2340, 1)
   			setPlayerStorageValue(cid, 5073, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
	elseif item.uid == 5074 then
   		queststatus = getPlayerStorageValue(cid, 5074)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Piece of Ancient Helmet.")
   			doPlayerAddItem(cid, 2341, 1)
   			setPlayerStorageValue(cid, 5074, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 5042 then
   		queststatus = getPlayerStorageValue(cid, 5042)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Piece of Ancient Helmet.")
   			doPlayerAddItem(cid, 2335, 1)
   			setPlayerStorageValue(cid, 5042, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 5043 then
   		queststatus = getPlayerStorageValue(cid, 5043)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Amazon Armor.")
   			doPlayerAddItem(cid, 2500, 1)
   			setPlayerStorageValue(cid, 5043, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 5044 then
   		queststatus = getPlayerStorageValue(cid, 5044)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Amazon Helmet.")
   			doPlayerAddItem(cid, 2499, 1)
   			setPlayerStorageValue(cid, 5044, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
-- Inferna
	elseif item.uid == 5015 then
   		queststatus = getPlayerStorageValue(cid, 5015)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Knight Armor.")
   			doPlayerAddItem(cid, 2476, 1)
   			setPlayerStorageValue(cid, 5015, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
	elseif item.uid == 5016 then
   		queststatus = getPlayerStorageValue(cid, 5016)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Fire Sword.")
   			doPlayerAddItem(cid, 2392, 1)
   			setPlayerStorageValue(cid, 5016, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
	elseif item.uid == 5017 then
   		queststatus = getPlayerStorageValue(cid, 5017)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Beholder Shield.")
   			doPlayerAddItem(cid, 2518, 1)
   			setPlayerStorageValue(cid, 5017, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
	elseif item.uid == 5018 then
   		queststatus = getPlayerStorageValue(cid, 5018)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Warrior Helmet.")
   			doPlayerAddItem(cid, 2475, 1)
   			setPlayerStorageValue(cid, 5018, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
-- Premmy Island
   	elseif item.uid == 5045 then
   		queststatus = getPlayerStorageValue(cid, 5045)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a knight Axe.")
   			doPlayerAddItem(cid, 2430, 1)
   			setPlayerStorageValue(cid, 5045, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 5046 then
   		queststatus = getPlayerStorageValue(cid, 5046)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Fire Axe.")
   			doPlayerAddItem(cid, 2432, 1)
   			setPlayerStorageValue(cid, 5046, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 5047 then
   		queststatus = getPlayerStorageValue(cid, 5047)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Vampire Shield.")
   			doPlayerAddItem(cid, 2534, 1)
   			setPlayerStorageValue(cid, 5047, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 5048 then
   		queststatus = getPlayerStorageValue(cid, 5048)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Dragon Lance.")
   			doPlayerAddItem(cid, 2414, 1)
   			setPlayerStorageValue(cid, 5048, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 5058 then
   		queststatus = getPlayerStorageValue(cid, 5058)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Piece of Ancient Helmet.")
   			doPlayerAddItem(cid, 2338, 1)
   			setPlayerStorageValue(cid, 5058, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 5059 then
   		queststatus = getPlayerStorageValue(cid, 5059)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Black Shield.")
   			doPlayerAddItem(cid, 2529, 1)
   			setPlayerStorageValue(cid, 5059, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 5060 then
   		queststatus = getPlayerStorageValue(cid, 5060)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Winged Helmet.")
   			doPlayerAddItem(cid, 2474, 1)
   			setPlayerStorageValue(cid, 5060, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
-- Tiquanda
   	elseif item.uid == 5052 then
   		queststatus = getPlayerStorageValue(cid, 5052)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Dwarven Axe.")
   			doPlayerAddItem(cid, 2435, 1)
   			setPlayerStorageValue(cid, 5052, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 5053 then
   		queststatus = getPlayerStorageValue(cid, 5053)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Boots of Haste.")
   			doPlayerAddItem(cid, 2195, 1)
   			setPlayerStorageValue(cid, 5053, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 5054 then
   		queststatus = getPlayerStorageValue(cid, 5054)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Royal Helmet.")
   			doPlayerAddItem(cid, 2498, 1)
   			setPlayerStorageValue(cid, 5054, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 5055 then
   		queststatus = getPlayerStorageValue(cid, 5055)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Barbarian Axe.")
   			doPlayerAddItem(cid, 2429, 1)
   			setPlayerStorageValue(cid, 5055, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 5056 then
   		queststatus = getPlayerStorageValue(cid, 5056)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Post Officers Hat.")
   			doPlayerAddItem(cid, 2665, 1)
   			setPlayerStorageValue(cid, 5056, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 5057 then
   		queststatus = getPlayerStorageValue(cid, 5057)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Shield of Honor.")
   			doPlayerAddItem(cid, 2517, 1)
   			setPlayerStorageValue(cid, 5057, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 5066 then
		queststatus = getPlayerStorageValue(cid, 5066)
		if queststatus == -1 then
  			container = doPlayerAddItem(cid, 1991, 1)
			doContainerAddItem(container, 2187, 1)
			doContainerAddItem(container, 2160, 1)
			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a bag.")
			setPlayerStorageValue(cid, 5066, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
-- Venore
	elseif item.uid == 5076 then
   		queststatus = getPlayerStorageValue(cid, 5076)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Crown Armor.")
   			doPlayerAddItem(cid, 2487, 1)
   			setPlayerStorageValue(cid, 5076, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
	elseif item.uid == 5077 then
   		queststatus = getPlayerStorageValue(cid, 5077)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Crown Legs.")
   			doPlayerAddItem(cid, 2488, 1)
   			setPlayerStorageValue(cid, 5077, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 5063 then
   		queststatus = getPlayerStorageValue(cid, 5063)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Dragon Hammer.")
   			doPlayerAddItem(cid, 2434, 1)
   			setPlayerStorageValue(cid, 5063, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 5064 then
   		queststatus = getPlayerStorageValue(cid, 5064)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Blue Robe.")
   			doPlayerAddItem(cid, 2656, 1)
   			setPlayerStorageValue(cid, 5064, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 5065 then
   		queststatus = getPlayerStorageValue(cid, 5065)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Giant Sword.")
   			doPlayerAddItem(cid, 2393, 1)
   			setPlayerStorageValue(cid, 5065, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 5080 then
   		queststatus = getPlayerStorageValue(cid, 5080)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Doll.")
   			doPlayerAddItem(cid, 2110, 1)
   			setPlayerStorageValue(cid, 5080, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
-- Folda
   	elseif item.uid == 5081 then
		queststatus = getPlayerStorageValue(cid,  5081)
		if queststatus == -1 then
  			container = doPlayerAddItem(cid,  1987, 1)
			doContainerAddItem(container, 2148,42)
			doContainerAddItem(container, 2580, 1)
			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a bag.")
			setPlayerStorageValue(cid, 5081, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 5082 then
   		queststatus = getPlayerStorageValue(cid, 5082)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Book.")
   			doPlayerAddItem(cid, 2217, 1)
   			setPlayerStorageValue(cid, 5082, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 5083 then
   		queststatus = getPlayerStorageValue(cid, 5083)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Crusader helmet.")
   			doPlayerAddItem(cid, 2497, 1)
   			setPlayerStorageValue(cid, 5083, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
-- Liberty Bay
   	elseif item.uid == 5084 then
   		queststatus = getPlayerStorageValue(cid, 5084)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Dark Shield.")
   			doPlayerAddItem(cid, 2521, 1)
   			setPlayerStorageValue(cid, 5084, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end 
   	elseif item.uid == 5086 then
   		queststatus = getPlayerStorageValue(cid, 5086)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Dragon Scale Armor.")
   			doPlayerAddItem(cid, 2492, 1)
   			setPlayerStorageValue(cid, 5086, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 5087 then
   		queststatus = getPlayerStorageValue(cid, 5087)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Tortoise Shield.")
   			doPlayerAddItem(cid, 6131, 1)
   			setPlayerStorageValue(cid, 5087, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end 
-- Others
   	elseif item.uid == 6000 then
   		queststatus = getPlayerStorageValue(cid, 6000)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Two Handed Sword.")
   			doPlayerAddItem(cid, 2377, 1)
   			setPlayerStorageValue(cid, 6000, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 6001 then
   		queststatus = getPlayerStorageValue(cid, 6001)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Battle Axe.")
   			doPlayerAddItem(cid, 2378, 1)
   			setPlayerStorageValue(cid, 6001, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 6002 then
   		queststatus = getPlayerStorageValue(cid, 6002)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Spyke Sword.")
   			doPlayerAddItem(cid, 2377, 1)
   			setPlayerStorageValue(cid, 6002, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 6003 then
   		queststatus = getPlayerStorageValue(cid, 6003)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Giant Sword.")
   			doPlayerAddItem(cid, 2393, 1)
   			setPlayerStorageValue(cid, 6003, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 6004 then
   		queststatus = getPlayerStorageValue(cid, 6004)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found an Obsidian Lance.")
   			doPlayerAddItem(cid, 2425, 1)
   			setPlayerStorageValue(cid, 6004, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 6005 then
   		queststatus = getPlayerStorageValue(cid, 6005)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found an Epee.")
   			doPlayerAddItem(cid, 2377, 1)
   			setPlayerStorageValue(cid, 6005, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 6006 then
   		queststatus = getPlayerStorageValue(cid, 6006)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Devil Helmet.")
   			doPlayerAddItem(cid, 2462, 1)
   			setPlayerStorageValue(cid, 6006, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 6007 then
   		queststatus = getPlayerStorageValue(cid, 6007)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Golden Legs.")
   			doPlayerAddItem(cid, 2470, 1)
   			setPlayerStorageValue(cid, 6007, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 6008 then
   		queststatus = getPlayerStorageValue(cid, 6008)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Magic Plate Armor.")
   			doPlayerAddItem(cid, 2472, 1)
   			setPlayerStorageValue(cid, 6008, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 6009 then
   		queststatus = getPlayerStorageValue(cid, 6009)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Crown Helmetr.")
   			doPlayerAddItem(cid, 2491, 1)
   			setPlayerStorageValue(cid, 6009, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 6010 then
   		queststatus = getPlayerStorageValue(cid, 6010)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Crown Armor.")
   			doPlayerAddItem(cid, 2487, 1)
   			setPlayerStorageValue(cid, 6010, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 6011 then
   		queststatus = getPlayerStorageValue(cid, 6011)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Crown Legs.")
   			doPlayerAddItem(cid, 2488, 1)
   			setPlayerStorageValue(cid, 6011, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 6012 then
   		queststatus = getPlayerStorageValue(cid, 6012)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Crown Shield.")
   			doPlayerAddItem(cid, 2519, 1)
   			setPlayerStorageValue(cid, 6012, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 6013 then
   		queststatus = getPlayerStorageValue(cid, 6013)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Dragon Scale Mail.")
   			doPlayerAddItem(cid, 2492, 1)
   			setPlayerStorageValue(cid, 6013, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 6014 then
   		queststatus = getPlayerStorageValue(cid, 6014)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Mastermind Shiled.")
   			doPlayerAddItem(cid, 2514, 1)
   			setPlayerStorageValue(cid, 6014, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 6015 then
   		queststatus = getPlayerStorageValue(cid, 6015)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found an Oranamented Shield.")
   			doPlayerAddItem(cid, 2524, 1)
   			setPlayerStorageValue(cid, 6016, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
   	elseif item.uid == 6016 then
   		queststatus = getPlayerStorageValue(cid, 6016)
   		if queststatus == -1 then
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a Griffin Shield.")
   			doPlayerAddItem(cid, 2533, 1)
   			setPlayerStorageValue(cid, 6016, 1)
   		else
   			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
   		end
	end
   	return true
   end
