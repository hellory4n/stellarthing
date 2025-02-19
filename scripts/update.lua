function main()
end

-- just so we get a stack trace
local _, err = xpcall(main, debug.traceback);
if err ~= nil then print(err) end