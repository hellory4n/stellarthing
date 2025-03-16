# Platform

I'm just gonna give a bunch of examples, it's not that hard

## Show a texture

```go
// textures are put in a cache to be blazingly fast
// so you could run this every frame and the game wouldn't die
texture := platform.LoadTexture("assets/1000_soviet_children_marching_towards_the_sun.png")

// for more pain and destruction use DrawTextureExt
platform.DrawTexture(texture, core.Vec2{50, 60}, 180, core.ColorWhite)
```

## Input

```go
// you can use autocomplete to see what else is available
if platform.IsKeyJustPressed(platform.KeyJ) {
    fmt.Println("J")
}
```

### Keymaps

Keymaps allow you map multiple keys for the same action, or let users change bindings and stuff.

```go
// setup
platform.AddKeymap("death_and_destruction", platform.KeyK)
platform.AddKeymap("death_and_destruction", platform.KeySpace)

// now you can check stuff
if platform.IsKeymapJustPressed("death_and_destruction") {
    panic("SO I LEARNED TO TURN AND LOOK THE OTHER WAY")
}
```

## Audio

Quite useful for when you're not deaf.

```go
// audio is also in a cache
likeifrealtable := audio.Load("assets/1000_soviet_children_marching_towards_the_sun.mp3")
likeifrealtable.Play()
```

Directional audio is supported too

```go
audio.SetListener(somewhere)
likeifrealtable.SetPosition(somewhereElse)
```