workspace "Brynhild"
    architecture "x64"
    configurations {"Debug", "Release", "Dist"}
    startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDirectories = {}
IncludeDirectories["GLFW"] = "Brynhild/vendor/GLFW/include"

include "Brynhild/vendor/GLFW"

project "Brynhild"
    location "Brynhild"
    kind "SharedLib"
    language "C++"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "PreCompiledHeader.h"
    pchsource "Brynhild/src/PreCompiledHeader.cpp"

    files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }

    includedirs { "%{prj.name}/vendor/spdlog/include", "%{prj.name}/src", "%{IncludeDirectories.GLFW}" }
    links{
      "GLFW",
      "opengl32.lib",
      "user32.lib",
      "gdi32.lib",
      "shell32.lib"
    }
    buildoptions "/utf-8"

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "on"
        systemversion "latest"
        
        defines { "BRYN_PLATFORM_WINDOWS", "BRYN_BUILD_DLL" }
        
        postbuildcommands {
            ("{COPYFILE} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines { "BRYN_DEBUG", "BRYN_ENABLE_ASSERTS" }
        symbols "On" 
        staticruntime "off"
        runtime "Debug"
    
    filter "configurations:Release"
        defines "BRYN_RELEASE"
        optimize "On"
        runtime "Release"
        
    filter "configurations:Dist"
        defines "BRYN_DIST"
        optimize "On"

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
        staticruntime "on"
        systemversion "latest"
        
        defines { "BRYN_PLATFORM_WINDOWS" }

    filter "configurations:Debug"
        defines "BRYN_DEBUG"
        symbols "On"
    
    filter "configurations:Release"
        defines "BRYN_RELEASE"
        optimize "On"
        
    filter "configurations:Dist"
        defines "BRYN_DIST"
        optimize "On"