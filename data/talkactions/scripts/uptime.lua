function onSay(cid, words, param, channel)
    local uptimeInSeconds = getWorldUpTime()
    local hours = math.floor(uptimeInSeconds / 3600)
    local minutes = math.ceil((uptimeInSeconds % 3600) / 60)

    if minutes == 60 then
        minutes = 0
        hours = hours + 1
    end

    local uptimeMessage = "Uptime: " .. hours .. " " .. (hours == 1 and "hour" or "hours") .. " and " .. minutes .. " " .. (minutes == 1 and "minute" or "minutes")

    doPlayerSendTextMessage(cid, MESSAGE_STATUS_CONSOLE_BLUE, uptimeMessage)
    return true
end
