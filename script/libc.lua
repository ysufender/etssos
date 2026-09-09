---@module "script.common"

---@type Efile
local Efile = require "efile"

local Common = require "script.common"

local sources = {
    "memory.c",
}

local other = {
    "libc/memory.h",
    "script/libc.lua",
}

---@param sub_path string
---@return string
local function libc(sub_path) return "libc/"..sub_path end

---@param options Common.Options
---@return Efile.Step[]
local function steps(options)
    local _steps = { }
    local step_names = { }

    for _, src in ipairs(sources) do
        local resolved_src = libc(src)
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
        .init("libc")
        :dependOnSteps(step_names))

    return _steps
end

---@type Common.Step
return {
    steps = steps
}
