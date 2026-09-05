---@class Efile
---@field Project  Efile.Project
---@field Step     Efile.Step
---@field Platform Efile.PLATFORM

---@enum Efile.PLATFORM
PLATFORM = {
    WIN32 = 0,
    UNIX  = 1,
}

---@alias Map<K, V> { [K]: V }

---@class Efile.Project
---@field name      string
---@field steps     Map<string, Efile.Step>
---@field init      fun(name: string): Efile.Project
---@field step      fun(self: string|Efile.Project, step: Efile.Step): string|Efile.Project
---@field multiStep fun(self: string|Efile.Project, steps: Efile.Step[]): string|Efile.Project
---@field build     fun(self: string|Efile.Project, target: string): string?
---@field resolve   fun(self: string|Efile.Project, target: string, to_build: string[], accumulator: Map<string, string>?, visited: Map<string, boolean>?): string?

---@class Efile.Step
---@field name          string
---@field dependencies  Efile.Step.Dependency[]
---@field actions       Efile.Step.Action[]
---@field _prebuild     Efile.Step.Action[]
---@field options       Efile.Step.Options
---@field init          fun(name: string, options: Efile.Step.Options?): Efile.Step
---@field dependOnStep  fun(self: Efile.Step, dependency: string): Efile.Step
---@field dependOnSteps fun(self: Efile.Step, dependencies: string[]): Efile.Step
---@field dependOnFile  fun(self: Efile.Step, dependency: string): Efile.Step
---@field dependOnFiles fun(self: Efile.Step, dependencies: string[]): Efile.Step
---@field action        fun(self: Efile.Step, action: Efile.Step.Action): Efile.Step
---@field pre           fun(self: Efile.Step, action: Efile.Step.Action): Efile.Step
---@field build         fun(self: Efile.Step): string?
---@field prebuild      fun(self: Efile.Step): string?

---@class Efile.Step.Options
---@field always_run boolean

---@alias Efile.Step.Command string
---@alias Script fun(): boolean, Efile.Step.Action?

---@class Efile.Step.Complex
---@field file string

---@alias Efile.Step.Action Efile.Step.Command|Script

---@alias Efile.Step.Dependency (Efile.Step.Complex)|(string)|(Efile.Step.Dependency.List)
---@alias Efile.Step.Dependency.List Efile.Step.Dependency[]
