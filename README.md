# Stellarthing (v1.1.0 dev)

## NOTE: This branch is in active development. It may be janky, or worse, busted. For stable versions, check other branches.

Space game.

Featuring a game engine in C99

## Building

### Linux

Make sure you have clang and make

Install raylib dependencies:

```sh
# ubuntu, debian, & company
sudo apt install libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev libwayland-dev libxkbcommon-dev

# fedora
sudo dnf install alsa-lib-devel mesa-libGL-devel libX11-devel libXrandr-devel libXi-devel libXcursor-devel libXinerama-devel libatomic

# arch
sudo pacman -S alsa-lib mesa libx11 libxrandr libxi libxcursor libxinerama
```

Run `make` from the project folder

Now you have the executable (`stellarthing`) on the project folder

Please note the C/C++ VS Code extension is dogwater, instead use clangd and then run
`bear -- make` (you may have to install bear) so everything works properly

I don't know how to setup cross-compilation (linux to windows/mac), for Windows just compile from wine, and I don't even know if it would work on Mac

### Windows

[Install raylib](https://raysan5.itch.io/raylib) (it comes with a compiler)

By default it installs to `C:\raylib`

Run `C:\raylib\w64devkit\w64devkit.exe`

Go to the project folder (if you don't speak terminal it's `cd [project folder]` with no brackets)

Run `make`

Now you have the executable (`stellarthing.exe`) on the project folder
