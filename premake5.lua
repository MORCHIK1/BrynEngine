workspace "Brynhild"
    architecture "x64"
    configurations {"Debug", "Release", "Dist"}
    startproject "Sandbox"
    staticruntime "on"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDirectories = {}
IncludeDirectories["GLFW"] = "Brynhild/vendor/GLFW/include"
IncludeDirectories["glad"] = "Brynhild/vendor/glad/include"
IncludeDirectories["imgui"] = "Brynhild/vendor/imgui"
IncludeDirectories["glm"] = "Brynhild/vendor/glm"

include "Brynhild/vendor/GLFW"
include "Brynhild/vendor/glad"
include "Brynhild/vendor/imgui"

project "Brynhild"
    location "Brynhild"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "PreCompiledHeader.h"
    pchsource "Brynhild/src/PreCompiledHeader.cpp"

    files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }

    includedirs { 
      "%{prj.name}/vendor/spdlog/include", 
      "%{prj.name}/src", 
      "%{IncludeDirectories.GLFW}",
      "%{IncludeDirectories.glad}",
      "%{IncludeDirectories.imgui}",
      "%{IncludeDirectories.glm}"
    }
    links{
      "GLFW",
      "glad",
      "imgui",
      "opengl32.lib",
    }
    buildoptions "/utf-8"

    filter "system:windows"
        systemversion "latest"
        defines { "BRYN_PLATFORM_WINDOWS" }

    filter "configurations:Debug"
        defines { "BRYN_DEBUG", "BRYN_ENABLE_ASSERTS" }
        symbols "on" 
        runtime "Debug"
    
    filter "configurations:Release"
        defines "BRYN_RELEASE"
        optimize "on"
        runtime "Release"
        
    filter "configurations:Dist"
        defines "BRYN_DIST"
        optimize "on"
        runtime "Release"


project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }
    links { "Brynhild" }

    includedirs {
        "Brynhild/vendor/spdlog/include",
        "Brynhild/src",
        "Brynhild/vendor",
        "%{IncludeDirectories.glm}"
    }

    buildoptions "/utf-8"

    filter "system:windows"
        systemversion "latest"
        
        defines { "BRYN_PLATFORM_WINDOWS" }

    filter "configurations:Debug"
        defines "BRYN_DEBUG"
        symbols "on"
        runtime "Debug"
    
    filter "configurations:Release"
        defines "BRYN_RELEASE"
        optimize "on"
        runtime "Release"
        
    filter "configurations:Dist"
        defines "BRYN_DIST"
        optimize "on"
        runtime "Release"