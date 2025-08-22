project "slang"
	kind "StaticLib"
	language "C++"
    cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/")
	objdir ("bin-int/")

	files
	{
		"include/**.h",
	}
	includedirs
	{
		"include"
	}

    filter "system:windows"
        systemversion "latest"
        staticruntime "On"

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
        links { "slangd" }

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
        links { "slang" }