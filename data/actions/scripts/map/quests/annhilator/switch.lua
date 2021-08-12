function onUse(cid, item, fromPosiiton, itemEx, toPosition)
	if item.uid == 7000 then
		if item.itemid == 1946 then
			player1pos = {x = 500, y = 755, z = 9, stackpos = 253}
			player1 = getThingfromPos(player1pos)

			player2pos = {x = 499, y = 755, z = 9, stackpos = 253}
			player2 = getThingfromPos(player2pos)

			player3pos = {x = 498, y = 755, z = 9, stackpos = 253}
			player3 = getThingfromPos(player3pos)

			player4pos = {x = 497, y = 755, z = 9, stackpos = 253}
			player4 = getThingfromPos(player4pos)

			if player1.itemid > 0 and player2.itemid > 0 and player3.itemid > 0 and player4.itemid > 0 then
				player1level = getPlayerLevel(player1.uid)
				player2level = getPlayerLevel(player2.uid)
				player3level = getPlayerLevel(player3.uid)
				player4level = getPlayerLevel(player4.uid)

 				questlevel = 100
  				if player1level >= questlevel and player2level >= questlevel and player3level >= questlevel and player4level >= questlevel then
					queststatus1 = getPlayerStorageValue(player1.uid, 100)
					queststatus2 = getPlayerStorageValue(player2.uid, 100)
					queststatus3 = getPlayerStorageValue(player3.uid, 100)
					queststatus4 = getPlayerStorageValue(player4.uid, 100)

					if queststatus1 == -1 and queststatus2 == -1 and queststatus3 == -1 and queststatus4 == -1 then
						demon1pos = {x = 498, y = 753, z = 10}
						demon2pos = {x = 500, y = 753, z = 10}
						demon3pos = {x = 499, y = 757, z = 10}
						demon4pos = {x = 497, y = 757, z = 10}
						demon5pos = {x = 502, y = 755, z = 10}
						demon6pos = {x = 501, y = 755, z = 10}
	 
						doSummonCreature("Demon", demon1pos)
						doSummonCreature("Demon", demon2pos)
						doSummonCreature("Demon", demon3pos)
						doSummonCreature("Demon", demon4pos)
						doSummonCreature("Demon", demon5pos)
						doSummonCreature("Demon", demon6pos)

						nplayer1pos = {x = 500, y = 755, z = 10}
						nplayer2pos = {x = 499, y = 755, z = 10}
						nplayer3pos = {x = 498, y = 755, z = 10}
						nplayer4pos = {x = 497, y = 755, z = 10}

						doSendMagicEffect(player1pos, CONST_ME_POFF)
						doSendMagicEffect(player2pos, CONST_ME_POFF)
  						doSendMagicEffect(player3pos, CONST_ME_POFF)
						doSendMagicEffect(player4pos, CONST_ME_POFF)

						doTeleportThing(player1.uid, nplayer1pos, 0)
						doTeleportThing(player2.uid, nplayer2pos, 0)
						doTeleportThing(player3.uid, nplayer3pos, 0)
						doTeleportThing(player4.uid, nplayer4pos, 0)

						doSendMagicEffect(nplayer1pos, CONST_ME_TELEPORT)
						doSendMagicEffect(nplayer2pos, CONST_ME_TELEPORT)
						doSendMagicEffect(nplayer3pos, CONST_ME_TELEPORT)
						doSendMagicEffect(nplayer4pos, CONST_ME_TELEPORT)
						doTransformItem(item.uid, 1945)
					else
						doPlayerSendCancel(cid, "Sorry, not possible.")
					end
				else
					doPlayerSendCancel(cid, "Sorry, not possible.")
				end
			else
				doPlayerSendCancel(cid, "Sorry, not possible.")
			end
		 end

		 if item.itemid == 1945 then
			starting = {x = 495, y = 751, z = 10, stackpos = 253}
			checking = {x = starting.x, y = starting.y, z = starting.z, stackpos = starting.stackpos}
			ending = {x = 502, y = 759, z = 10, stackpos = 253}
			players = 0
			totalmonsters = 0
			monster = {}
			repeat
			creature= getThingfromPos(checking)
			 if creature.itemid > 0 then
				 if getPlayerAccess(creature.uid) == 0 then
					 players = players + 1
				 end
				
				if getPlayerAccess(creature.uid) ~= 0 and getPlayerAccess(creature.uid) ~= 3 then
					totalmonsters = totalmonsters + 1
					monster[totalmonsters] = creature.uid
				end
			end

			checking.x = checking.x + 1
			if checking.x > ending.x then
				checking.x = starting.x
				checking.y = checking.y + 1
			end
			
			until checking.y > ending.y
			if players == 0 then
				trash= {x = 547, y = 407, z = 10}
				current = 0
				repeat
				current = current + 1
				doTeleportThing(monster[current], trash)
				until current >= totalmonsters
				doTransformItem(item.uid, 1946)
			end
		end
	end
	return true
end