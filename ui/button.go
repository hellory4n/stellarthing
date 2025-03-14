// ui :)
package ui

import (
	"fmt"

	rl "github.com/gen2brain/raylib-go/raylib"
	"github.com/hellory4n/stellarthing/core"
	"github.com/hellory4n/stellarthing/platform"
)

type ButtonStyle int

const (
	ButtonStylePrimary ButtonStyle = iota
	ButtonStyleSecondary
	ButtonStyleDanger
)

// makes a button :)
func Button(x, y, w, h float64, text string, style ButtonStyle, onPressed func()) {
	// center text :)
	var textSize rl.Vector2 = rl.MeasureTextEx(boldFont, text, float32(DefaultFontSize), 1)
	var textPos core.Vec2 = core.Vec2{
		(w / 2) - (float64(textSize.X) / 2),
		(h / 2) - (float64(textSize.Y) / 2),
	}
	var textColor core.Color = core.ColorWhite

	// base texture
	switch style {
	case ButtonStylePrimary:
		DrawPrimaryButton(core.Vec2{x, y}, core.Vec2{w, h})
	case ButtonStyleSecondary:
		DrawSecondaryButton(core.Vec2{x, y}, core.Vec2{w, h})
	case ButtonStyleDanger:
		DrawDangerButton(core.Vec2{x, y}, core.Vec2{w, h})
	default:
		panic("MATE\n")
	}

	// is it focused?
	buttonRect := core.Rect{x, y, w, h}
	if buttonRect.HasPoint(platform.MousePosition()) {
		DrawHoverOutline(core.Vec2{x, y}, core.Vec2{w, h})

		// and is it pressed?
		if platform.IsMouseButtonJustReleased(platform.MouseButtonLeft) {
			onPressed()
		}
		// different mouse thingy so its not highlighted for 1 frame
		if platform.IsMouseButtonHeld(platform.MouseButtonLeft) {
			textColor = core.ColorBlack
			DrawPressedButton(core.Vec2{x, y}, core.Vec2{w, h})
		}
	}

	// finally draw text :)
	DrawBoldText(text, textPos.Add(core.Vec2{x, y}), DefaultFontSize, textColor)
}

// it's a button that toggles. writes the result into out
func ToggleButton(x, y, w, h float64, text string, out *bool) {
	if *out {
		Button(x, y, w, h, fmt.Sprintf("%s: on", text), ButtonStylePrimary, func() {
			*out = false
		})
	} else {
		Button(x, y, w, h, fmt.Sprintf("%s: off", text), ButtonStyleSecondary, func() {
			*out = true
		})
	}
}

// it's a button that cycles. writes the index into current
func CycleButton(x, y, w, h float64, current *int, options ...string) {
	Button(x, y, w, h, options[*current], ButtonStyleSecondary, func() {
		*current++
		if *current >= len(options) {
			*current = 0
		}
	})
}
