function onUse(cid, item, fromPosition, itemEx, toPosition)
	stonePosition = {x = 256, y = 830, z = 7, stackpos = 1}
	getStonePosition = getThingfromPos(stonePosition)
	stoneUniqueID = 6505
	itemToRemove = 1354
	effectRemove = CONST_ME_SMOKE
	effectCreate = CONST_ME_MAGIC_BLUE

	if item.uid == stoneUniqueID and item.itemid == 1945 and getStonePosition.itemid == itemToRemove then
		doRemoveItem(getStonePosition.uid, 1)
		doTransformItem(item.uid, item.itemid + 1)
		doSendMagicEffect(stonePosition, effectRemove)
	elseif item.uid == stoneUniqueID and item.itemid == 1946 then
		doCreateItem(itemToRemove, 1, stonePosition)
		doTransformItem(item.uid, item.itemid - 1)
		doSendMagicEffect(stonePosition, effectCreate)
	end
	return true
end