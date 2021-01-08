project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"%{wks.location}/SGUI/vendor/spdlog/include",
		"%{wks.location}/SGUI/src",
		"%{wks.location}/SGUI/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}"
	}

	links
	{
		"SGUI"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "SG_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "SG_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "SG_DIST"
		runtime "Release"
		optimize "on"
