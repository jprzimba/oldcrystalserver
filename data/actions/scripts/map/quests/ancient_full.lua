function onUse(cid, item, fromPosition, itemEx, toPosition)
	piece1pos = {x = 299, y = 439, z = 8, stackpos = 1}
	piece2pos = {x = 299, y = 440, z = 8, stackpos = 1}
	helmetpos = {x = 299, y = 439, z = 8, stackpos = 1}

	getpiece1 = getThingfromPos(piece1pos)
	getpiece2 = getThingfromPos(piece2pos)

	if item.uid == 6667 and item.itemid == 1945 and getpiece1.itemid == 2342 and getpiece2.itemid == 2147 then
		doRemoveItem(getpiece1.uid, 1)
		doRemoveItem(getpiece2.uid, 1)
		doCreateItem(2343, 1, helmetpos)
		doTransformItem(item.uid, item.itemid + 1)
	elseif item.uid == 6667 and item.itemid == 1946 then
		doTransformItem(item.uid, item.itemid - 1)
	else
		doPlayerSendDefaultCancel(cid, RETURNVALUE_NOTPOSSIBLE)
	end
	return true
end