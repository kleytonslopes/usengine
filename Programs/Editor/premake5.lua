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
    }

    libdirs
    {
        "%{extern_lib_dir.SDL2}",
        "%{extern_lib_dir.ASSIMP}",
        "%{extern_lib_dir.BULLET}",
    }

    links
    {
        "opengl32.lib",
        "Usen",
        "GLAD",
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
    }

    postbuildcommands
    {
        "copy F:\\Dependencies\\SDL2\\SDL2-2.26.5\\lib\\x64\\SDL2.dll $(SolutionDir)Programs\\Editor\\SDL2.dll",
        "copy %{wks.location}\\ThirdParty\\ASSIMP\\build\\bin\\Debug\\assimp-vc143-mtd.dll $(SolutionDir)Programs\\Editor\\assimp-vc143-mtd.dll",
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
            buildoptions "/MDd"
            symbols "on"
        
        filter "configurations:Release"
            defines 
            {
                "RELEASE",
            }
            buildoptions "/MD"
            optimize "on"