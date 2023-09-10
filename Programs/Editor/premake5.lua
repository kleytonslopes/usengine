project "Editor"
    kind "ConsoleApp"
    language "C++"
    cppdialect "c++17"
    staticruntime "on"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/obj/" .. outputdir .. "/%{prj.name}")

    files
    {
        "include/**.hpp",
        "include/**.h",
        "generated/**.hpp",
        "src/**.cpp"
    }

    includedirs
    {
        "include",
        "generated",
        "%{wks.location}/Engine/Usen/include",
        "%{wks.location}/Engine/Usen/generated",
        "%{include_dir.SDL2}",
        "%{include_dir.GLAD}",
        "%{include_dir.UUID}",
        "%{include_dir.GLM}",
        "%{include_dir.YAML}",
        "%{include_dir.ASSIMP}",
        "%{include_dir.ASSIMP_BUILD}",
        "%{include_dir.STB}",
        "%{include_dir.MINI}",
        "%{include_dir.BULLET}",
        "%{include_dir.IMGUI}",
        "%{include_dir.PHYSX}",
        "%{include_dir.FBXSDK}",
    }

    libdirs
    {
        "%{extern_lib_dir.SDL2}",
        "%{extern_lib_dir.ASSIMP}",
        "%{extern_lib_dir.BULLET}",
        "%{extern_lib_dir.PHYSX}",
        "%{extern_lib_dir.FBXSDK}",
    }

    links
    {
        "opengl32.lib",
        "Usen",
        "GLAD",
        "IMGUI",
        "YAML",
        "SDL2.lib",
        "SDL2main.lib",
        "assimp-vc143-mtd.lib",
        "Bullet3Common_Debug.lib",
        "Bullet3Dynamics_Debug.lib",
        "Bullet3Collision_Debug.lib",
        "BulletCollision_Debug.lib",
        "BulletDynamics_Debug.lib",
        "LinearMath_Debug.lib",
        "LowLevel_static_64.lib",
        "LowLevelAABB_static_64.lib",
        "LowLevelDynamics_static_64.lib",
        "PhysX_64.lib",
        "PhysXCharacterKinematic_static_64.lib",
        "PhysXCommon_64.lib",
        "PhysXCooking_64.lib",
        "PhysXExtensions_static_64.lib",
        "PhysXFoundation_64.lib",
        "PhysXPvdSDK_static_64.lib",
        "PhysXTask_static_64.lib",
        "PhysXVehicle_static_64.lib",
        "PhysXVehicle2_static_64.lib",
        "PVDRuntime_64.lib",
        "SceneQuery_static_64.lib",
        "SimulationController_static_64.lib",
        "SnippetRender_static_64.lib",
        "SnippetUtils_static_64.lib",
        "libfbxsdk.lib",
    }

    postbuildcommands
    {
        "copy F:\\Dependencies\\SDL2\\SDL2-2.26.5\\lib\\x64\\SDL2.dll $(SolutionDir)Programs\\Editor\\SDL2.dll",
        "copy %{wks.location}\\ThirdParty\\ASSIMP\\build\\bin\\Debug\\assimp-vc143-mtd.dll $(SolutionDir)Programs\\Editor\\assimp-vc143-mtd.dll",
        --"copy C:\\Program Files\\Autodesk\\FBX\\FBX SDK\\2020.3.4\\lib\\vs2022\\x64\\release\\libfbxsdk.dll $(SolutionDir)Programs\\Editor\\libfbxsdk.dll",
    }

    filter "system:windows"
        systemversion "latest"

        --defines
        --{
        --    "PLATFORM_WINDOWS",
        --    "WIN32_LEAN_AND_MEAN",
        --    "_CRT_SECURE_NO_WARNINGS",
        --    "YAML_CPP_STATIC_DEFINE",
        --    "_DEBUG",
        --}

        filter "configurations:Debug"
            defines 
            {
                "DEBUG",
                "PLATFORM_WINDOWS",
                "WIN32_LEAN_AND_MEAN",
                "_CRT_SECURE_NO_WARNINGS",
                "YAML_CPP_STATIC_DEFINE",
                "LOG_WARNING",
                "LOG_INFORMATION",
                "LOG_DEBUG",
                "LOG_TRACE",
                "LOG_DEFAULT",
            }
            buildoptions "/MTd" --MDd
            symbols "on"

        filter "configurations:EditorDebug"
            defines 
            {
                "DEBUG",
                "PLATFORM_WINDOWS",
                "WIN32_LEAN_AND_MEAN",
                "_CRT_SECURE_NO_WARNINGS",
                "YAML_CPP_STATIC_DEFINE",
                "LOG_WARNING",
                "LOG_INFORMATION",
                "LOG_DEBUG",
                "LOG_TRACE",
                "LOG_DEFAULT",
                "APP_EDITOR_MODE"
            }
            buildoptions "/MTd"
            symbols "on"

        filter "configurations:GameDebug"
            defines 
            {
                "DEBUG",
                "PLATFORM_WINDOWS",
                "WIN32_LEAN_AND_MEAN",
                "_CRT_SECURE_NO_WARNINGS",
                "YAML_CPP_STATIC_DEFINE",
                "LOG_WARNING",
                "LOG_INFORMATION",
                "LOG_DEBUG",
                "LOG_TRACE",
                "LOG_DEFAULT",
                "APP_GAME_MODE"
            }
            buildoptions "/MTd"
            symbols "on"

        filter "configurations:Release"
            defines 
            {
                "NDEBUG",
                "PLATFORM_WINDOWS",
                "WIN32_LEAN_AND_MEAN",
                "_CRT_SECURE_NO_WARNINGS",
                "YAML_CPP_STATIC_DEFINE",
            }
            buildoptions "/MT"
            optimize "on"