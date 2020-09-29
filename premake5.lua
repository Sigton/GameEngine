workspace "GameEngine"
    architecture "x86_64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/GameEngine/vendor/GLFW/include"
IncludeDir["ImGui"] = "%{wks.location}/GameEngine/vendor/imgui"
IncludeDir["Glad"] = "%{wks.location}/GameEngine/vendor/Glad/include"

group "Dependencies"
    include "GameEngine/vendor/GLFW"
    include "GameEngine/vendor/imgui"
    include "GameEngine/vendor/Glad"
group ""

include "GameEngine"
include "Sandbox"
