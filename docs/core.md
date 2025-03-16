# Core

Starry features handsome features.

## Math

There's vectors

```go
vecma2 := core.Vec2{1.0, 2.0}
vecma3 := core.Vec3{1.0, 2.0, 3.0}

// integer variant
vecma2i := core.Vec2i{1, 2}
vecma3i := core.Vec3i{1, 2, 3}
```

There's colors too

The reason I didn't just use `image/color` is because I didn't know it existed

```go
asdfjjfjsjgskgallgklsgh := core.Rgba(255, 255, 255, 255)
```

Rectangle.

```go
the := core.Rect{1, 2, 30, 40}
```

## Utilities

### Debug mode

Displays a bunch of bullshit into your eyeballs.

Press F3 to see it.

### Timer

As the name implies, it's a timer

Example:

```go
// the bool part is whether it should loop
timer := core.NewTimer(5, false)
timer.Timeout = func() {
    fmt.Println("OH WOULD YOU LOOK AT THE TIME")
    fmt.Println("ITS TIME TO LEAVE")
}
timer.Start()
```

### Benchmark

I don't know why this exists.

```go
b := core.NewBenchmark()

// do some bullshit

// also prints how many milliseconds that took
b.Stop()
```