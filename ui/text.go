package ui

import (
	rl "github.com/gen2brain/raylib-go/raylib"
	"github.com/hellory4n/stellarthing/core"
	"github.com/hellory4n/stellarthing/platform"
)

// single-line text input. please note it's very barebones (not good). writes whatever the user wrote to out
func TextInput(x, y, w, h float64, placeholder string, out *string) {
	// vertical centering
	var textSize rl.Vector2
	if *out == "" {
		textSize = rl.MeasureTextEx(boldFont, placeholder, float32(DefaultFontSize), 1)
	} else {
		textSize = rl.MeasureTextEx(boldFont, *out, float32(DefaultFontSize), 1)
	}
	var textY float64 = (w / 2) - (float64(textSize.Y) / 2)

	DrawTextInput(core.Vec2{x, y}, core.Vec2{w, h})

	// mate
	rect := core.Rect{x, y, w, h}
	if rect.HasPoint(platform.MousePosition()) {
		DrawHoverOutline(core.Vec2{x, y}, core.Vec2{w, h})
		// bullshit i did to see if it stops fucking with player input
		core.InternalInputFieldFocus = true

		// apparently the character thingy is a queue
		var key int32 = rl.GetCharPressed()
		for key > 0 {
			// you can't write control characters
			// TODO: unicode has more control character than that
			if key >= 32 {
				*out += string(key)
			}

			// next character
			key = rl.GetCharPressed()
		}

		// we all mank mistakes
		if platform.IsKeyJustPressed(platform.KeyBackspace) && len(*out) > 0 {
			// we do this fuckery so you dont remove half a character
			thingyButInRunes := []rune(*out)
			thingyButInRunes = (thingyButInRunes)[:len(thingyButInRunes)-1]
			*out = string(thingyButInRunes)
		}
	}

	// text.
	rl.BeginScissorMode(int32(x), int32(y), int32(w), int32(h))
	if *out == "" {
		DrawRegularText(placeholder, core.Vec2{x + 8, y + textY},
			DefaultFontSize, core.Rgba(255, 255, 255, 127))
	} else {
		DrawRegularText(*out, core.Vec2{x + 8, y + textY}, DefaultFontSize, core.ColorWhite)
	}
	rl.EndScissorMode()
}
