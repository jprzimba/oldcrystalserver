function onLogout(cid)
        if getPlayerStorageValue(cid, 36901) > 0 and getPlayerStorageValue(cid, 35700) < 1 then
                doPlayerSetStorageValue(cid, 36901, 0)
                return true
        end
        return true
end