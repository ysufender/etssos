---@module "script.common"

---@type Efile
local Efile = require "efile"

local Common = require "script.common"

local sources = {
    "timer.c",
    "interrupt.c",
    "pin.c",
    "kernel.c",
    "io.c",
}

local other = {
    "kernel/pin.h",
    "kernel/io.h",
    "kernel/interrupt.h",
    "kernel/kernel.h",
    "kernel/timer.h",
    "script/kernel.lua",
}

---@param sub_path string
---@return string
local function kernel(sub_path) return "kernel/"..sub_path end

---@param options Common.Options
---@return Efile.Step[]
local function steps(options)
    local _steps = { }
    local step_names = { }

    for _, src in ipairs(sources) do
        local resolved_src = kernel(src)
        local cmd, out, pre = Common.cc(resolved_src, options)
        table.insert(step_names, out)

        local step = Efile.Step
            .init(out)
            :dependOnSteps({
                "base",
                "libc",
            })
            :dependOnFiles(other)
            :dependOnFile(resolved_src)
            :action(cmd)
            :pre(pre)
        table.insert(_steps, step)
    end

    table.insert(_steps, Efile.Step
        .init("kernel")
        :dependOnSteps(step_names))

    return _steps
end

---@type Common.Step
return {
    steps = steps
}
