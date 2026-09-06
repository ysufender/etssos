---@module "script.common"

---@type Efile
local Efile = require "efile"

local asmsources = {
    "boot.S",
}

local other = {
    "arch/archdef.h",
    "arch/interrupt.S",
    "script/arch.lua"
}

---@param source_path string
---@param options Common.Options
---@return string, string, string
local function asm(source_path, options)
    local output_file = "build/"..string.match(source_path, "(.+%a+.+)%.S")..".o"
    local base_dir = "build/"..string.match(source_path, "(.+/).+%.S")

    return
        options.as..options.asflags..source_path.." -o "..output_file,
        output_file,
        "mkdir -p "..base_dir
end

---@param sub_path string
---@return string
local function arch(sub_path) return "arch/"..sub_path end

---@param options Common.Options
---@return Efile.Step[]
local function steps(options)
    local _steps = { }
    local step_names = { }

    for _, src in ipairs(asmsources) do
        local resolved_src = arch(src)
        local cmd, out, pre = asm(resolved_src, options)
        table.insert(step_names, out)
        table.insert(_steps, Efile.Step
            .init(out)
            :dependOnStep("base")
            :dependOnFiles(other)
            :dependOnFile(resolved_src)
            :action(cmd)
            :pre(pre))
    end

    table.insert(_steps, Efile.Step
        .init("arch")
        :dependOnSteps(step_names))

    return _steps
end

---@type Common.Step
return {
    steps = steps
}
