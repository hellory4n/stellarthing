# Stellarthing

Space game.

Featuring a game engine in C99

## Building

Install raylib (`raylib-devel` on fedora, not sure if other distros have it)

Run `make && ./stellarthing`

Please note the C/C++ VS Code extension is dogwater, instead use clangd and then run
`bear -- make` (you may have to install bear) so everything works properly

You can also compile from linux to windows if you're insane:

1. step 1: install wine
2. step 2: [install raylib on wine](https://raysan5.itch.io/raylib/purchase)
3. step 3: run raylib installation/w64devkit.exe
4. step 4: compile the project like you would on linux