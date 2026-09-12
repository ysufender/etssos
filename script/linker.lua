---@module "script.common"
---@module "script.efile"

---@type Efile
local Efile = require "efile"

---@class Linker
local Linker = {}

---@param project Efile.Project
---@param options Common.Options
---@return Efile.Step
function Linker.step(project, options)
    ---@type string[]
    local object_files = { }

    for _, step in pairs(project.steps) do
        local extension = string.match(step.name, ".*(%..*)")
        if extension == ".o" then
            table.insert(object_files, step.name)
        end
    end

    local object_files_combined = table.concat(object_files, " ")

    return Efile.Step
        .init("link")
        :dependOnSteps({
            "arch",
            "kernel",
            "drivers",
            "libc",
            "user",
        })
        :dependOnFile("linker.ld")
        :pre("mkdir -p build/bin/")
        :action(
            options.ld
                ..options.ldflags
                .." -o build/bin/"..project.name..".elf "
                ..object_files_combined
                .." /home/joseph/prog/xtensa-lx106-elf/lib/gcc/xtensa-lx106-elf/8.4.0/libgcc.a ")
end

return Linker
