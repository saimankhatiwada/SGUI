include "./vendor/premake/premake_customization/solution_items.lua"

workspace "SGUI"
	architecture "x86_64"
	startproject "Synthesia-Editor"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/SGUI/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/SGUI/vendor/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/SGUI/vendor/imgui"
IncludeDir["glm"] = "%{wks.location}/SGUI/vendor/glm"
IncludeDir["stb_image"] = "%{wks.location}/SGUI/vendor/stb_image"
IncludeDir["entt"] = "%{wks.location}/SGUI/vendor/entt/include"
IncludeDir["yaml_cpp"] = "%{wks.location}/SGUI/vendor/yaml-cpp/include"
IncludeDir["ImGuizmo"] = "%{wks.location}/SGUI/vendor/ImGuizmo"

group "Dependencies"
	include "vendor/premake"
	include "SGUI/vendor/GLFW"
	include "SGUI/vendor/Glad"
	include "SGUI/vendor/imgui"
	include "SGUI/vendor/yaml-cpp"
group ""

include "SGUI"
include "Sandbox"
include "Synthesia-Editor"
