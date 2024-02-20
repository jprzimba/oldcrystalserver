function onSay(cid, words, param, channel)
    local effectID = tonumber(param)

    if not effectID or effectID < 0 or effectID > CONST_ME_LAST then
        doPlayerSendCancel(cid, "Numeric param may not be lower than 0 and higher than " .. CONST_ME_LAST .. ".")
        return true
    end

    doSendMagicEffect(getCreaturePosition(cid), effectID)
    return true
end
