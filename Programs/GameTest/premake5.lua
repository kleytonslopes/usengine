project "GameTest"
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
        "%{include_dir.IMGUI}",
        "%{include_dir.PHYSX}",
        "%{include_dir.FBXSDK}",
        "%{include_dir.ENTT}",
    }

    libdirs
    {
        "%{extern_lib_dir.SDL2}",
        --"%{extern_lib_dir.ASSIMP}",
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
        --"assimp-vc143-mtd.lib",
        "PhysX_64.lib",
        "PhysXCommon_64.lib",
        "PhysXCooking_64.lib",
        "PhysXExtensions_static_64.lib",
        "PhysXFoundation_64.lib",
        "PhysXPvdSDK_static_64.lib",
        "PhysXVehicle_static_64.lib",
        "PhysXVehicle2_static_64.lib",
        "PhysXCharacterKinematic_static_64.lib",
        "libfbxsdk.lib",
    }

    postbuildcommands
    {
        "copy F:\\Dependencies\\SDL2\\SDL2-2.26.5\\lib\\x64\\SDL2.dll $(SolutionDir)Programs\\GameTest\\SDL2.dll",
        "copy %{wks.location}\\ThirdParty\\ASSIMP\\build\\bin\\Debug\\assimp-vc143-mtd.dll $(SolutionDir)Programs\\GameTest\\assimp-vc143-mtd.dll",
        --"copy C:\\Program Files\\Autodesk\\FBX\\FBX SDK\\2020.3.4\\lib\\vs2022\\x64\\release\\libfbxsdk.dll $(SolutionDir)Programs\\GameTest\\libfbxsdk.dll",
    }

    filter "system:windows"
        systemversion "latest"

        --defines
        --{
        --    "PLATFORM_WINDOWS",
        --    "WIN32_LEAN_AND_MEAN",
        --    "_CRT_SECURE_NO_WARNINGS",
        --    "YAML_CPP_STATIC_DEFINE",
        --    "APP_GAME_MODE"
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
                "APP_GAME_MODE"
            }
            libdirs
            {
                "%{extern_lib_dir.PHYSX}",
                "%{extern_lib_dir.ASSIMP}",
            }
            links
            {
                "assimp-vc143-mtd.lib",
            }
            buildoptions "/MTd"
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
            libdirs
            {
                "%{extern_lib_dir.PHYSX}",
                "%{extern_lib_dir.ASSIMP}",
            }
            links
            {
                "assimp-vc143-mtd.lib",
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
            libdirs
            {
                "%{extern_lib_dir.PHYSX}",
                "%{extern_lib_dir.ASSIMP}",
            }
            links
            {
                "assimp-vc143-mtd.lib",
            }
            buildoptions "/MTd"
            symbols "on"

        filter "configurations:Release"
            defines 
            {
                "RELEASE",
                "NDEBUG",
            }
            libdirs
            {
                "%{extern_lib_dir_release.PHYSX}",
                "%{extern_lib_dir_release.ASSIMP}",
            }
            links
            {
                "LinearMath.lib",
                "assimp-vc143-mt.lib",
            }
            buildoptions "/MT"
            optimize "on"