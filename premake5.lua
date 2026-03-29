workspace "Log-Puller"
    architecture "x64"
    configurations { "Debug", "Release" }
    location "build"

filter "system:windows"
    toolset "gcc"

filter "system:linux"
    toolset "gcc"

filter "system:macosx"
    toolset "clang"

project "Log-Puller"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++23"

    targetdir ("bin/%{cfg.buildcfg}")
    objdir ("bin-int/%{cfg.buildcfg}")

    files {
        "src/**.cpp",
        "include/**.h"
    }

    includedirs {
        "include",
        "vendor"
    }

    filter "configurations:Debug"
        symbols "On"

    filter "configurations:Release"
        optimize "On"
