local t = {
	[5032] = {5032, "a blue robe", 2656, 1},
	[5033] = {5033, "a medusa shield", 2536, 1},
	[5034] = {5034, "a crystal mace", 2445, 1},
	[5035] = {5035, "a dragon lance", 2414, 1},
	[5036] = {5036, "a knight legs", 2477, 1},
	[5037] = {5037, "platinum coins", 2152, 100},
	[5038] = {5038, "a ring of healing", 2214, 1},
	[5039] = {5039, "a piece of ancient hemet", 2339, 1},
	[5040] = {5040, "a piece of ancient hemet", 2337, 1},
	[5041] = {5041, "a piece of ancient hemet", 2336, 1},
	[5042] = {5042, "a piece of ancient hemet", 2335, 1},
	[5043] = {5043, "an amazon armor", 2500, 1},
	[5044] = {5044, "an amazon helmet", 2499, 1},
	[5073] = {5073, "a piece of ancient hemet", 2340, 1},
	[5074] = {5074, "a piece of ancient hemet", 2341, 1}
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
