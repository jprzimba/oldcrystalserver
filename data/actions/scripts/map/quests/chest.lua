function onUse(cid, item, fromPosition, itemEx, toPosition)
-- Tiquanda
   	if item.uid == 5066 then
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

--- Folda

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


	end
   	return true
   end
