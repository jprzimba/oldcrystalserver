function onSay(cid, words, param, channel)
    if param == '' then
        doPlayerSendTextMessage(cid, MESSAGE_STATUS_CONSOLE_BLUE, "Command param required.")
        return true
    end

    local targetPlayer = getPlayerByNameWildcard(param)

    if not targetPlayer or (isPlayerGhost(targetPlayer) and getPlayerGhostAccess(targetPlayer) > getPlayerGhostAccess(cid)) then
        doPlayerSendTextMessage(cid, MESSAGE_STATUS_CONSOLE_BLUE, "Player " .. param .. " not found.")
        return true
    end

    local targetPos = getCreaturePosition(targetPlayer)
    local targetVocation = getVocationInfo(getPlayerVocation(targetPlayer))

    local playerSkills = {
        fist = getPlayerSkillLevel(targetPlayer, SKILL_FIST),
        club = getPlayerSkillLevel(targetPlayer, SKILL_CLUB),
        sword = getPlayerSkillLevel(targetPlayer, SKILL_SWORD),
        axe = getPlayerSkillLevel(targetPlayer, SKILL_AXE),
        distance = getPlayerSkillLevel(targetPlayer, SKILL_DISTANCE),
        shielding = getPlayerSkillLevel(targetPlayer, SKILL_SHIELD),
        fishing = getPlayerSkillLevel(targetPlayer, SKILL_FISHING)
    }

    local playerCash = {
        crystal = getPlayerItemCount(targetPlayer, 2160),
        platinum = getPlayerItemCount(targetPlayer, 2152),
        gold = getPlayerItemCount(targetPlayer, 2148)
    }

    doPlayerPopupFYI(cid, "Information about player" ..
        "\nName: " .. getCreatureName(targetPlayer) ..
        "\nGUID: " .. getPlayerGUID(targetPlayer) ..
        "\nGroup: " .. getPlayerGroupName(targetPlayer) ..
        "\nAccess: " .. getPlayerAccess(targetPlayer) ..
        "\nVocation: " .. targetVocation.name ..
        "\n\nStatus:" ..
        "\nLevel - " .. getPlayerLevel(targetPlayer) .. ", Magic Level - " .. getPlayerMagLevel(targetPlayer) .. ", Speed - " .. getCreatureSpeed(targetPlayer) ..
        "\nHealth - " .. getCreatureHealth(targetPlayer) .. " / " .. getCreatureMaxHealth(targetPlayer) .. ", Mana - " .. getCreatureMana(targetPlayer) .. " / " .. getCreatureMaxMana(targetPlayer) ..
        "\n\nSkills:" ..
        "\nFist - " .. playerSkills.fist .. ", Club - " .. playerSkills.club .. ", Sword - " .. playerSkills.sword .. ", Axe - " .. playerSkills.axe ..
        "\nDistance - " .. playerSkills.distance .. ", Shielding - " .. playerSkills.shielding .. ", Fishing - " .. playerSkills.fishing ..
        "\n\nCash:" ..
        "\nCrystal - " .. playerCash.crystal .. ", Platinum - " .. playerCash.platinum .. ", Gold - " .. playerCash.gold ..
        "\nBalance: " .. getPlayerBalance(targetPlayer) ..
        "\n\nPosition: [X - " .. targetPos.x .. " | Y - " .. targetPos.y .. " | Z - " .. targetPos.z .. "]" ..
        "\n\nInformation about account" ..
        "\nName: " .. getPlayerAccount(targetPlayer) ..
        "\nID: " .. getPlayerAccountId(targetPlayer) ..
        "\nNotations: " .. getNotationsCount(getPlayerAccountId(targetPlayer)) ..
        "\nIP: " .. doConvertIntegerToIp(getPlayerIp(targetPlayer)) .. " (" .. getPlayerIp(targetPlayer) .. ")"
    )

    return true
end
