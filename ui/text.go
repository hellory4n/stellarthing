package ui

import (
	rl "github.com/gen2brain/raylib-go/raylib"
	"github.com/hellory4n/stellarthing/core"
	"github.com/hellory4n/stellarthing/platform"
)

// single-line text input. please note it's very barebones (not good). writes whatever the user wrote to out
func TextInput(pos core.Vec2, size core.Vec2, placeholder string, out *string) {
	// vertical centering
	var textSize rl.Vector2
	if *out == "" {
		textSize = rl.MeasureTextEx(boldFont, placeholder, float32(DefaultFontSize), 1)
	} else {
		textSize = rl.MeasureTextEx(boldFont, *out, float32(DefaultFontSize), 1)
	}
	var textY float64 = (size.Y / 2) - (float64(textSize.Y) / 2)

	DrawTextInput(pos, size)

	// mate
	rect := core.NewRect(pos.X, pos.Y, size.X, size.Y)
	if rect.HasPoint(platform.MousePosition()) {
		DrawHoverOutline(pos, size)
		// bullshit i did to see if it stops fucking with player input
		core.FocusedTextField = out
	}

	// text.
	rl.BeginScissorMode(int32(pos.X), int32(pos.Y), int32(size.X), int32(size.Y))
	if *out == "" {
		DrawRegularText(placeholder, core.NewVec2(pos.X + 8, pos.Y + textY),
			DefaultFontSize, core.Rgba(255, 255, 255, 127))
	} else {
		DrawRegularText(*out, core.NewVec2(pos.X + 8, pos.Y + textY), DefaultFontSize, core.ColorWhite)
	}
	rl.EndScissorMode()
}

func UpdateInputFieldsFrfrfrThisTime() {
	if core.FocusedTextField == nil {
		return
	}

	// apparently the character thingy is a queue
	var key int32 = rl.GetCharPressed()
	for key > 0 {
		// you can't write control characters
		// TODO: unicode has more control character than that
		if key >= 32 {
			*core.FocusedTextField += string(key)
		}

		// next character
		key = rl.GetCharPressed()
	}

	// we all mank mistakes
	if platform.IsKeyJustPressed(platform.KeyBackspace) && len(*core.FocusedTextField) > 0 {
		// we do this fuckery so you dont remove half a character
		thingyButInRunes := []rune(*core.FocusedTextField)
		thingyButInRunes = (thingyButInRunes)[:len(thingyButInRunes) - 1]
		*core.FocusedTextField = string(thingyButInRunes)
	}
}