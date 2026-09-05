---@module "script.efile"

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
---@field steps fun(options: Common.Options, sources: string[]): Efile.Step[]
