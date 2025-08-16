project "glad"
	kind "StaticLib"
	language "C"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"include/glad/glad.h",
		"include/KHR/khrplatform.h",
		"src/glad.c"
	}

	includedirs
	{
		"include"
	}
    
    filter "system:windows"
        systemversion "latest"
        staticruntime "On"

    filter "configurations:Debug"
        symbols "on"
        runtime "Debug"
    
    filter "configurations:Release"
        optimize "on"
        runtime "Release"