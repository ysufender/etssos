---@module "script.common"

local Linker = require "script.linker"

---@type Efile
local Efile = require "efile"

---@module "script.arch"
local Arch = require "script.arch"

---@module "script.kernel"
local Kernel = require "script.kernel"

---@module "script.drivers"
local Drivers = require "script.drivers"

---@module "script.other"
local Other = require "script.other"

---@type Common.Options
local options = {
    name = "etssos",
    version = "0.0.1",

    as = "xtensa-lx106-elf-as ",
    cc = "xtensa-lx106-elf-gcc ",
    ld = "xtensa-lx106-elf-ld ",
    cflags = "-c -O2 ",
    asflags = " ",
    ldflags = "-T linker.ld "
              .."-nostdlib -nostartfiles -nodefaultlibs ",

    burner = "esptool ",
    board = "esp8266 ",
    port = "/dev/ttyUSB0 ",
    baud_rate = 9600,
    upload_rate = 115200,
}

local config_string = string.format([[
#ifndef _ETSSOS_CONFIG_H
#define _ETSSOS_CONFIG_H

#define ETSSOS_NAME    "%s"
#define ETSSOS_VERSION "%s"

#define ETSSOS_AS "%s"
#define ETSSOS_CC "%s"
#define ETSSOS_LD "%s"

#define ETSSOS_CFLAGS  "%s"
#define ETSSOS_LDFLAGS "%s"
#define ETSSOS_ASFLAGS "%s"

#define ETSSOS_BURNER "%s"
#define ETSSOS_BOARD  "%s"
#define ETSSOS_PORT   "%s"
#define ETSSOS_BAUD   %d
#define ETSSOS_UPLOAD %d

#endif /* _ETSSOS_CONFIG_H */
]], options.name, options.version,
    options.as, options.cc, options.ld,
    options.cflags, options.ldflags, options.asflags,
    options.burner, options.board, options.port,
    options.baud_rate, options.upload_rate)

local project = Efile.Project
    .init(options.name)

project
    :step(Efile.Step
        .init("base")
        :dependOnFile("build.lua")
        :action("mkdir -p config")
        :action(function ()
            local file = io.open("config/etssos_config.h", "w")
            if not file then return "Failed to create config file" end

            local _, err = file:write(config_string)

            if err then
                return "Failed to create config file: "..err
            end
        end))

    :step(Efile.Step
        .init("all")
        :dependOnSteps({
            "create_bin",
        }))

    :multiStep(Arch.steps(options))
    :multiStep(Kernel.steps(options))
    :multiStep(Drivers.steps(options))

    :step(Linker.step(project, options))

    :step(Efile.Step
        .init("create_bin")
        :dependOnStep("link")
        :action("rm -f build/bin/"..options.name..".elf-*")
        :action(options.burner
                .."--chip "..options.board
                .."elf2image build/bin/etssos.elf"))

    :multiStep(Other.upload(options))

    :step(Efile.Step
        .init("monitor", { always_run = true })
        :dependOnStep("upload")
        :action(function ()
            local exec = string.format([[
                python3 -c "
                    import serial
                    s = serial.Serial('%s', %d)
                    while True:
                        print(s.readline().decode('utf-8', errors = 'ignore'), end = '', flush = True)
                "
                ]], options.port:match("(.*) "), options.baud_rate)

            local serial = io.popen(exec, "r")
            if not serial then return "Failed to open serial" end

            for line in serial:lines() do
                print(line)
            end

            local _, _, code = serial:close()
            if not code then return "Error during serial "..tostring(code) end
        end))

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
            print("    upload")
        end))

local result = project:build(arg[1] or "all") or "Success"
print(result)
