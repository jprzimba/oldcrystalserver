function onUse(cid, item, fromPosition, itemEx, toPosition)
	wall1 = {x = 1496, y = 1488, z = 5, stackpos = 1}
	wall2 = {x = 1497, y = 1488, z = 5, stackpos = 1}
	getwall1 = getThingfromPos(wall1)
	getwall2 = getThingfromPos(wall2)

	if item.uid == 7002 and item.itemid == 1945 then
		doRemoveItem(getwall1.uid, 1)
		doRemoveItem(getwall2.uid, 1)
		doTransformItem(item.uid, item.itemid + 1)
	elseif item.uid == 7002 and item.itemid == 1946 then
		doCreateItem(1052, 1, wall1)
		doCreateItem(1052, 1, wall2)
		doTransformItem(item.uid, item.itemid - 1)		
	else
		doPlayerSendDefaultCancel(cid, RETURNVALUE_NOTPOSSIBLE)
	end

	return true
end