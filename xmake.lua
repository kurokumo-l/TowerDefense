add_rules("mode.debug", "mode.release")

set_toolchains("msvc")
set_languages("cxx23")

target("TowerDefense")
    set_kind("binary")

    add_includedirs(
        "include", 
        "include/Manager",
        "dep/cJSON/include",
        "dep/SDL2/include", 
        "dep/SDL2_gfx/include",
        "dep/SDL2_image/include", 
        "dep/SDL2_mixer/include",
        "dep/SDL2_ttf/include"
    )

    add_files("src/*.cpp", "src/Manager/*.cpp", "dep/cJSON/src/*.c")

    add_ldflags("/subsystem:console")
    add_cxflags("/utf-8")

    add_syslinks("shell32")
    add_links(
        "dep/SDL2/lib/x64/SDL2", 
        "dep/SDL2/lib/x64/SDL2main",
        "dep/SDL2_gfx/lib/x64/SDL2_gfx", 
        "dep/SDL2_image/lib/x64/SDL2_image",
        "dep/SDL2_mixer/lib/x64/SDL2_mixer", 
        "dep/SDL2_ttf/lib/x64/SDL2_ttf"
    )

    add_linkdirs(
        "dep/SDL2/lib/x64", 
        "dep/SDL2_gfx/lib/x64",
        "dep/SDL2_image/lib/x64",
        "dep/SDL2_mixer/lib/x64",
        "dep/SDL2_ttf/lib/x64"
    )

    after_build(function(target)
        local output_dir = target:targetdir()
        os.cp("dep/**/x64/*.dll", output_dir)

        local output_res_dir = path.join(output_dir, "res")
        if not os.isdir(output_res_dir) then 
            os.mkdir(output_res_dir)
        end
        os.cp("res/**", output_res_dir, {root = "res"})
    end)



