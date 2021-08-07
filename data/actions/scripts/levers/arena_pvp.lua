local config = {
	level = 25,
	entry =
	{
		{x = 1040, y = 987, z = 8},
		{x = 1040, y = 989, z = 8}
	},
	destination =
	{
		{x = 1043, y = 988, z = 9},
		{x = 1050, y = 988, z = 9}
	}
}

function onUse(cid, item, fromPosition, itemEx, toPosition)
	if item.uid == 7001 and item.itemid == 1945 then
		local players = {}
		for _, position in ipairs(config.entry) do
			local pid = getTopCreature(position).uid
			if(pid == 0 or not isPlayer(pid) or getPlayerLevel(pid) < config.level) then
				doPlayerSendDefaultCancel(cid, RETURNVALUE_NOTPOSSIBLE)
				return true
			end

			table.insert(players, pid)
		end

		for i, pid in ipairs(players) do
			doSendMagicEffect(config.entry[i], CONST_ME_POFF)
			doTeleportThing(pid, config.destination[i], false)
			doSendMagicEffect(config.destination[i], CONST_ME_ENERGYAREA)
		end

		doTransformItem(item.uid, item.itemid + 1)
   	end
	return true
end
