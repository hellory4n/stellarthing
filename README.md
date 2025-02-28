# Stellarthing

Space game.

Featuring a game engine in Go

## Building

If you're using Windows then good luck

Install dependencies:

```sh
# ubuntu
sudo apt-get install libgl1-mesa-dev libxi-dev libxcursor-dev libxrandr-dev libxinerama-dev libwayland-dev libxkbcommon-dev -y
# fedora
sudo dnf install mesa-libGL-devel libXi-devel libXcursor-devel libXrandr-devel libXinerama-devel wayland-devel libxkbcommon-devel -y
```

Run:

```sh
go run .
```