function onUse(cid, item, fromPosition, itemEx, toPosition)
	local prize = item.uid
	local count = item.actionid
	if prize > 0 and prize < 9000 then
		local queststatus = getPlayerStorageValue(cid, prize)
		if queststatus == -1 then
			if count > 1 then
				doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, 'You have found '.. count ..' of ' .. getItemNameById(prize) .. '.')
				doPlayerAddItem(cid, prize, count)
				setPlayerStorageValue(cid, prize, 1)
			else
				doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, 'You have found a ' .. getItemNameById(prize) .. '.')
				doPlayerAddItem(cid, prize, 1)
				setPlayerStorageValue(cid, prize, 1)
			end
		else
			doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
		end

		return true
	else
		return false
	end
end
