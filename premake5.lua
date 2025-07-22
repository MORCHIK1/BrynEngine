workspace "Brynhild"
    architecture "x64"
    configurations {"Debug", "Release", "Dist"}
    startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Brynhild"
    location "Brynhild"
    kind "SharedLib"
    language "C++"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }

    includedirs "%{prj.name}/vendor/spdlog/include"
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
        defines "BRYN_DEBUG"
        symbols "On"
    
    filter "configurations:Release"
        defines "BRYN_RELEASE"
        optimize "On"
        
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
        "Brynhild/src"
    }

    buildoptions "/utf-8"

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