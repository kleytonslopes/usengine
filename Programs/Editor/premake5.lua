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
        "src/**.cpp"
    }

    includedirs
    {
        "include",
        "%{wks.location}/Engine/Usen/include",
        "%{include_dir.SDL2}",
        "%{include_dir.GLAD}",
        "%{include_dir.UUID}",
        "%{include_dir.GLM}",
    }

    libdirs
    {
        "%{extern_lib_dir.SDL2}"
    }

    links
    {
        "opengl32.lib",
        "Usen",
        "GLAD",
        "SDL2.lib",
        "SDL2main.lib"
    }

    postbuildcommands
    {
        "copy F:\\Dependencies\\SDL2\\SDL2-2.26.5\\lib\\x64\\SDL2.dll $(SolutionDir)Programs\\Editor\\SDL2.dll",
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
                "PLATFORM_WINDOWS",
                "WIN32_LEAN_AND_MEAN",
            }
            buildoptions "/MD"
            optimize "on"