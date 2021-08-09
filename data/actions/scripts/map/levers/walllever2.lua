function onUse(cid, item, frompos, item2, topos)
	wall1 = {x = 1496, y = 1488, z = 5, stackpos = 1}
	wall2 = {x = 1497, y = 1488, z = 5, stackpos = 1}
	getwall1 = getThingfromPos(wall1)
	getwall2 = getThingfromPos(wall2)

	if item.uid == 7003 and item.itemid == 1945 then
		doRemoveItem(getwall1.uid, 1)
		doRemoveItem(getwall2.uid, 1)
		doTransformItem(item.uid, item.itemid + 1)
	elseif item.uid == 7003 and item.itemid == 1946 then
		doTransformItem(item.uid, item.itemid - 1)		
	else
		doPlayerSendDefaultCancel(cid, RETURNVALUE_NOTPOSSIBLE)
	end

	return true
end