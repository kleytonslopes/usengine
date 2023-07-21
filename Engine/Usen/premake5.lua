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
        "src/**.cpp"
    }

    includedirs
    {
        "include",
        "%{include_dir.SDL2}",
        "%{include_dir.GLAD}",
        "%{include_dir.UUID}",
        "%{include_dir.GLM}",
    }

    links
    {

    }

    filter "system:windows"
        systemversion "latest"

        filter "configurations:Debug"
            defines 
            {
                "DEBUG",
                "WIN32_LEAN_AND_MEAN",
                "PLATFORM_WINDOWS",
                "LOG_WARNING",
                "LOG_INFORMATION",
                "LOG_DEBUG",
                "LOG_TRACE",
                "LOG_DEFAULT",
            }
            buildoptions "/MDd"
            symbols "on"
        
        filter "configurations:Release"
            defines 
            {
                "RELEASE",
                "WIN32_LEAN_AND_MEAN",
                "PLATFORM_WINDOWS",
            }
            buildoptions "/MD"
            optimize "on"