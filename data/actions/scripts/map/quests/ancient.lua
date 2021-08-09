function onUse(cid, item, fromPosition, itemEx, toPosition)
	piece1pos = {x = 300, y = 443, z = 8, stackpos = 1}
	piece2pos = {x = 301, y = 443, z = 8, stackpos = 1}
	piece3pos = {x = 302, y = 443, z = 8, stackpos = 1}
	piece4pos = {x = 303, y = 443, z = 8, stackpos = 1}
	piece5pos = {x = 304, y = 443, z = 8, stackpos = 1}
	piece6pos = {x = 305, y = 443, z = 8, stackpos = 1}
	piece7pos = {x = 306, y = 443, z = 8, stackpos = 1}
	helmetpos = {x = 303, y = 441, z = 8, stackpos = 1}
	getpiece1 = getThingfromPos(piece1pos)
	getpiece2 = getThingfromPos(piece2pos)
	getpiece3 = getThingfromPos(piece3pos)
	getpiece4 = getThingfromPos(piece4pos)
	getpiece5 = getThingfromPos(piece5pos)
	getpiece6 = getThingfromPos(piece6pos)
	getpiece7 = getThingfromPos(piece7pos)

	if item.uid == 6666 and item.itemid == 1945 and getpiece1.itemid == 2336 and getpiece2.itemid == 2337 and getpiece3.itemid == 2335 and getpiece4.itemid == 2339 and getpiece5.itemid == 2340 and getpiece6.itemid == 2338 and getpiece7.itemid == 2341 then
		doRemoveItem(getpiece1.uid, 1)
		doRemoveItem(getpiece2.uid, 1)
		doRemoveItem(getpiece3.uid, 1)
		doRemoveItem(getpiece4.uid, 1)
		doRemoveItem(getpiece5.uid, 1)
		doRemoveItem(getpiece6.uid, 1)
		doRemoveItem(getpiece7.uid, 1)
		doCreateItem(2342, 1, helmetpos)
		doTransformItem(item.uid, item.itemid + 1)
	elseif item.uid == 6666 and item.itemid == 1946 then
		doTransformItem(item.uid, item.itemid - 1)
	else
		doPlayerSendDefaultCancel(cid, RETURNVALUE_NOTPOSSIBLE)
	end
	return true
end