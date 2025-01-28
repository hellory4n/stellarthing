# Stellarthing

A game about space things

# Starry Engine

starry is the next biggest ever replacement of unity unreal godot game maker cryengine frostbite source 2 rpg maker lumberyard defold panda3d flax monogame libgdx ogre bevy phaser armory gdevelop cocos2d renpy urho3d stride haxeflixel pygame blender game engine fucking idk

best game engine in the world awards 1921 winner

10th best game engine when it comes to usability awards 3000 BC winner

## Epic features
- Modern C#
- Overkill graphics (it uses [skia](https://skia.org/) (but [the c# version](https://github.com/mono/SkiaSharp)))
- Acceptable math structs
- Assets work
- Async await everywhere
- Esoteric tilemap
- Blazingly fast and very handsome entity system
- Sick sound effect and music system
- COMING SOON: Acceptable UI
- COMING SOON: Modding through lua

# How to build

First you need the .NET 8 SDK

To release:
```sh
# idk how it goes on windows
dotnet publish --os win -c Release --sc
dotnet publish --os linux -c Release --sc
```

It's somewhere in `stellarthing/bin/Release/` then the publish folder

If you're using windows you can try [this tutorial](https://www.google.com/search?q=how+to+install+linux)