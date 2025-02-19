function main()
    print(starry.deg2rad(180))
    print(starry.rad2deg(3.14))
    print(starry.random_base64(10))
    print(starry.clamp(56934, 0, 10))

    mate = vec2.new(1, 2)
    man = vec2.new(3, 4)
    print(mate:add(man))
end

-- just so we get a stack trace
local _, err = xpcall(main, debug.traceback);
if err ~= nil then print(err) end