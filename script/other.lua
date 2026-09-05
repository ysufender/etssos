---@module "script.efile"
---@module "script.common"

---@type Efile
local Efile = require "efile"

---@class Other
local Other = {}

---@param pattern string
---@return fun(): string
local function glob_files(pattern)
    local proc = io.popen("ls "..pattern)

    if proc then
        local matches = proc:lines()
        return matches
    else
        return function() return "" end
    end
end

---@param options Common.Options
---@return Efile.Step
function Other.upload(options)
    ---@type Efile.Step[]
    local steps = { }

    ---@type string[]
    local step_names = { }

    local bin_glob = "build/bin/"..options.name..".elf-*"
    local matches = glob_files(bin_glob)

    for match in matches do
        local address = string.match(match, ".%.elf+%-(.+)%.+")
        local cmd = options.burner
                    .."--chip "..options.board
                    .."--port "..options.port
                    .."--baud "..tostring(options.upload_rate).." "
                    .."--no-stub "
                    .."write-flash "..address.." "..match

        table.insert(step_names, match)
        table.insert(steps, Efile.Step
            .init(match)
            :dependOnStep("create_bin")
            :dependOnFile("script/other.lua")
            :action(cmd))
    end

    table.insert(steps, Efile.Step
        .init("upload")
        :dependOnSteps(step_names))

    return steps
end

return Other
