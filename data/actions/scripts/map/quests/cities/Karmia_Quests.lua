local t = {
	[5014] = {5014, "a bright sword", 2407, 1},
	[5019] = {5019, "a serpent sword", 2409, 1},
	[5021] = {5021, "a halberd", 2381, 1},
	[5022] = {5022, "an amazon shield", 2537, 1},
	[5023] = {5023, "a broad sword", 2413, 1},
	[5025] = {5025, "a noble armor", 2486, 1},
	[5026] = {5026, "a tower shield", 2528, 1},
	[5029] = {5029, "a snakebit rod", 2182, 1},
	[5030] = {5030, "a wand of vortex", 2190, 1},
	[5031] = {5031, "platinum coins", 2152, 50},
	[5067] = {5067, "the black knight key quest", 2088, 2},
	[5068] = {5068, "plate armor", 5068, 1},
	[5069] = {5069, "a brass legs", 2478, 1}
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
