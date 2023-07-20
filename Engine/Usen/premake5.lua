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
                "LOG_WARNING",
                "LOG_INFORMATION",
                "LOG_DEBUG",
                "LOG_TRACE",
                "LOG_DEFAULT",
            }
            buildoptions "/MDd"
            symbols "on"
        
        filter "configurations:Release"
            defines {"RELEASE"}
            buildoptions "/MD"
            optimize "on"