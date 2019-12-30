TIMEOUT = 2.5

TMR = tmr.create()

function S()
    print("Interrupted.")
    TMR:stop()
end

print("Fuse Program v2")

for file_name, file_size in pairs(file.list()) do
    if file_name == "main.lua" then
        print("'main.lua' will be run in", TIMEOUT, "seconds")
        print("Invoke function S() to stop booting.")
        TMR:register(TIMEOUT * 1000, tmr.ALARM_SINGLE,
            function()
                print("Run 'main.lua' now.")
                dofile("main.lua")
            end)
        TMR:start()
        return
    end
end

print("Warn: 'main.lua' does not exist.")
