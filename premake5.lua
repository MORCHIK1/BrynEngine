workspace "Brynhild"
    architecture "x64"
    configurations {"Debug", "Release", "Dist"}
    startproject "Sandbox"
    staticruntime "off"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDirectories = {}
IncludeDirectories["GLFW"] = "Brynhild/vendor/GLFW/include"
IncludeDirectories["glad"] = "Brynhild/vendor/glad/include"
IncludeDirectories["imgui"] = "Brynhild/vendor/imgui"

include "Brynhild/vendor/GLFW"
include "Brynhild/vendor/glad"
include "Brynhild/vendor/imgui"

project "Brynhild"
    location "Brynhild"
    kind "SharedLib"
    language "C++"
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
      "%{IncludeDirectories.imgui}"
    }
    links{
      "GLFW",
      "glad",
      "imgui",
      "opengl32.lib",
      "user32.lib",
      "gdi32.lib",
      "shell32.lib"
    }
    buildoptions "/utf-8"

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"
        
        defines { "BRYN_PLATFORM_WINDOWS", "BRYN_BUILD_DLL" }
        
        postbuildcommands {
            ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
        }

    filter "configurations:Debug"
        defines { "BRYN_DEBUG", "BRYN_ENABLE_ASSERTS" }
        symbols "On" 
        runtime "Debug"
    
    filter "configurations:Release"
        defines "BRYN_RELEASE"
        optimize "On"
        runtime "Release"
        
    filter "configurations:Dist"
        defines "BRYN_DIST"
        optimize "On"
        runtime "Release"


project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }
    links { "Brynhild" }

    includedirs {
        "Brynhild/vendor/spdlog/include",
        "Brynhild/src",
    }

    buildoptions "/utf-8"

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"
        
        defines { "BRYN_PLATFORM_WINDOWS" }

    filter "configurations:Debug"
        defines "BRYN_DEBUG"
        symbols "On"
        runtime "Debug"
    
    filter "configurations:Release"
        defines "BRYN_RELEASE"
        optimize "On"
        runtime "Release"
        
    filter "configurations:Dist"
        defines "BRYN_DIST"
        optimize "On"
        runtime "Release"