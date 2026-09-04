---@class Efile
---@field Project  Project
---@field Step     Step
---@field Platform PLATFORM

---@enum PLATFORM
PLATFORM = {
    WIN32 = 0,
    UNIX  = 1,
}

---@alias Map<K, V> { [K]: V }

---@class Project
---@field name      string
---@field steps     Map<string, Step>
---@field init      fun(name: string): Project
---@field step      fun(self: string|Project, step: Step): string|Project
---@field multiStep fun(self: string|Project, steps: Step[]): string|Project
---@field build     fun(self: string|Project, target: string): string?
---@field resolve   fun(self: string|Project, target: string, to_build: string[], accumulator: Map<string, string>?, visited: Map<string, boolean>?): string?

---@class Step
---@field name          string
---@field dependencies  Step.Dependency[]
---@field actions       Step.Action[]
---@field _prebuild     Step.Action[]
---@field options       Step.Options
---@field init          fun(name: string, options: Step.Options?): Step
---@field dependOnStep  fun(self: Step, dependency: string): Step
---@field dependOnSteps fun(self: Step, dependencies: string[]): Step
---@field dependOnFile  fun(self: Step, dependency: string): Step
---@field dependOnFiles fun(self: Step, dependencies: string[]): Step
---@field action        fun(self: Step, action: Step.Action): Step
---@field pre           fun(self: Step, action: Step.Action): Step
---@field build         fun(self: Step): string?
---@field prebuild      fun(self: Step): string?

---@class Step.Options
---@field always_run boolean

---@alias Step.Command string
---@alias Script fun(): string?

---@class Step.Complex
---@field file string

---@alias Step.Action Step.Command|Script

---@alias Step.Dependency (Step.Complex)|(string)|(Step.Dependency.List)
---@alias Step.Dependency.List Step.Dependency[]
