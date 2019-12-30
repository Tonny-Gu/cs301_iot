led_default = {
    ["r"] = 100,
    ["g"] = 100,
    ["b"] = 100
}


function stm32_cmd(opcode, reg, hval, lval)
    checksum = bit.bxor(opcode, reg, hval, lval)
    spi.send(1, opcode, reg, hval, lval, checksum)
    return checksum
end

function stm32_cmd_wb(reg, val)
    if val==nil or val==-1 then return end
    stm32_cmd(0x11, reg, 0x00, val)
end

function stm32_cmd_wh(reg, val)
    if val==nil or val==-1 then return end
    lval = bit.band(val, 0xFF)
    hval = bit.rshift(val, 8)
    stm32_cmd(0x12, reg, hval, lval)
end

function stm32_cmd_rb(reg)
    stm32_cmd(0x21, reg, 0x00, 0x00)
    return string.byte(spi.recv(1, 1))
end

function stm32_cmd_rh(reg)
    lval = stm32_cmd_rb(reg)
    stm32_cmd(0x22, reg, 0x00, 0x00)
    hval = string.byte(spi.recv(1, 1))
    val = bit.lshift(hval, 8) + lval
    return val
end

function stm32_cmd_rst()
    spi.send(1, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE)    
end

function stm32_set_led(status)
    if not status then return end
    stm32_cmd_wh(1, status["r"])
    stm32_cmd_wh(2, status["g"])
    stm32_cmd_wh(3, status["b"])
end

function stm32_set_led_default(status)
    if not status then return end
    stm32_cmd_wh(8, status["r"])
    stm32_cmd_wh(9, status["g"])
    stm32_cmd_wh(10, status["b"])
end

function stm32_set_motor(status)
    if not status then return end
    stm32_cmd_wh(4, status["speed"])
end

function stm32_set_env(status)
    if not status then return end
    stm32_cmd_wb(5, status["temp"])
    stm32_cmd_wb(6, status["humi"])
    stm32_cmd_wh(7, status["ambi"])
end

function stm32_set_node(status)
    if not status then return end
    stm32_cmd_wb(11, status["auto_mode"])
    stm32_cmd_wh(12, status["ambi_throttle"])
end

function stm32_get_led_status()
    return {
        ["r"] = stm32_cmd_rh(1),
        ["g"] = stm32_cmd_rh(2),
        ["b"] = stm32_cmd_rh(3)
    }
end

function stm32_get_motor_status()
    return {
        ["speed"] = stm32_cmd_rh(4)
    }
end

function stm32_get_node_status()
    return {
        ["auto_mode"] = stm32_cmd_rb(11),
        ["ambi_throttle"] = stm32_cmd_rh(12)
    }
end

function stm32_spi_init()
    print("[Info] SPI: Init.")
    spi.setup(1, spi.MASTER, spi.CPOL_LOW, spi.CPHA_LOW, 8, 32, spi.FULLDUPLEX)
    PIN_CS = 8
    gpio.mode(PIN_CS, gpio.INPUT, gpio.PULLUP)
    stm32_cmd_rst()
    stm32_set_led_default(led_default)
    stm32_cmd_wh(12, 950)
    led_default = nil
end

stm32_spi_init()
