local config = {
    rateExperience = getConfigInfo('rateExperience'),
    rateSkill = getConfigInfo('rateSkill'),
    rateLoot = getConfigInfo('rateLoot'),
    rateMagic = getConfigInfo('rateMagic'),
    rateSpawn = getConfigInfo('rateSpawn'),
    protectionLevel = getConfigInfo('protectionLevel'),
    stages = getBooleanFromString(getConfigInfo('experienceStages'))
}

function onSay(cid, words, param, channel)
    local experienceRate = config.rateExperience

    if config.stages then
        experienceRate = getExperienceStage(getPlayerLevel(cid), getVocationInfo(getPlayerVocation(cid)).experienceMultiplier)
    end

    local message = "Server Information:\n\n" ..
                        "Experience rate: x" .. experienceRate .. "\n" ..
                        "Skills rate: x" .. config.rateSkill .. "\n" ..
                        "Loot rate: x" .. config.rateLoot .. "\n" ..
                        "Magic rate: x" .. config.rateMagic .. "\n" ..
                        "Spawn rate: x" .. config.rateSpawn .. "\n" ..
                        "Protection level: " .. config.protectionLevel

    doPlayerPopupFYI(cid, message)
    return true
end
