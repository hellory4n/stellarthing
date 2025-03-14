package ui

import (
	"github.com/hellory4n/stellarthing/core"
	"github.com/hellory4n/stellarthing/platform"
)

// makes a slider lol. writes into out
func Slider(x, y, w, h float64, label string, min float64, max float64, out *float64) {
	// some extra padding in the hitbox so its less fucky
	sliderRect := core.Rect{x - 64, y, w + 64, y}
	if sliderRect.HasPoint(platform.MousePosition()) {
		if platform.IsMouseButtonHeld(platform.MouseButtonLeft) {
			var t float64 = (platform.MousePosition().X - x) / w
			*out = core.Clamp(min+t*(max-min), min, max)
		}
	}

	DrawSlider(core.Vec2{x, y}, core.Vec2{w, h}, ((*out-min)/max)*2)
}
