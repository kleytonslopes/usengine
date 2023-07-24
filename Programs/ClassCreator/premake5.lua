project "ClassCreator"
	kind "ConsoleApp"
	language "C#"
	clr "Unsafe"
	nuget { "glfw-net:3.3.1" }
	
	files
	{
		path.join(BGFX_DIR, "bindings/cs/**.cs"),
		"examples/%{prj.name}/**.cs"
	}

	links { "System.Drawing" }

	filter "configurations:Debug"
		symbols "On"
		optimize "Debug"
		defines "DEBUG"

	filter "configurations:Release"
		optimize "Full"