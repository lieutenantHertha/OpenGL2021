-- premake5.lua
workspace "OpenGL2021"
    configurations{"Debug", "Release"}
    architecture "x86_64"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Demo"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    location "%{wks.location}/Demo"

    targetdir ("%{wks.location}/bin/"..outputdir.."/%{prj.name}")
    objdir ("%{wks.location}/int-bin/"..outputdir.."/%{prj.name}")

    files
    {
        "%{prj.location}/src/*.h",
        "%{prj.location}/src/*.cpp",

        "%{prj.location}/src/vendor/**.h",
        "%{prj.location}/src/vendor/**.cpp",
        "%{prj.location}/src/vendor/**.hpp",
        "%{prj.location}/src/vendor/**.inl",

        "%{prj.location}/src/Tests/*.h",
        "%{prj.location}/src/Tests/*.cpp"
    }

    removefiles
    {
        "%{prj.location}/src/vendor/imgui/exampleRef.cpp"
    }

    defines
    {
        "GLEW_STATIC"
    }

    includedirs
    {
        "%{wks.location}/Dependencies/glew/include",
        "%{wks.location}/Dependencies/glfw/include",
        "%{prj.location}/src",
        "%{prj.location}/src/vendor",
        "%{prj.location}/src/Tests"
    }

    libdirs
    {
        "%{wks.location}/Dependencies/glew/lib/Release/x64",
        "%{wks.location}/Dependencies/glfw/lib-vc2019"
    }

    links
    {
        "glew32s.lib",
        "glfw3.lib",
        "opengl32.lib"
    }

    filter "configurations:Debug"
        defines "DEBUG"
        runtime "Debug"
        symbols "on"