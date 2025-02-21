# Stellarthing

Space game.

Featuring a game engine in C++ (no STL)

## Building

You need GCC and Meson

First clone raylib:

```sh
cd subprojects
git clone https://github.com/raysan5/raylib
```

Compile with:

```sh
meson setup build
# actually compile
meson compile -C build
```

Cross-compilation to Windows is also supported:

```sh
meson setup --cross-file win32-cross-compile.ini build/win32
# actually compile
meson compile -C build/win32
```

If you're using Windows then good luck