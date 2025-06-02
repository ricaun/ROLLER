const std = @import("std");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});

    const sdl_image = b.dependency("SDL_image", .{
        .target = target,
        .optimize = optimize,
    });
    const sdl_image_lib = sdl_image.artifact("SDL3_image");

    const sdl = b.dependency("sdl", .{
        .target = target,
        .optimize = optimize,
        .lto = optimize != .Debug,
    });
    const sdl_lib = sdl.artifact("SDL3");

    const exe_mod = b.createModule(.{
        .target = target,
        .optimize = optimize,
        .link_libc = true,
    });
    exe_mod.linkLibrary(sdl_lib);
    exe_mod.linkLibrary(sdl_image_lib);

    exe_mod.addCSourceFiles(.{
        .files = &.{
            "PROJECTS/ROLLER/3d.c",
            "PROJECTS/ROLLER/building.c",
            "PROJECTS/ROLLER/car.c",
            "PROJECTS/ROLLER/carplans.c",
            "PROJECTS/ROLLER/cdx.c",
            "PROJECTS/ROLLER/colision.c",
            "PROJECTS/ROLLER/comms.c",
            "PROJECTS/ROLLER/control.c",
            "PROJECTS/ROLLER/date.c",
            "PROJECTS/ROLLER/drawtrk3.c",
            "PROJECTS/ROLLER/engines.c",
            "PROJECTS/ROLLER/frontend.c",
            "PROJECTS/ROLLER/func2.c",
            "PROJECTS/ROLLER/func3.c",
            "PROJECTS/ROLLER/function.c",
            "PROJECTS/ROLLER/graphics.c",
            "PROJECTS/ROLLER/horizon.c",
            "PROJECTS/ROLLER/loadtrak.c",
            "PROJECTS/ROLLER/mouse.c",
            "PROJECTS/ROLLER/moving.c",
            "PROJECTS/ROLLER/network.c",
            "PROJECTS/ROLLER/plans.c",
            "PROJECTS/ROLLER/polyf.c",
            "PROJECTS/ROLLER/polytex.c",
            "PROJECTS/ROLLER/replay.c",
            "PROJECTS/ROLLER/sound.c",
            "PROJECTS/ROLLER/svgacpy.c",
            "PROJECTS/ROLLER/tower.c",
            "PROJECTS/ROLLER/transfrm.c",
            "PROJECTS/ROLLER/userfns.c",
            "PROJECTS/ROLLER/view.c",
        },
    });

    switch (target.result.os.tag) {
        .windows => {},
        else => {
            exe_mod.addCMacro("__int16", "int16");
            exe_mod.addCMacro("_O_RDONLY", "O_RDONLY");
            exe_mod.addCMacro("_O_BINARY", "0x200");
        },
    }

    const exe = b.addExecutable(.{
        .name = "roller",
        .root_module = exe_mod,
    });
    exe.want_lto = optimize != .Debug;

    b.installArtifact(exe);

    const run_cmd = b.addRunArtifact(exe);
    run_cmd.step.dependOn(b.getInstallStep());
    run_cmd.setCwd(b.path("fatdata"));

    if (b.args) |args| {
        run_cmd.addArgs(args);
    }

    const run_step = b.step("run", "Run the app");
    run_step.dependOn(&run_cmd.step);
}
