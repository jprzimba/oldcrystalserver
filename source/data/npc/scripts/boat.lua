local keywordHandler = KeywordHandler:new()
local npcHandler = NpcHandler:new(keywordHandler)
NpcSystem.parseParameters(npcHandler)

function onCreatureAppear(cid)			npcHandler:onCreatureAppear(cid)			end
function onCreatureDisappear(cid)		npcHandler:onCreatureDisappear(cid)			end
function onCreatureSay(cid, type, msg)		npcHandler:onCreatureSay(cid, type, msg)		end
function onThink()				npcHandler:onThink()					end

local travelNode = keywordHandler:addKeyword({'mystic island'}, StdModule.say, {npcHandler = npcHandler, onlyFocus = true, text = 'Do you wish to travel to {Mystic Island} for 10 gold coins?'})
	travelNode:addChildKeyword({'yes'}, StdModule.travel, {npcHandler = npcHandler, premium = true, level = 50, cost = 150, destination = {x=1447, y=1504, z=7} })
	travelNode:addChildKeyword({'no'}, StdModule.say, {npcHandler = npcHandler, onlyFocus = true, reset = true, text = 'I wouldn\'t go there either.'})

travelNode = keywordHandler:addKeyword({'enigma city'}, StdModule.say, {npcHandler = npcHandler, onlyFocus = true, text = 'Do you wish to travel to {Enigma City} for 150 gold coins?'})
	travelNode:addChildKeyword({'yes'}, StdModule.travel, {npcHandler = npcHandler, premium = true, level = 0, cost = 150, destination = {x=942, y=978, z=6} })
	travelNode:addChildKeyword({'no'}, StdModule.say, {npcHandler = npcHandler, onlyFocus = true, reset = true, text = 'Too expensive, eh?'})

keywordHandler:addKeyword({'travel'}, StdModule.say, {npcHandler = npcHandler, onlyFocus = true, text = 'I can take you to {Ardrak Island}, {Enigma City}, {Folda}, {Mystic Island}, {Orn City} and {Port Noble} for just a small fee.'})

npcHandler:addModule(FocusModule:new())