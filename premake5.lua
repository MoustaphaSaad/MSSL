workspace "MSSL"
    configurations {"Debug", "Release"}
    platforms {"x86", "x86_64"}
    location "build"
    startproject "Test"

project "MSSL"
    kind "SharedLib"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"

    files {"inc/**.h", "src/**.cpp"}

    includedirs {"inc/"}

    buildoptions {"-std=c++11"}

    filter "configurations:Debug"
        defines {"DEBUG", "COMPILE_DLL"}
        flags {"Symbols"}

    filter "configurations:Release"
        defines {"NDEBUG", "COMPILE_DLL"}
        optimize "On"

    filter "platforms:x86"
        architecture "x86"

    filter "platforms:x86_64"
        architecture "x86_64"

project "Test"
    kind "ConsoleApp"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"

    files {"test/**.h", "test/**.cpp"}

    includedirs {"inc/"}

    links {"MSSL"}

    buildoptions {"-std=c++11"}

    filter "configurations:Debug"
        defines {"DEBUG"}
        flags {"Symbols"}

    filter "configurations:Release"
        defines {"NDEBUG"}
        optimize "On"

    filter "platforms:x86"
        architecture "x86"

    filter "platforms:x86_64"
        architecture "x86_64"
