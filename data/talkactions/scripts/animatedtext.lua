function onSay(cid, words, param, channel)
    if param == '' then
        doPlayerSendTextMessage(cid, MESSAGE_STATUS_CONSOLE_BLUE, "Command param required.")
        return true
    end

    local params = string.explode(param, " ", 2)
    local color = tonumber(params[1])

    if color and color > 0 and color < 256 then
        local text = params[2] or ""
        doSendAnimatedText(getCreaturePosition(cid), text, color)
    else
        doPlayerSendTextMessage(cid, MESSAGE_STATUS_CONSOLE_BLUE, "Typed color has to be between 0 and 256")
    end

    return true
end
