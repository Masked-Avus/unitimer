workspace "unitimer"
    configurations { "Debug", "Release" }
    location "build/"

    project "unitimer"
        kind "None"
        location ("build/%{prj.name}/" .. _ACTION)
        language "C++"
        cppdialect "C++11"
        files "src/**.hpp"
        includedirs "src/"

    project "unitimer.tests"
        kind "ConsoleApp"
        location ("build/%{prj.name}/" .. _ACTION)
        objdir "obj/"
        targetname "%{prj.name}"
        targetdir "bin/%{prj.name}/%{cfg.buildcfg}"
        language "C++"
        cppdialect "C++11"
        files {
            "tests/**.hpp",
            "tests/**.cpp"
        }
        includedirs "src/"
