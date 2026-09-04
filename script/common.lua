---@module "script.efile"

---@class Common.Options
---@field version string
---@field cc      string
---@field cflags  string
---@field as      string
---@field asflags string
---@field ld      string
---@field ldflags string

---@class Common.Step
---@field steps fun(options: Common.Options, sources: string[]): Step[]
