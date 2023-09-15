project "Usen"
    kind "StaticLib"
    language "C++"
    cppdialect "c++17"
    staticruntime "on"

    pchheader "upch.hpp"
    pchsource "src/upch.cpp"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/obj/" .. outputdir .. "/%{prj.name}")

    files
    {
        "include/**.hpp",
        "generated/**.hpp",
        "src/**.cpp"
    }

    includedirs
    {
        "include",
        "generated",
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

    links
    {
        "YAML",
    }

    filter "system:windows"
        systemversion "latest"
        
        defines
        {
            "PLATFORM_WINDOWS",
            "WIN32_LEAN_AND_MEAN",
            "_CRT_SECURE_NO_WARNINGS",
            "YAML_CPP_STATIC_DEFINE"
        }

        filter "configurations:Debug"
            defines 
            {
                "DEBUG",
                "LOG_WARNING",
                "LOG_INFORMATION",
                "LOG_DEBUG",
                "LOG_TRACE",
                "LOG_DEFAULT",
            }
            buildoptions "/MTd"
            symbols "on"

        filter "configurations:EditorDebug"
            defines 
            {
                "DEBUG",
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
                "RELEASE",
                "NDEBUG",
            }
            buildoptions "/MT"
            optimize "on"