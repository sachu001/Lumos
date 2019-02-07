project 'volk'
	kind 'StaticLib'
	systemversion "latest"
	cppdialect "C++14"
	files
	{
		"volk.h",
        "volk.c"
	}

	sysincludedirs
	{
		"../"
	}

	filter "system:windows"
		defines
		{
			"VK_USE_PLATFORM_WIN32_KHR"
		}

	filter "system:linux"
		defines
		{
			"VK_USE_PLATFORM_XCB_KHR"
		}
		buildoptions
    	{
    	  "-fPIC"
		}
	filter "system:macosx"
		defines
		{
			"VK_USE_PLATFORM_MACOS_MVK"
		}



	filter "configurations:Debug"
	symbols "On"

	filter "configurations:Release"
	optimize "On"

	filter "configurations:Dist"
	optimize "On"