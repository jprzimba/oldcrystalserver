--------------------------------------------------------------------------------------------
	------------------------------   Script by Shynzo --------------------------------
--------------------------------------------------------------------------------------------
local keywordHandler = KeywordHandler:new()
local npcHandler = NpcHandler:new(keywordHandler)
NpcSystem.parseParameters(npcHandler)
local talkState = {}

function onCreatureAppear(cid)				npcHandler:onCreatureAppear(cid)			end
function onCreatureDisappear(cid)			npcHandler:onCreatureDisappear(cid)			end
function onCreatureSay(cid, type, msg)			npcHandler:onCreatureSay(cid, type, msg)		end
function onThink()					npcHandler:onThink()					end

function creatureSayCallback(cid, type, msg)
	if(not npcHandler:isFocused(cid)) then
		return false
	end

	local talkUser = NPCHANDLER_CONVBEHAVIOR == CONVERSATION_DEFAULT and 0 or cid
	local addonItem = 'Sorry, you don\'t have the items I requested.'        -- what will the NPC say if you don't have the items he wants
	local addonPremium = 'Sorry, you need a premium account to get addons.'    -- what will the NPC say if you aren't a premium player
	local addonGive = 'Here you are.'                                        -- what will the NPC say if he gives you the addon

	if(msgcontains(msg, 'first') or msgcontains(msg, 'first addon')) then
        if isPremium(cid) then
         
                if getPlayerItemCount(cid,2160) >= 1 then
                    selfSay('Did you buy first addons for 10k?', cid)
		talkState[talkUser] = 1
                else
                    selfSay('Come back when you have 10k.', cid)
                end

        else
            selfSay(addonPremium, cid)
        end
	elseif(msgcontains(msg, 'yes') and talkState[talkUser] == 1) then
        if getPlayerItemCount(cid,2160) >= 1 or getPlayerItemCount(cid,2152) >= 100 or getPlayerItemCount(cid,2148) >= 10000 then
            if doPlayerTakeItem(cid,2160,1) or doPlayerTakeItem(cid,2152,100) or doPlayerTakeItem(cid,2148,10000) == 0 then
                selfSay(addonGive, cid)
				doPlayerAddOutfit(cid, 136, 1)
				doPlayerAddOutfit(cid, 128, 1)
				doPlayerAddOutfit(cid, 137, 1)
				doPlayerAddOutfit(cid, 129, 1)
				doPlayerAddOutfit(cid, 138, 1)
				doPlayerAddOutfit(cid, 130, 1)
				doPlayerAddOutfit(cid, 139, 1)
				doPlayerAddOutfit(cid, 131, 1)
				doPlayerAddOutfit(cid, 140, 1)
				doPlayerAddOutfit(cid, 132, 1)
				doPlayerAddOutfit(cid, 141, 1)
				doPlayerAddOutfit(cid, 133, 1)
				doPlayerAddOutfit(cid, 142, 1)
				doPlayerAddOutfit(cid, 134, 1)
				doPlayerAddOutfit(cid, 147, 1)
				doPlayerAddOutfit(cid, 143, 1)
				doPlayerAddOutfit(cid, 148, 1)
				doPlayerAddOutfit(cid, 144, 1)
				doPlayerAddOutfit(cid, 149, 1)
				doPlayerAddOutfit(cid, 145, 1)
				doPlayerAddOutfit(cid, 150, 1)
				doPlayerAddOutfit(cid, 146, 1)
				doPlayerAddOutfit(cid, 155, 1)
				doPlayerAddOutfit(cid, 151, 1)
				doPlayerAddOutfit(cid, 156, 1)
				doPlayerAddOutfit(cid, 152, 1)
				doPlayerAddOutfit(cid, 157, 1)
				doPlayerAddOutfit(cid, 153, 1)
				doPlayerAddOutfit(cid, 158, 1)
				doPlayerAddOutfit(cid, 154, 1)
				doPlayerAddOutfit(cid, 252, 1)
				doPlayerAddOutfit(cid, 251, 1)
				doPlayerAddOutfit(cid, 269, 1)
				doPlayerAddOutfit(cid, 268, 1)
				doPlayerAddOutfit(cid, 270, 1)
				doPlayerAddOutfit(cid, 273, 1)
				doPlayerAddOutfit(cid, 279, 1)
				doPlayerAddOutfit(cid, 278, 1)
				doPlayerAddOutfit(cid, 288, 1)
				doPlayerAddOutfit(cid, 289, 1)
				doPlayerAddOutfit(cid, 324, 1)
				doPlayerAddOutfit(cid, 325, 1)
				doPlayerAddOutfit(cid, 336, 1)
				doPlayerAddOutfit(cid, 335, 1)

            end
        else
            selfSay(addonItem, cid)
        end
        talkState[talkUser] = 0
    elseif (msgcontains(msg, 'second') or msgcontains(msg, 'second addon')) then
        if isPremium(cid) then
                if getPlayerItemCount(cid,2160) >= 2 or getPlayerItemCount(cid,2152) >= 200 or getPlayerItemCount(cid,2148) >= 20000 then
                    selfSay('Did you bring me the 20k?', cid)
                    talkState[talkUser] = 4
                else
                    selfSay('Come back when you have the 20k.', cid)
                end

        else
            selfSay(addonPremium, cid)
        end
	elseif(msgcontains(msg, 'yes') and talkState[talkUser] == 4) then
	if getPlayerItemCount(cid,2160) >= 2 or getPlayerItemCount(cid,2152) >= 200 or getPlayerItemCount(cid,2148) >= 20000 then
            if doPlayerTakeItem(cid,2160,1) or doPlayerTakeItem(cid,2152,100) or doPlayerTakeItem(cid,2148,10000) == 0 then
                selfSay(addonGive, cid)
				doPlayerAddOutfit(cid, 136, 2)
				doPlayerAddOutfit(cid, 128, 2)
				doPlayerAddOutfit(cid, 137, 2)
				doPlayerAddOutfit(cid, 129, 2)
				doPlayerAddOutfit(cid, 138, 2)
				doPlayerAddOutfit(cid, 130, 2)
				doPlayerAddOutfit(cid, 139, 2)
				doPlayerAddOutfit(cid, 131, 2)
				doPlayerAddOutfit(cid, 140, 2)
				doPlayerAddOutfit(cid, 132, 2)
				doPlayerAddOutfit(cid, 141, 2)
				doPlayerAddOutfit(cid, 133, 2)
				doPlayerAddOutfit(cid, 142, 2)
				doPlayerAddOutfit(cid, 134, 2)
				doPlayerAddOutfit(cid, 147, 2)
				doPlayerAddOutfit(cid, 143, 2)
				doPlayerAddOutfit(cid, 148, 2)
				doPlayerAddOutfit(cid, 144, 2)
				doPlayerAddOutfit(cid, 149, 2)
				doPlayerAddOutfit(cid, 145, 2)
				doPlayerAddOutfit(cid, 150, 2)
				doPlayerAddOutfit(cid, 146, 2)
				doPlayerAddOutfit(cid, 155, 2)
				doPlayerAddOutfit(cid, 151, 2)
				doPlayerAddOutfit(cid, 156, 2)
				doPlayerAddOutfit(cid, 152, 2)
				doPlayerAddOutfit(cid, 157, 2)
				doPlayerAddOutfit(cid, 153, 2)
				doPlayerAddOutfit(cid, 158, 2)
				doPlayerAddOutfit(cid, 154, 2)
				doPlayerAddOutfit(cid, 252, 2)
				doPlayerAddOutfit(cid, 251, 2)
				doPlayerAddOutfit(cid, 269, 2)
				doPlayerAddOutfit(cid, 268, 2)
				doPlayerAddOutfit(cid, 270, 2)
				doPlayerAddOutfit(cid, 273, 2)
				doPlayerAddOutfit(cid, 279, 2)
				doPlayerAddOutfit(cid, 278, 2)
				doPlayerAddOutfit(cid, 288, 2)
				doPlayerAddOutfit(cid, 289, 2)
				doPlayerAddOutfit(cid, 324, 2)
				doPlayerAddOutfit(cid, 325, 2)
				doPlayerAddOutfit(cid, 336, 2)
				doPlayerAddOutfit(cid, 335, 2)
            end
        else
            selfSay(addonItem, cid)
        end

		talkState[talkUser] = 0
	elseif(msgcontains(msg, 'no') and isInArray({1}, talkState[talkUser])) then
		talkState[talkUser] = 0
		selfSay('Ok then.', cid)
	end

	return true
end

npcHandler:setCallback(CALLBACK_MESSAGE_DEFAULT, creatureSayCallback)
npcHandler:addModule(FocusModule:new())


