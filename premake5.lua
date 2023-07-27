include_dir = {}
include_dir["SDL2"] = "F:/Dependencies/SDL2/SDL2-2.26.5/include"
include_dir["GLM"]  = "F:/Dependencies/glm"
include_dir["GLAD"] = "%{wks.location}/ThirdParty/GLAD/include"
include_dir["UUID"] = "%{wks.location}/ThirdParty/UUID_V4"
include_dir["YAML"] = "%{wks.location}/ThirdParty/YAML/include"
include_dir["IMGUI"] = "%{wks.location}/ThirdParty/IMGUI/include"

extern_lib_dir = {}
extern_lib_dir["SDL2"] = "F:/Dependencies/SDL2/SDL2-2.26.5/lib/x64"


workspace "UsEngine"
    architecture "x64"
    startproject "Editor"

    configurations{ "Debug", "Release" }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    flags
    {
        "MultiProcessorCompile"
    }

group "ThirdParty"
   include "ThirdParty/GLAD"
   include "ThirdParty/YAML"
   include "ThirdParty/IMGUI"
group ""

group "Engine"
   include "Engine/Usen"
group ""

group "Programs"
   include "Programs/Editor"
group ""

group "Generated"

group ""