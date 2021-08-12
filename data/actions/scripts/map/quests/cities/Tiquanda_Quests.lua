local t = {
	[5052] = {5052, "a dwarven axe", 2435, 1},
	[5053] = {5053, "a boots of haste", 2195, 1},
	[5054] = {5054, "a royal helmet", 2498, 1},
	[5055] = {5055, "a jade hammer", 7422, 1},
	[5056] = {5056, "a nightmare blade", 7418, 1},
	[5057] = {5057, "a reaper's axe", 7420, 1},
	[5066] = {5066, "a surprise", 2160, 10}
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
