local shutdownEvent = 0

function onSay(cid, words, param, channel)
    if param == '' then
        doSetGameState(GAMESTATE_SHUTDOWN)
        return true
    end

    local lowerParam = param:lower()

    if isInArray({"cancel", "stop"}, lowerParam) then
        stopEvent(shutdownEvent)
        shutdownEvent = 0
        return true
    elseif lowerParam == "kill" then
        os.exit()
        return true
    end

    local minutes = tonumber(param)

    if not minutes or minutes < 0 then
        doPlayerSendCancel(cid, "Numeric param may not be lower than 0.")
        return true
    end

    if shutdownEvent ~= 0 then
        stopEvent(shutdownEvent)
    end

    return prepareShutdown(math.abs(math.ceil(minutes)))
end

function prepareShutdown(minutes)
    if minutes <= 0 then
        doSetGameState(GAMESTATE_SHUTDOWN)
        return false
    end

    local message = "Server is going down in " .. minutes .. " " .. (minutes == 1 and "minute" or "minutes")

    if minutes <= 3 then
        doBroadcastMessage(message .. ", please log out.")
    else
        doBroadcastMessage(message .. ".")
    end

    shutdownEvent = addEvent(prepareShutdown, 60000, minutes - 1)
    return true
end
