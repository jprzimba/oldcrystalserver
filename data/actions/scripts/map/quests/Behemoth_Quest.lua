local t = {
	[5010] = {5010, "golden armor", 2466},
	[5011] = {5011, "demon shield", 2520},
	[5012] = {5012, "guargian halberd", 2427},
	[5013] = {5013, "platinum amulet", 2171}
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
