include_dir = {}
include_dir["SDL2"] = "F:/Dependencies/SDL2/SDL2-2.26.5/include"

extern_include_dir = {}
extern_include_dir["SDL2"] = "F:/Dependencies/SDL2/SDL2-2.26.5/include"

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

group ""

group "Engine"
   include "Engine/Usen"
group ""

group "Programs"
   include "Programs/Editor"
group ""