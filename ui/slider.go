package ui

import (
	"github.com/hellory4n/stellarthing/core"
	"github.com/hellory4n/stellarthing/platform"
)

// makes a slider lol. writes into out
func Slider(pos core.Vec2, size core.Vec2, label string, min float64, max float64, out *float64) {
	// some extra padding in the hitbox so its less fucky
	sliderRect := core.NewRect(pos.X - 64, pos.Y, size.X + 64, size.Y)
	if sliderRect.HasPoint(platform.MousePosition()) {
		if platform.IsMouseButtonHeld(platform.MouseButtonLeft) {
			var t float64 = (platform.MousePosition().X - pos.X) / size.X
			*out = core.Clamp(min + t * (max - min), min, max)
		}
	}

	DrawSlider(pos, size, ((*out - min) / max) * 2)
}