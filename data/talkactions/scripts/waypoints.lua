function onSay(cid, words, param, channel)
    if param ~= '' then
        doWaypointAddTemporal(param, getCreaturePosition(cid))
        doPlayerSendTextMessage(cid, MESSAGE_STATUS_CONSOLE_BLUE, "Temporal waypoint saved.")
        return true
    end

    local waypointsList = getWaypointList()
    local waypointsStr = ""

    for _, waypoint in ipairs(waypointsList) do
        waypointsStr = waypointsStr .. waypoint.name .. "\n"
    end

    doShowTextDialog(cid, 2160, waypointsStr)
    return true
end
