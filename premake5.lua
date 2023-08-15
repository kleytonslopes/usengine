include_dir = {}
include_dir["SDL2"]         = "F:/Dependencies/SDL2/SDL2-2.26.5/include"
include_dir["GLM"]          = "F:/Dependencies/glm"
include_dir["BULLET"]       = "F:/Dependencies/bullet3/src"
include_dir["GLAD"]         = "%{wks.location}/ThirdParty/GLAD/include"
include_dir["UUID"]         = "%{wks.location}/ThirdParty/UUID_V4"
include_dir["YAML"]         = "%{wks.location}/ThirdParty/YAML/include"
include_dir["IMGUI"]        = "%{wks.location}/ThirdParty/IMGUI"
include_dir["ASSIMP"]       = "%{wks.location}/ThirdParty/ASSIMP/include"
include_dir["ASSIMP_BUILD"] = "%{wks.location}/ThirdParty/ASSIMP/build/include"
include_dir["STB"]          = "%{wks.location}/ThirdParty/STB"
include_dir["MINI"]         = "%{wks.location}/ThirdParty/MINI/src"

extern_lib_dir = {}
extern_lib_dir["SDL2"] = "F:/Dependencies/SDL2/SDL2-2.26.5/lib/x64"
extern_lib_dir["BULLET"] = "F:/Dependencies/bullet3/build/lib/Debug"
extern_lib_dir["ASSIMP"] = "%{wks.location}/ThirdParty/ASSIMP/build/lib/Debug"


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