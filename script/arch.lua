---@class Step

local Efile = require "efile"

local Arch = { }

local archdir   = "arch/"

local as        = "xtensa-lx106-elf-as "
local asflags   = " "

---@param source_path string
---@return string, string
local function asm(source_path)
    local file_path_no_ext = string.match(source_path, "(.+%a+.+)%.S")
    local output_file = "build/"..file_path_no_ext..".o"
    return
        as..asflags..source_path.." -o "..output_file,
        output_file
end

---@param sub_path string
---@return string
local function arch(sub_path) return archdir..sub_path end

---@return Step[]
function Arch.archsteps(archsrc)
    local steps = { }
    local step_names = { }

    for _, src in ipairs(archsrc) do
        local resolved_src = arch(src)
        local cmd, out, pre = asm(resolved_src)
        table.insert(step_names, out)
        table.insert(steps, Efile.Step
            .init(out)
            :action(cmd)
            :pre(pre))
    end

    table.insert(steps, Efile.Step
        .init("arch")
        :dependOnStep("base")
        :dependOnSteps(step_names))

    return steps
end

---@class Option
---@field sources string[]
Arch.Option = { }

return Arch
