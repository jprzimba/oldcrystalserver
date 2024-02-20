local cleanEvent = 0

function onSay(cid, words, param, channel)
    if param == '' then
        local collectedItems = doCleanMap()
        local itemWord = (collectedItems == 1) and "item" or "items"
        doPlayerSendTextMessage(cid, MESSAGE_STATUS_CONSOLE_BLUE, "Collected " .. collectedItems .. " " .. itemWord .. ".")
        return true
    end

    local t = string.explode(param, ",")
    if t[1] == 'tile' then
        local removeLoaded = false
        if t[2] then
            removeLoaded = getBooleanFromString(t[2])
        end

        doCleanTile(getCreaturePosition(cid), removeLoaded)
        return true
    end

    local minutes = tonumber(param)
    if not minutes then
        doPlayerSendCancel(cid, "Command requires numeric param.")
        return true
    end

    stopEvent(cleanEvent)
    prepareClean(minutes, cid)
    return true
end

function prepareClean(minutes, cid)
    if minutes == 0 then
        local collectedItems = doCleanMap()
        local itemWord = (collectedItems == 1) and "item" or "items"
        if isPlayer(cid) then
            doPlayerSendTextMessage(cid, MESSAGE_STATUS_CONSOLE_BLUE, "Cleaned " .. collectedItems .. " " .. itemWord .. ".")
        end

        doBroadcastMessage("Game map cleaned.")
    elseif minutes > 0 then
        local pluralS = (minutes > 1) and "s" or ""
        doBroadcastMessage("Game map cleaning in " .. minutes .. " minute" .. pluralS .. ", please pick up all your items.")
        cleanEvent = addEvent(prepareClean, 60000, minutes - 1, cid)
    end
end
