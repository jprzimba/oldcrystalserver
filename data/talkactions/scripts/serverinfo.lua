local config = {
    rateExperience = getConfigInfo('rateExperience'),
    rateSkill = getConfigInfo('rateSkill'),
    rateLoot = getConfigInfo('rateLoot'),
    rateMagic = getConfigInfo('rateMagic'),
    rateSpawnMin = getConfigInfo('rateSpawnMin'),
    rateSpawnMax = getConfigInfo('rateSpawnMax'),
    protectionLevel = getConfigInfo('protectionLevel'),
    stages = getBooleanFromString(getConfigInfo('experienceStages'))
}

function onSay(cid, words, param, channel)
    local experienceRate = config.rateExperience

    if config.stages then
        experienceRate = getExperienceStage(getPlayerLevel(cid), getVocationInfo(getPlayerVocation(cid)).experienceMultiplier)
    end

    local spawnRateMessage = "Spawn rate: x" .. config.rateSpawnMin

    if config.rateSpawnMin ~= config.rateSpawnMax then
        spawnRateMessage = spawnRateMessage .. " to x" .. config.rateSpawnMax
    end

    local message = "Server Information:\n\n" ..
                        "Experience rate: x" .. experienceRate .. "\n" ..
                        "Skills rate: x" .. config.rateSkill .. "\n" ..
                        "Loot rate: x" .. config.rateLoot .. "\n" ..
                        "Magic rate: x" .. config.rateMagic .. "\n" ..
                        spawnRateMessage .. "\n" ..
                        "Protection level: " .. config.protectionLevel

    doPlayerPopupFYI(cid, message)
    return true
end
