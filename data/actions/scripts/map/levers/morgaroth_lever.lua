function onUse(cid, item, fromPosition, itemEx, toPosition)
	gatepos = {x = 638, y = 591, z = 10, stackpos = 1}
	getgate = getThingfromPos(gatepos)

	if item.uid == 7009 and item.itemid == 1945 and getgate.itemid == 387 then
		doRemoveItem(getgate.uid, 1)
		doTransformItem(item.uid, item.itemid + 1)
	elseif item.uid == 7009 and item.itemid == 1946 and getgate.itemid == 0 then
		doCreateItem(381, 1, gatepos)
		doTransformItem(item.uid, item.itemid - 1)
	else
		doPlayerSendDefaultCancel(cid, RETURNVALUE_NOTPOSSIBLE)
	end
	return true
end