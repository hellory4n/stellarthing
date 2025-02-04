# Starry C

Got a random segfault in C#, C is great because all of your segfaults are your own skill issue

## Building

If you're using Windows then good luck lmao

First you need GCC and Make and stuff.

Then you have to install some libraries

On Fedora it's

```sh
sudo dnf install glfw glfw-devel glew glew-devel mesa-libGL mesa-libGL-devel mesa-libGLU-devel -y
```

GLAD requires [generating header files](https://glad.dav1d.de/#language=c&specification=gl&api=gl%3D3.3&api=gles1%3Dnone&api=gles2%3Dnone&api=glsc2%3Dnone&profile=core&loader=on&localfiles=on) (just click generate and download the `.h` files) and then putting them in your `/usr/include/glad`

Now you can compile and run with:

```sh
make && ./bin/stellarthing
```

Compiling to Windows requires MinGW

```sh
sudo dnf install mingw64-gcc
make windows
```