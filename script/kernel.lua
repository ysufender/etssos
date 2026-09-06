---@module "script.common"

---@type Efile
local Efile = require "efile"

local Common = require "script.common"

---@param sub_path string
---@return string
local function kernel(sub_path) return "kernel/"..sub_path end

---@param sub_path string
---@return string
local function header(sub_path) return string.match(sub_path, "(.+%a+.+)%.c")..".h" end

---@param options Common.Options
---@param sources string[]
---@return Efile.Step[]
local function steps(options, sources)
    local _steps = { }
    local step_names = { }

    for _, src in ipairs(sources) do
        local resolved_src = kernel(src)
        local cmd, out, pre = Common.cc(resolved_src, options)
        table.insert(step_names, out)

        local step = Efile.Step
            .init(out)
            :dependOnStep("base")
            :dependOnFile("script/kernel.lua")
            :dependOnFile(resolved_src)
            :action(cmd)
            :pre(pre)

        if os.execute("test -e "..header(resolved_src)) then
            step:dependOnFile(header(resolved_src))
        end

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
