local config = {
    broadcast = false
}

function onSay(cid, words, param, channel)
    if param == '' then
        doPlayerSendTextMessage(cid, MESSAGE_STATUS_CONSOLE_BLUE, "Command param required.")
        return true
    end

    local targetPlayer = getPlayerByNameWildcard(param)

    if not targetPlayer then
        doPlayerSendTextMessage(cid, MESSAGE_STATUS_CONSOLE_BLUE, "Player " .. param .. " not found.")
        return true
    end

    if getPlayerAccess(targetPlayer) >= getPlayerAccess(cid) then
        doPlayerSendTextMessage(cid, MESSAGE_STATUS_CONSOLE_BLUE, "Cannot perform action.")
        return true
    end

    local direction = 1
    if words:sub(2, 2) == "d" then
        direction = -1
    end

    local newGroupId = getPlayerGroupId(targetPlayer) + direction

    if newGroupId <= 0 or not setPlayerGroupId(targetPlayer, newGroupId) then
        doPlayerSendTextMessage(cid, MESSAGE_STATUS_CONSOLE_BLUE, "Cannot perform action.")
        return true
    end

    local groupName = getGroupInfo(newGroupId).name
    local actionType = (direction == 1) and "promoted" or "demoted"
    local actionMessage = param .. " has been " .. actionType .. " to " .. groupName .. "."

    if not config.broadcast then
        doPlayerSendTextMessage(cid, MESSAGE_STATUS_CONSOLE_BLUE, actionMessage)
    else
        doBroadcastMessage(actionMessage, MESSAGE_EVENT_ADVANCE)
    end

    doPlayerSendTextMessage(targetPlayer, MESSAGE_EVENT_ADVANCE, "You have " .. actionMessage)
    return true
end
