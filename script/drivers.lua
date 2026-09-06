---@module "script.common"

---@type Efile
local Efile = require "efile"

local Common = require "script.common"

---@param sub_path string
---@return string
local function driver(sub_path) return "drivers/"..sub_path end

local sources = {
    "uart/uart.c",
    "timer/timer.c",
    "gpio/gpio.c",
    "iomux.c",
}

local other = {
    driver("uart/uart.h"),
    driver("timer/timer.h"),
    driver("gpio/gpio.h"),
    driver("common.h"),
    driver("iomux.h"),
    "script/drivers.lua",
}

---@param options Common.Options
---@return Efile.Step[]
local function steps(options)
    local _steps = { }
    local step_names = { }

    for _, src in ipairs(sources) do
        local resolved_src = driver(src)
        local cmd, out, pre = Common.cc(resolved_src, options)
        table.insert(step_names, out)

        local step = Efile.Step
            .init(out)
            :dependOnStep("base")
            :dependOnFiles(other)
            :dependOnFile(resolved_src)
            :action(cmd)
            :pre(pre)

        table.insert(_steps, step)
    end

    table.insert(_steps, Efile.Step
        .init("drivers")
        :dependOnSteps(step_names))

    return _steps
end

---@type Common.Step
return {
    steps = steps
}
