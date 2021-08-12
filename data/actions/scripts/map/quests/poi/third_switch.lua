function onUse(cid, item, fromPosition, itemEx, toPosition)
	firePosition = {x = 245, y = 830, z = 7, stackpos = 1}
	getFirePosition = getThingfromPos(firePosition)
	fireUniqueID = 6502
	itemToRemove = 6289
	effectRemove = CONST_ME_SMOKE
	effectCreate = CONST_ME_MAGIC_BLUE

	if item.uid == fireUniqueID and item.itemid == 1945 and getFirePosition.itemid == itemToRemove then
		doRemoveItem(getFirePosition.uid, 1)
		doTransformItem(item.uid, item.itemid + 1)
		doSendMagicEffect(firePosition, effectRemove)
	elseif item.uid == fireUniqueID and item.itemid == 1946 then
		doCreateItem(itemToRemove, 1, firePosition)
		doTransformItem(item.uid, item.itemid - 1)
		doSendMagicEffect(firePosition, effectCreate)
	end
	return true
end