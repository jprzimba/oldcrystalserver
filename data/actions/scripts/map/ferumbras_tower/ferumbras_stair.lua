function onUse(cid, item, fromPosition, itemEx, toPosition)
	gatepos = {x = 643, y = 542, z = 8, stackpos = 1}
	getgate = getThingfromPos(gatepos)

	if item.uid == 5169 and item.itemid == 1945 and getgate.itemid == 0 then
		doCreateItem(1385, 1, gatepos)
		doTransformItem(item.uid, item.itemid + 1)
	elseif item.uid == 5169 and item.itemid == 1946 and getgate.itemid == 1385 then
		doRemoveItem(getgate.uid, 1)
		doTransformItem(item.uid, item.itemid - 1)
	else
		doPlayerSendDefaultCancel(cid, RETURNVALUE_NOTPOSSIBLE)
	end
	return true
end