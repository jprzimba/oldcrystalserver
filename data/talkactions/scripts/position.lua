local config = {
	access = 3 -- to see other players position
}

function onSay(cid, words, param, channel)
    local player = cid

    if param ~= '' and getPlayerAccess(cid) >= config.access then
        local targetPlayer = getPlayerByNameWildcard(param)

        if not targetPlayer or (isPlayerGhost(targetPlayer) and getPlayerGhostAccess(targetPlayer) > getPlayerGhostAccess(cid)) then
            doPlayerSendTextMessage(cid, MESSAGE_STATUS_CONSOLE_BLUE, "Player " .. param .. " is not currently online.")
            return true
        end

        player = targetPlayer
    end

    local position = getCreaturePosition(player)
    doPlayerSendTextMessage(cid, MESSAGE_STATUS_CONSOLE_BLUE, (player == cid and "Your" or getCreatureName(player)) .. " current position is [X: " .. position.x .. " | Y: " .. position.y .. " | Z: " .. position.z .. "]")
    return true
end