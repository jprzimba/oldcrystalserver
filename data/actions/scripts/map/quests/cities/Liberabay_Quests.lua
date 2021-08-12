local t = {
	[5084] = {5084, "a dark shield", 2521, 1},
	[5086] = {5086, "a dragon scale mail", 2492, 1},
	[5087] = {5087, "a tortoise shield", 6131, 1}
}

function onUse(cid, item, fromPosition, itemEx, toPosition)
	local v = t[item.uid]
	if getPlayerStorageValue(cid,v[1]) == -1 and getPlayerFreeCap(cid) >= (getItemWeightById(v[3])) then
		setPlayerStorageValue(cid, v[1], 1)
		doPlayerAddItem(cid, v[3], v[4])
		doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found " .. v[2] .. ".")
	elseif getPlayerStorageValue(cid, v[1]) == 1 then
		doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
	elseif getPlayerFreeCap(cid) < (getItemWeightById(v[3])) then
		doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You need " .. getItemWeightById(v[3]) .. ".00 oz in order to get the item.")
	end

	return true
end
