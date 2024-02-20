function onSay(cid, words, param, channel)
    local animationID = tonumber(param)

    if not animationID or animationID < 0 or animationID > CONST_ANI_LAST then
        doPlayerSendCancel(cid, "Numeric param may not be lower than 0 and higher than " .. CONST_ANI_LAST .. ".")
        return true
    end

    local position = getCreaturePosition(cid)

    for i = 1, 30 do
        local targetPosition = {
            x = position.x + math.random(-7, 7),
            y = position.y + math.random(-5, 5),
            z = position.z
        }

        doSendDistanceShoot(position, targetPosition, animationID)
    end

    return true
end
