---@module "script.efile"

---@class Common
local Common = { }

---@class Common.Options
---@field name        string
---@field version     string
---@field burner      string
---@field board       string
---@field baud_rate   integer
---@field upload_rate integer
---@field port        string
---@field cc          string
---@field cflags      string
---@field as          string
---@field asflags     string
---@field ld          string
---@field ldflags     string

---@class Common.Step
---@field steps fun(options: Common.Options): Efile.Step[]

---@param source_path string
---@param options Common.Options
---@return string, string, string
function Common.cc(source_path, options)
    local output_file = "build/"..string.match(source_path, "(.+%a+.+)%.c")..".o"
    local base_dir = "build/"..string.match(source_path, "(.+/).+%.c")

    return
        options.cc..options.cflags..source_path.." -o "..output_file,
        output_file,
        "mkdir -p "..base_dir
end

return Common
