local savingEvent = 0

function onSay(cid, words, param, channel)
    local delayMinutes = tonumber(param)

    if delayMinutes then
        stopEvent(savingEvent)
        save(delayMinutes * 60 * 1000)
    elseif param == '' then
        doSaveServer()
        doPlayerSendTextMessage(cid, MESSAGE_STATUS_CONSOLE_BLUE, "Server saved.")
    else
        local targetPlayer = getPlayerByNameWildcard(param)

        if not targetPlayer or (isPlayerGhost(targetPlayer) and getPlayerGhostAccess(targetPlayer) > getPlayerGhostAccess(cid)) then
            doPlayerSendTextMessage(cid, MESSAGE_STATUS_CONSOLE_BLUE, "Player " .. param .. " not found.")
        else
            doPlayerSave(targetPlayer)
        end
    end

    return true
end

function save(delay)
    doSaveServer()

    if delay > 0 then
        savingEvent = addEvent(save, delay, delay)
    end
end
