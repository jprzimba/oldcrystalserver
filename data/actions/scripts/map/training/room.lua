-- Dont change ids if you dont change it in map edito
local ACTION_IDS = {
	NORTH = 2017,
	SOUTH = 2018,
	WEST = 2019,
	EAST = 2020
}

local emptyRoom = true -- dont change it

function onUse(cid, item, fromPosition, itemEx, toPosition)
	currentCharPosition = getPlayerPosition(cid)
	if (item.actionid == ACTION_IDS.NORTH) then
		if (currentCharPosition.y < fromPosition.y) then
			othersidePos = {x = fromPosition.x, y = fromPosition.y + 1, z = fromPosition.z}
		else
			othersidePos = {x = fromPosition.x, y = fromPosition.y - 1, z = fromPosition.z, stackpos = STACKPOS_TOP_CREATURE}
			things = getThingfromPos(othersidePos)
			if (things.itemid == 1) then
				if (getPlayerLevel(things.uid) > 0) then
					emptyRoom = false
				end
			end
		end
	elseif (item.actionid == ACTION_IDS.SOUTH) then
		if (currentCharPosition.y > fromPosition.y) then
			othersidePos = {x=fromPosition.x, y=fromPosition.y-1, z=fromPosition.z}
		else
			othersidePos = {x = fromPosition.x, y = fromPosition.y + 1, z = fromPosition.z, stackpos = STACKPOS_TOP_CREATURE}
			things = getThingfromPos(othersidePos)
			if (things.itemid == 1) then
				if (getPlayerLevel(things.uid) > 0) then
					emptyRoom = false
				end
			end
		end
	elseif (item.actionid == ACTION_IDS.EAST) then
		if (currentCharPosition.x > fromPosition.x) then
			othersidePos = {x = fromPosition.x - 1, y = fromPosition.y, z = fromPosition.z}
		else
			othersidePos = {x = fromPosition.x + 1, y = fromPosition.y, z = fromPosition.z, stackpos = STACKPOS_TOP_CREATURE}
			things = getThingfromPos(othersidePos)
			if (things.itemid == 1) then
				if (getPlayerLevel(things.uid) > 0) then
					emptyRoom = false
				end
			end
		end
	elseif (item.actionid == ACTION_IDS.WEST) then
		if (currentCharPosition.x < fromPosition.x) then
			othersidePos = {x = fromPosition.x + 1, y = fromPosition.y, z = fromPosition.z}
		else
			othersidePos = {x = fromPosition.x - 1, y = fromPosition.y, z = fromPosition.z, stackpos= STACKPOS_TOP_CREATURE}
			things = getThingfromPos(othersidePos)
			if (things.itemid == 1) then
				if (getPlayerLevel(things.uid) > 0) then
					emptyRoom = false
				end
			end
		end
	end

	if (emptyRoom == true) then
		doTeleportThing(cid, othersidePos)
		doSendMagicEffect(othersidePos, CONST_ME_TELEPORT)
	else
		doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "The room is full, please try another room.")
	end

	return true
end