local t = {
	-- Unique items
	[6506] = {6506, "the avenger", 6528},
	[6507] = {6506, "arcane staff", 2453},
	[6508] = {6506, "arbalest", 5803},

	-- Others
	[6509] = {6509, "frozen starlight", 2361},
	[6510] = {6510, "pair of soft boots", 6132},
	[6511] = {6511, "stuffed dragon", 6566},
	[6512] = {6512, "cerimonial ankh", 6561}
}

function onUse(cid, item, fromPosition, itemEx, toPosition)
	local v = t[item.uid]
	if getPlayerStorageValue(cid,v[1]) == -1 and getPlayerFreeCap(cid) >= (getItemWeightById(v[3])) then
		setPlayerStorageValue(cid, v[1], 1)
		doPlayerAddItem(cid, v[3])
		doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You have found a " .. v[2] .. ".")
	elseif getPlayerStorageValue(cid, v[1]) == 1 then
		doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "It is empty.")
	elseif getPlayerFreeCap(cid) < (getItemWeightById(v[3])) then
		doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "You need " .. getItemWeightById(v[3]) .. ".00 oz in order to get the item")
	end

	return true
end
