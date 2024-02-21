-- Don't change IDs if you don't change it in map editor
local ACTION_IDS = {
    NORTH = 2017,
    SOUTH = 2018,
    WEST = 2019,
    EAST = 2020
}

function onUse(cid, item, fromPosition, itemEx, toPosition)
    local emptyRoom = true
    local currentCharPosition = getPlayerPosition(cid)
    local othersidePos = {}

    if item.actionid == ACTION_IDS.NORTH then
        othersidePos = currentCharPosition.y < fromPosition.y and {x = fromPosition.x, y = fromPosition.y + 1, z = fromPosition.z}
                                                         or {x = fromPosition.x, y = fromPosition.y - 1, z = fromPosition.z, stackpos = STACKPOS_TOP_CREATURE}
    elseif item.actionid == ACTION_IDS.SOUTH then
        othersidePos = currentCharPosition.y > fromPosition.y and {x = fromPosition.x, y = fromPosition.y - 1, z = fromPosition.z}
                                                         or {x = fromPosition.x, y = fromPosition.y + 1, z = fromPosition.z, stackpos = STACKPOS_TOP_CREATURE}
    elseif item.actionid == ACTION_IDS.EAST then
        othersidePos = currentCharPosition.x > fromPosition.x and {x = fromPosition.x - 1, y = fromPosition.y, z = fromPosition.z}
                                                         or {x = fromPosition.x + 1, y = fromPosition.y, z = fromPosition.z, stackpos = STACKPOS_TOP_CREATURE}
    elseif item.actionid == ACTION_IDS.WEST then
        othersidePos = currentCharPosition.x < fromPosition.x and {x = fromPosition.x + 1, y = fromPosition.y, z = fromPosition.z}
                                                         or {x = fromPosition.x - 1, y = fromPosition.y, z = fromPosition.z, stackpos = STACKPOS_TOP_CREATURE}
    end

    if othersidePos.x and othersidePos.y then
        local things = getThingfromPos(othersidePos)
        if things.itemid == 1 and getPlayerLevel(things.uid) > 0 then
            emptyRoom = false
        end
    end

    if emptyRoom then
        doTeleportThing(cid, othersidePos)
        doSendMagicEffect(othersidePos, CONST_ME_TELEPORT)
    else
        doPlayerSendTextMessage(cid, MESSAGE_INFO_DESCR, "The room is full, please try another room.")
    end

    return true
end
