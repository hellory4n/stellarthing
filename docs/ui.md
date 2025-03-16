# UI

I'm insane so I made my own immediate mode GUI too

## Themes

The theme system is quite simple. It's just a bunch of functions for drawing. (prefixed with `Draw`)

## Button

Buttons are essential for any UI. It's quite tricky to make one without buttons. Try making an UI without
buttons.

The Starry button can have multiple styles and calls a function when pressed

```go
ui.Button(x, y, w, h, "Quit Sibelius", ui.ButtonStyleSecondary, func() {
    os.Exit(0)
})
```

The styles are primary, secondary, and danger.

### Toggle button

If you just want to enable/disable something, you can use a toggle button

```go
enabled := false
ui.ToggleButton(x, y, w, h, "The toggle enables the tickbox that enables the button", &enabled)
```

### Cycle button

It's just a toggle button but with more options. How efficient.

```go
options := []string{"option 1", "option 2", "option 3"}
idx := 0
ui.CycleButton(x, y, w, h, &idx, options)
fmt.Println(options[idx])
```

## Slider

As the name implies, it slides.

```go
val := 0.0
ui.Slider(x, y, w, h, min, max, &val)
```

## Text input

You can type stuff too.

```go
text := ""
ui.TextInput(x, y, w, h, "placeholder", &text)
```