include_dir = {}
include_dir["SDL2"]         = "F:/Dependencies/SDL2/SDL2-2.26.5/include"
include_dir["GLM"]          = "F:/Dependencies/glm"
include_dir["PHYSX"]        = "F:/Dependencies/PhysX/physx/include"
include_dir["FBXSDK"]       = "C:/Program Files/Autodesk/FBX/FBX SDK/2020.3.4/include"
include_dir["GLAD"]         = "%{wks.location}/ThirdParty/GLAD/include"
include_dir["UUID"]         = "%{wks.location}/ThirdParty/UUID_V4"
include_dir["YAML"]         = "%{wks.location}/ThirdParty/YAML/include"
include_dir["IMGUI"]        = "%{wks.location}/ThirdParty/IMGUI"
include_dir["ASSIMP"]       = "%{wks.location}/ThirdParty/ASSIMP/include"
include_dir["ASSIMP_BUILD"] = "%{wks.location}/ThirdParty/ASSIMP/build/include"
include_dir["STB"]          = "%{wks.location}/ThirdParty/STB"
include_dir["MINI"]         = "%{wks.location}/ThirdParty/MINI/src"
include_dir["ENTT"]         = "%{wks.location}/ThirdParty/ENTT/src"


extern_lib_dir = {}
extern_lib_dir["SDL2"]   = "F:/Dependencies/SDL2/SDL2-2.26.5/lib/x64"
extern_lib_dir["PHYSX"]  = "F:/Dependencies/PhysX/physx/bin/win.x86_64.vc143.mt/debug"
extern_lib_dir["ASSIMP"] = "%{wks.location}/ThirdParty/ASSIMP/build/lib/Debug"
extern_lib_dir["FBXSDK"] = "C:/Program Files/Autodesk/FBX/FBX SDK/2020.3.4/lib/vs2022/x64/release"

extern_lib_dir_release = {}
extern_lib_dir_release["ASSIMP"] = "%{wks.location}/ThirdParty/ASSIMP/build/lib/Release"
extern_lib_dir_release["PHYSX"] = "F:/Dependencies/PhysX/physx/bin/win.x86_64.vc143.mt/release"


workspace "UsEngine"
    architecture "x64"
    startproject "Editor"

    configurations{ "Debug", "EditorDebug", "GameDebug", "Release" }

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
   include "Programs/GameTest"
group ""

group "Libs"
group ""