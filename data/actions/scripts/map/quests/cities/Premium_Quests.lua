local t = {
	[5045] = {5045, "a knight axe", 2430, 1},
	[5046] = {5046, "a fire axe", 2432, 1},
	[5047] = {5047, "a vampire shield", 2534, 1},
	[5048] = {5048, "an obsidian lance", 2425, 1},
	[5058] = {5058, "a piece of ancient helmet", 2338, 1},
	[5059] = {5059, "a black shield", 2529, 1},
	[5060] = {5060, "a winged helmet", 2474, 1},
	[5088] = {5088, "a thunder hammer", 2421, 1}
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
