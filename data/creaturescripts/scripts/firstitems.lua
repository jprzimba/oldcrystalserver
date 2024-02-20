local firstItems = {
    [0] = {2173, 2525, 3965, 2124, 2457, 2647, 2643},
    [1] = {2173, 2525, 2190, 2124, 2457, 2647, 2643},
    [2] = {2173, 2525, 2182, 2124, 2457, 2647, 2643},
    [3] = {2173, 2525, 2399, 2124, 2457, 2647, 2643},
    [4] = {2173, 2525, 2428, 2124, 2457, 2647, 2643},
}

function onLogin(cid)
    if getPlayerStorageValue(cid, 30001) == -1 then
        local vocationItems = firstItems[getPlayerVocation(cid)]

        for _, itemID in ipairs(vocationItems) do
            doPlayerAddItem(cid, itemID, 1)
        end

        local backpack = doPlayerAddItem(cid, 10522, 1)
        doAddContainerItem(backpack, 2160, 3)
        doAddContainerItem(backpack, 2554, 1)
        doAddContainerItem(backpack, 2120, 1)

        if getPlayerSex(cid) == 0 then
            doPlayerAddItem(cid, 2463, 1)
        else
            doPlayerAddItem(cid, 2463, 1)
        end

        setPlayerStorageValue(cid, 30001, 1)
    end

    return true
end
