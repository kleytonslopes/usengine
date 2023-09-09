project "KyrnnessAsset"
    kind "StaticLib"
    language "C++"
    cppdialect "c++17"
    staticruntime "on"

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
        "%{include_dir.KyrnnessCore}",
    }

    filter "system:windows"
        systemversion "latest"
        
        defines
        {
            "PLATFORM_WINDOWS",
        }

        filter "configurations:Debug"
            defines 
            {
                "DEBUG",
            }
            buildoptions "/MTd"
            symbols "on"

        filter "configurations:EditorDebug"
            defines 
            {
                "DEBUG",
            }
            buildoptions "/MTd"
            symbols "on"

        filter "configurations:GameDebug"
            defines 
            {
                "DEBUG",
            }
            buildoptions "/MTd"
            symbols "on"
            
        filter "configurations:Release"
            defines 
            {
                "RELEASE",
                "NDEBUG",
            }
            buildoptions "/MD"
            optimize "on"