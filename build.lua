---@module "script.common"

local Linker = require "script.linker"

---@type Efile
local Efile = require "efile"

---@module "script.arch"
local Arch = require "script.arch"

---@module "script.kernel"
local Kernel = require "script.kernel"

---@type Common.Options
local options = {
    name = "etssos",
    version = "0.0.1",
    as = "xtensa-lx106-elf-as ",
    cc = "xtensa-lx106-elf-gcc ",
    ld = "xtensa-lx106-elf-ld ",
    cflags = "-c ",
    asflags = " ",
    ldflags = "-T linker.ld "
              .."-nostdlib -nostartfiles -nodefaultlibs ",
}

---@type string[]
local kernelsrc = {
    "kernel.c",
}

---@type string[]
local archsrc = {
    "boot.S",
}

local project = Efile.Project
    .init(options.name)

project
    :step(Efile.Step
        .init("base")
        :dependOnFile("build.lua"))

    :step(Efile.Step
        .init("all")
        :dependOnSteps({
            "link",
        }))

    :multiStep(Arch.steps(options, archsrc))
    :multiStep(Kernel.steps(options, kernelsrc))

    :step(Linker.step(project, options))

    :step(Efile.Step
        .init("clean")
        :action("rm -rf build"))

    :step(Efile.Step
        .init("help", { always_run = true })
        :action(function ()
            print("usage: efile <target>")
            print("targets:")
            print("    all")
            print("    arch")
            print("    kernel")
            print("    link")
            print("    help")
            print("    clean")
        end))

local result = project:build(arg[1] or "all") or "Success"
print(result)
