function onUse(cid, item, fromPosition, itemEx, toPosition)
	scarabpos = {x = 649, y = 615, z = 10, stackpos = STACKPOS_TOP_MOVEABLE_ITEM_OR_CREATURE} 
	scarab = getThingfromPos(scarabpos) 

	telepos = {x = 607, y = 649, z = 10, stackpos = 1} 
	beforepos = getPlayerPosition(cid) 

	effect1pos = {x = 649, y = 616, z = 10, stackpos = 1} 

	if scarab.itemid == 5954 and beforepos.x == 649 and beforepos.y == 616 and beforepos.z == 10 then 
		doTeleportThing(cid, telepos) 
		doSendMagicEffect(effect1pos, CONST_ME_MAGIC_BLUE) 
		doSendMagicEffect(telepos, CONST_ME_ENERGYAREA) 
		doSendMagicEffect(scarabpos, CONST_ME_POFF) 
		doRemoveItem(scarab.uid, 1) 
	else 
		doPlayerSendCancel(cid, "You need to stay in the fire.") 
	end 

	if item.itemid == 1485 then 
		doPlayerSendCancel(cid, "Put Demon Horn on coal basin.") 
	end 

	return true
end