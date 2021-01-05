workspace"SGUI"
  architecture "x64"

  configurations
  {
  	  "Debug",
	  "Release"
  }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
IncludeDir = {}
IncludeDir["GLFW"] = "SGUI/vendor/GLFW/include"
IncludeDir["Glad"] = "SGUI/vendor/Glad/include"
IncludeDir["ImGui"] = "SGUI/vendor/imgui"
IncludeDir["glm"] = "SGUI/vendor/glm"
IncludeDir["stb_image"] = "SGUI/vendor/stb_image"

include "SGUI/vendor/GLFW"
include "SGUI/vendor/Glad"
include "SGUI/vendor/imgui"


project "SGUI"
  location "SGUI"
  kind "StaticLib"
  language "C++"
  cppdialect "C++17"
  staticruntime "on"
  systemversion "latest"

  targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
  objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")


  files
  {
  	  "%{prj.name}/Src/**.h",
	  "%{prj.name}/Src/**.cpp",
      "%{prj.name}/vendor/glm/glm/**.hpp",
      "%{prj.name}/vendor/glm/glm/**.inl",
      "%{prj.name}/vendor/stb_image/**.cpp",
      "%{prj.name}/vendor/stb_image/**.h"
  }

  includedirs
  {
      "%{prj.name}/Src",
  	  "%{prj.name}/vendor/spdlog/include",
	  "%{IncludeDir.GLFW}",
      "%{IncludeDir.Glad}",
      "%{IncludeDir.ImGui}",
      "%{IncludeDir.glm}",
      "%{IncludeDir.stb_image}"
  }

  links
  {
  	  "GLFW",
      "Glad",
      "ImGui",
	  "opengl32.lib"
  }

  defines
  {
  	  "SG_PLATFORM_WINDOW",
	  "SG_ENABLE_ASSERTS",
      "GLFW_INCLUDE_NONE"
  }

  filter "configurations:Debug"
    defines "SG_DEBUG"
	symbols "on"
   
  filter "configurations:Release"
    defines "SG_Release"
	optimize  "on"

project "Sandbox"
   location "Sandbox"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++17"
   staticruntime "on"
   systemversion "latest"

   targetdir ("bin/" ..outputdir.. "/%{prj.name}")
   objdir ("bin-int/" ..outputdir.. "/%{prj.name}")
   
   files
   {
       "%{prj.name}/Src/**.h",
	   "%{prj.name}/Src/**.cpp",
       "%{prj.name}/GameTest/**.h",
	   "%{prj.name}/GameTest/**.cpp"
   }

   includedirs
   {
       "SGUI/Src",
	   "SGUI/vendor/spdlog/include",
       "SGUI/vendor/imgui",
       "%{IncludeDir.glm}"
   }

   links
   {
   	   "SGUI"
   }

   defines
   {
   	   "SG_PLATFORM_WINDOW"
   }
   filter "configurations:Debug"
     defines "SG_DEBUG"
	 symbols "on"
   filter "configurations:Release"
     defines "SG_Release"
	 optimize  "on"