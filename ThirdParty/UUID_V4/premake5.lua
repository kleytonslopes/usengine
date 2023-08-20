project "UUID"
    kind "StaticLib"
    language "C"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("obj/" .. outputdir .. "/%{prj.name}")

    files
    {
        "uuid_v4.h"
    }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

        
    filter "configurations:EditorDebug"
        runtime "Debug"
        symbols "on"

    filter "configurations:GameDebug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"