# Stellarthing

Space game.

Featuring a game engine in C++ (no STL)

## Building

Install clang and cmake and stuff (you can probably use gcc but clang is recommended)

You need some dependencies for raylib to work:

Ubuntu:
```sh
sudo apt install libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev libwayland-dev libxkbcommon-dev
```

Fedora:
```sh
sudo dnf install alsa-lib-devel mesa-libGL-devel libX11-devel libXrandr-devel libXi-devel libXcursor-devel libXinerama-devel libatomic
```

Arch Linux:
```sh
sudo pacman -S alsa-lib mesa libx11 libxrandr libxi libxcursor libxinerama
```

Void Linux:
```sh
sudo xbps-install alsa-lib-devel libglvnd-devel libX11-devel libXrandr-devel libXi-devel libXcursor-devel libXinerama-devel mesa MesaLib-devel mesa-dri mesa-intel-dri
```

On Windows you can probably use [Raylib's Windows installer](https://raysan5.itch.io/raylib)

Now setup CMake:

```sh
cmake -B build
# or setup for debug mode
cmake -DCMAKE_BUILD_TYPE=Debug -B build
```

And compile with:

```sh
cmake --build build
```

The executable will be in `build/stellarthing/stellarthing`

Also if you're using vscode, don't use the Microsoft C/C++ extension, use clangd instead (it's better)

## Cross-compiling

Compiling from Linux to Windows is supported too

First install MinGW and MinGW GCC (look it up in your distro)

Then setup with:

```sh
cmake -B build/windows -DCMAKE_TOOLCHAIN_FILE=cmake_win32.cmake
```

And compile with:

```sh
cmake --build build/windows
```

The executable will be in `build/windows/stellarthing/stellarthing.exe`