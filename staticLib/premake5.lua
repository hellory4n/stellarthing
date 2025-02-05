baseName = path.getbasename(os.getcwd());

project (baseName)
    kind "StaticLib"
    location "./"
    targetdir "../bin/%{cfg.buildcfg}"

    vpaths 
    {
        ["Header Files/*"] = { "include/**.h", "include/**.hpp", "**.h", "**.hpp"},
        ["Source Files/*"] = { "src/**.cpp", "src/**.c", "**.cpp","**.c"},
    }
    files {"**.hpp", "**.h", "**.cpp","**.c"}

    includedirs { "./" }
    includedirs { "./src" }
    includedirs { "./include" }

    include_raylib()