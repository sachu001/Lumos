IncludeDir = {}
IncludeDir["GLFW"] = "external/glfw/include/"
IncludeDir["Glad"] = "external/glad/include/"
IncludeDir["lua"] = "external/lua/src/"
IncludeDir["stb"] = "external/stb/"
IncludeDir["OpenAL"] = "external/OpenAL/include/"
IncludeDir["Box2D"] = "external/box2d/include/"
IncludeDir["external"] = "external/"
IncludeDir["vulkan"] = "external/vulkan/"
IncludeDir["Lumos"] = "src"
IncludeDir["External"] = "external/"
IncludeDir["ImGui"] = "external/imgui/"
IncludeDir["freetype"] = "external/freetype/include"
IncludeDir["SpirvCross"] = "external/SPIRV-Cross"
IncludeDir["cereal"] = "external/cereal/include"
IncludeDir["spdlog"] = "external/spdlog/include"

project "Lumos"
	kind "StaticLib"
	language "C++"
	editandcontinue "Off"

	files
	{
		"src/**.h",
		"src/**.c",
		"src/**.cpp"
	}

	removefiles
	{
		"src/Platform/**"
	}

	includedirs
	{
		"../",
		"src/",
		"",
		"../src/"
	}

	sysincludedirs
	{
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.lua}",
		"%{IncludeDir.stb}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.OpenAL}",
		"%{IncludeDir.Box2D}",
		"%{IncludeDir.vulkan}",
		"%{IncludeDir.external}",
		"%{IncludeDir.External}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.freetype}",
		"%{IncludeDir.SpirvCross}",
		"%{IncludeDir.cereal}",
		"%{IncludeDir.Lumos}",
	}

	links
	{
		"lua",
		"box2d",
		"imgui",
		"freetype",
		"SpirvCross"
	}

	defines
	{
		"LUMOS_ENGINE",
		"FREEIMAGE_LIB",
		"LUMOS_DYNAMIC",
		"LUMOS_ROOT_DIR="  .. root_dir,
	"IMGUI_USER_CONFIG=\"src/ImGui/ImConfig.h\"",
	"LUMOS_PROFILE",
	"TRACY_ENABLE",
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "on"
		systemversion "latest"

		pchheader "Precompiled.h"
		pchsource "src/Precompiled.cpp"

		defines
		{
			"LUMOS_PLATFORM_WINDOWS",
			"LUMOS_RENDER_API_OPENGL",
			"LUMOS_RENDER_API_VULKAN",
			"VK_USE_PLATFORM_WIN32_KHR",
			"WIN32_LEAN_AND_MEAN",
			"_CRT_SECURE_NO_WARNINGS",
			"_DISABLE_EXTENDED_ALIGNED_STORAGE",
			"_SILENCE_CXX17_OLD_ALLOCATOR_MEMBERS_DEPRECATION_WARNING",
			"_SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING",
			"LUMOS_IMGUI",
			"LUMOS_OPENAL",
			"LUMOS_VOLK",
			"USE_VMA_ALLOCATOR",
			"LUMOS_SSE"
		}

		files
		{
			"src/Platform/Windows/*.h",
			"src/Platform/Windows/*.cpp",

			"src/Platform/GLFW/*.h",
			"src/Platform/GLFW/*.cpp",

			"src/Platform/OpenAL/*.h",
			"src/Platform/OpenAL/*.cpp",

			"src/Platform/OpenGL/*.h",
			"src/Platform/OpenGL/*.cpp",

			"src/Platform/Vulkan/*.h",
			"src/Platform/Vulkan/*.cpp",

			"external/glad/src/glad_wgl.c"
		}

		links
		{
			"glfw",
		}

		buildoptions
		{
			"/MP", "/bigobj"
		}
		disablewarnings { 4307 }

		characterset ("MBCS")

		filter 'files:external/**.cpp'
			flags  { 'NoPCH' }
		filter 'files:external/**.c'
			flags  { 'NoPCH' }

	filter "system:macosx"
		cppdialect "C++17"
		systemversion "latest"

		files
		{
			"src/Platform/macOS/*.mm",
			"src/Platform/macOS/*.h",
			"src/Platform/macOS/*.cpp",

			"src/Platform/Unix/*.h",
			"src/Platform/Unix/*.cpp",

			"src/Platform/GLFW/*.h",
			"src/Platform/GLFW/*.cpp",

			"src/Platform/OpenAL/*.h",
			"src/Platform/OpenAL/*.cpp",

			"src/Platform/OpenGL/*.h",
			"src/Platform/OpenGL/*.cpp",

			"src/Platform/Vulkan/*.h",
			"src/Platform/Vulkan/*.cpp"
		}

		defines
		{
			"LUMOS_PLATFORM_MACOS",
			"LUMOS_PLATFORM_UNIX",
			"LUMOS_RENDER_API_OPENGL",
			"LUMOS_RENDER_API_VULKAN",
			"VK_USE_PLATFORM_METAL_EXT",
			"LUMOS_IMGUI",
			"LUMOS_OPENAL",
			"LUMOS_VOLK",
			"USE_VMA_ALLOCATOR",
			"LUMOS_SSE"
		}

		links
		{
			"QuartzCore.framework",
			"Metal.framework",
			"Cocoa.framework",
        	"IOKit.framework",
        	"CoreFoundation.framework",
			"CoreVideo.framework",
			"OpenAL.framework",
			"SystemConfiguration.framework",
			"glfw"
		}

		libdirs
		{
			"../bin/**"
		}

		buildoptions
		{
			"-Wno-attributes",
	"-Wno-nullability-completeness",
	"-fdiagnostics-absolute-paths"
		}

		SetRecommendedXcodeSettings()

pchheader "../Lumos/src/Precompiled.h"
pchsource "../Lumos/src/Precompiled.cpp"

		filter 'files:external/**.cpp'
			flags  { 'NoPCH' }
		filter 'files:external/**.c'
			flags  { 'NoPCH' }
		filter 'files:src/**.m'
			flags  { 'NoPCH' }
		filter 'files:src/**.mm'
			flags  { 'NoPCH' }

	filter "system:ios"
		cppdialect "C++17"
		systemversion "latest"
		kind "StaticLib"

		defines
		{
			"LUMOS_PLATFORM_IOS",
			"LUMOS_PLATFORM_MOBILE",
			"LUMOS_PLATFORM_UNIX",
			"LUMOS_RENDER_API_VULKAN",
			"VK_USE_PLATFORM_IOS_MVK",
			"LUMOS_IMGUI",
			"USE_VMA_ALLOCATOR",
			"LUMOS_OPENAL"
		}

		files
		{
			"src/Platform/iOS/*.mm",
			"src/Platform/iOS/*.h",
			"src/Platform/iOS/*.cpp",

			"src/Platform/OpenAL/*.h",
			"src/Platform/OpenAL/*.cpp",

			"src/Platform/Unix/*.h",
			"src/Platform/Unix/*.cpp",

			"src/Platform/Vulkan/*.h",
			"src/Platform/Vulkan/*.cpp"
		}

		removefiles
		{
			"src/Platform/Unix/UnixFileSystem.cpp"
		}

		links
		{
			"QuartzCore.framework",
			"Metal.framework",
        	"IOKit.framework",
        	"CoreFoundation.framework",
			"CoreVideo.framework",
			"OpenAL.framework"
		}

		libdirs
		{
			"../bin/**"
		}

		buildoptions
		{
			"-Wno-attributes",
			"-Wno-nullability-completeness"
		}

		SetRecommendedXcodeSettings()

	filter "system:linux"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"LUMOS_PLATFORM_LINUX",
			"LUMOS_PLATFORM_UNIX",
			"LUMOS_RENDER_API_OPENGL",
			"LUMOS_RENDER_API_VULKAN",
			"VK_USE_PLATFORM_XCB_KHR",
			"LUMOS_IMGUI",
			"LUMOS_VOLK"
		}

		files
		{
			"src/Platform/Unix/*.h",
			"src/Platform/Unix/*.cpp",

			"src/Platform/GLFW/*.h",
			"src/Platform/GLFW/*.cpp",

			"src/Platform/OpenAL/*.h",
			"src/Platform/OpenAL/*.cpp",

			"src/Platform/OpenGL/*.h",
			"src/Platform/OpenGL/*.cpp",

			"src/Platform/Vulkan/*.h",
			"src/Platform/Vulkan/*.cpp"
		}

		links
		{
			"glfw"
		}

		linkoptions
		{
			"external/OpenAL/libs/linux/libopenal.so"
		}

		linkoptions{ "-Wl,-rpath=\\$$ORIGIN" }

		libdirs
		{
			"../bin/**"
		}

		buildoptions
		{
			"-fpermissive",
			"-fPIC",
			"-Wignored-attributes",
			"-Wno-psabi"
		}

		links { "X11", "pthread"}

		pchheader "../Lumos/src/Precompiled.h"
		pchsource "../Lumos/src/Precompiled.cpp"

		filter 'files:external/**.cpp'
			flags  { 'NoPCH' }
		filter 'files:external/**.c'
			flags  { 'NoPCH' }
		filter 'files:src/**.c'
			flags  { 'NoPCH' }

		if _OPTIONS["arch"] ~= "arm" then
			buildoptions
			{
				"-msse4.1",
			}

			defines { "LUMOS_SSE" ,"USE_VMA_ALLOCATOR"}
		end

	filter "configurations:Debug"
		defines { "LUMOS_DEBUG", "_DEBUG" }
		symbols "On"
		runtime "Debug"

	filter "configurations:Release"
		defines "LUMOS_RELEASE"
		optimize "On"
		symbols "On"
		runtime "Release"

		filter "configurations:Production"
		defines "LUMOS_PRODUCTION"
		symbols "Off"
		optimize "Full"
		runtime "Release"
