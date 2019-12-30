WIFI_CFG = {}
WIFI_CFG.ssid = "Proj"
WIFI_CFG.pwd = ""
WIFI_CFG.save = false
WIFI_CFG.auto = true
WIFI_CFG.got_ip_cb = function(info) on_wifi_conn() end

PIN_DHT11 = 4
NTP_SERVER = "203.107.6.88"

MQTT_SERVER = "47.106.254.82"
MQTT_PORT = 10010
MQTT_TOPIC_PUB = "/node0/pub"
MQTT_TOPIC_SUB = "/node0/sub"
MQTT = mqtt.Client("clientid", 120)
MQTT:on("message", function(client, topic, data) on_mqtt_recv(topic, data) end)
MQTT:on("offline", function(client) node.restart() end)
MQTT:on("connect",
    function(client)
        print("[Info] MQTT: Connected.")
        MQTT:subscribe(MQTT_TOPIC_SUB, 1)
        TASK_POLL:start()
    end
)

POLL_CYCLE_TIME = 10
SYNC_CYCLE_TIME = 2
TASK_POLL = tmr.create()
TASK_POLL:register(POLL_CYCLE_TIME * 1000, tmr.ALARM_AUTO, function() task_poll_main() end)
TASK_SYNC = tmr.create()
TASK_SYNC:register(SYNC_CYCLE_TIME * 1000, tmr.ALARM_AUTO, function() task_sync_main() end)

env = {
    ["temp"] = 0,
    ["humi"] = 0,
    ["ambi"] = 0
}

led = {
    ["r"] = 0,
    ["g"] = 0,
    ["b"] = 0
}

motor = {
    ["speed"] = 0
}

node = {
    ["auto_mode"] = 0,
    ["ambi_throttle"] = 0
}

cmd = nil

function on_mqtt_recv(topic, msg)
    print("[Info] MQTT: Received message: ", msg)
    cmd = sjson.decode(msg)["cmd"]
end

function task_sync_main()
    nouse, env["temp"], env["humi"], nouse, nouse = dht.read(PIN_DHT11)
    env["ambi"] = 1024 - adc.read(0)
    
    stm32_cmd_rst()
    stm32_set_env(env)
    if cmd then
        stm32_set_led(cmd["led"])
        stm32_set_motor(cmd["motor"])
        stm32_set_node(cmd["node"])
        cmd = nil
    end
    led = stm32_get_led_status()
    motor = stm32_get_motor_status()
    node = stm32_get_node_status()
    print("[Info] SPI: Sync finished.")
end

function task_poll_main()
    msg = { ["timestamp"] = rtctime.get(),
        ["sensor"] = env,
        ["status"] = {
            ["led"] = led,
            ["motor"] = motor,
            ["node"] = node
        }
    }
    msg_json = sjson.encode(msg)
    print("[Info] MQTT: Sent message: ", msg_json)
    MQTT:publish(MQTT_TOPIC_PUB, msg_json, 1, 1)
end

function on_wifi_conn()
    print("[Info] WiFi: Connected. Info: ", wifi.sta.getip())
    sntp.sync(NTP_SERVER,
        function(sec, usec, server, info)
            tm = rtctime.epoch2cal(rtctime.get() + 28800)
            print("[Info] SNTP: Current time: ", string.format("%04d/%02d/%02d %02d:%02d:%02d", tm["year"], tm["mon"], tm["day"], tm["hour"], tm["min"], tm["sec"]))
        end,
        
        function()
            print("[Info] SNTP: Failed.")
        end,
        
        true
    )
    MQTT:connect(MQTT_SERVER, MQTT_PORT)
end

function main()
    dofile("spi_test.lua");
    
    
    print("[Info] WiFi: Init.")
    wifi.sta.config(WIFI_CFG)

    TASK_SYNC:start()
end

main()
