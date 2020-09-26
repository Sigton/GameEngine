project "GameEngine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "gepch.h"
	pchsource "src/gepch.cpp"

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	defines
	{
        "_CRT_SECURE_NO_WARNINGS",
        "GE_PLATFORM_WINDOWS"
	}

	includedirs
	{
		"src"
	}

	links
	{
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
		}

	filter "configurations:Debug"
		defines "GE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "GE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "GE_DIST"
		runtime "Release"
		optimize "on"