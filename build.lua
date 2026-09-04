local Efile = require "efile"

local Arch = require "script.arch"

local project_name = "etssos"
local project_version = "0.0.1"

local cc        = "xtensa-lx106-elf-gcc "
local cflags    = "-mtest-section-literals "
                  .."-mlongcalls "

local ld        = "xtensa-lx106-elf-ld "
local ldflags   = " "
local ldfile    = "linker.ld"

local kerneldir = "kernel/"
local driverdir = "drivers/"

---@type string[]
local kernelsrc = {
    "main.c",
}

---@type string[]
local archsrc = {
    "boot.S",
}

local project = Efile.Project
    .init(project_name)

    :step(Efile.Step
        .init("base")
        :dependOnFile("build.lua"))

    :multiStep(Arch.archsteps())

for _, step in pairs(project.steps) do
    print(step.name)
end

-- local result = project:build(arg[1] or "") or "Success"
-- print(result)
