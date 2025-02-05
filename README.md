# Starry C

Got a random segfault in C#, C is great because all of your segfaults are your own skill issue

## Building

premake.

you can also compile from linux to windows if you're insane

1. step 1: install wine
2. step 2: install w64devkit on wine
3. step 3: run w64devkit.exe
4. step 4: compile the project like you would on linux

you can release stuff with these commands: (you have to generate makefiles first)


```sh
make config=release_x64
# arm is supported, i just don't know anyone with an arm pc
# (apple silicon and raspberry pi doesn't count, mac isn't supported and why would you run this on a raspberry pi)
make config=release_arm64
```
