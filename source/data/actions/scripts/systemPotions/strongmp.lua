local potionID = 7589
local bpCharges = 20
local bpID = 7342
local bpPrice = 1600
local itemName = getItemNameById(potionID)

function onUse(cid, item, fromPosition, itemEx, toPosition)
	if doPlayerRemoveMoney(cid, bpPrice) == TRUE then
		local bag = doPlayerAddItem(cid, bpID, 1)
			doPlayerSendTextMessage(cid, MESSAGE_STATUS_CONSOLE_BLUE, "You have purchased a backpack of ".. itemName .."s for ".. bpPrice .." gold.")
		for i=1,20 do
			doAddContainerItem(bag, potionID, bpCharges)
		end
                else
                        doPlayerSendTextMessage(cid, MESSAGE_STATUS_CONSOLE_ORANGE, "You need ".. bpPrice .." gold coins for a backpack of ".. itemName .."s.")
		end
        return FALSE
end