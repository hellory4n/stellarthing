// useful for when you're not blind
package graphics

import (
	"image/color"

	rl "github.com/gen2brain/raylib-go/raylib"
	"github.com/hellory4n/stellarthing/core"
)

// clears the screen
func Clear(color core.Color) {
	rl.BeginDrawing()
	rl.ClearBackground(rl.NewColor(color.R, color.G, color.B, color.A))
}

// as the name implies, it ends drawing
func EndDrawing() {
	rl.EndDrawing()
}

// this is utter insanity. srcPos and srcSize are used for cropping the image, dstPos and dstSize are the actual position and size, origin is a multiplier so (0, 0) is the top left, (0.5, 0.5) is the center, and (1, 1) is the bottom right. everything else is self-explanatory
func DrawTextureExt(texture Texture, srcPos core.Vec2, srcSize core.Vec2, dstPos core.Vec2, dstSize core.Vec2, origin core.Vec2, angle float64, tint core.Color) {
	rl.DrawTexturePro(
		rl.Texture2D{
			ID: texture.id,
			Width: texture.width,
			Height: texture.height,
			Format: texture.format,
			Mipmaps: texture.mipmaps,
		},
		rl.Rectangle{X: float32(srcPos.X), Y:  float32(srcPos.Y), Width: float32(srcSize.X), Height: float32(srcSize.Y)},
		rl.Rectangle{X: float32(dstPos.X), Y:  float32(dstPos.Y), Width: float32(dstSize.X), Height: float32(dstSize.Y)},
		rl.Vector2{X: float32(origin.X * dstSize.X), Y: float32(origin.Y * dstSize.Y)},
		float32(angle),
		color.RGBA{R: tint.R, G: tint.G, B: tint.B, A: tint.A},
	)
}

// draws a texture. if you want a comically large parameter list use DrawTextureExt instead
func DrawTexture(texture Texture, pos core.Vec2, angle float64, color core.Color) {
	DrawTextureExt(
		texture, core.NewVec2(0, 0), texture.Size().ToVec2(), pos, texture.Size().ToVec2(),
		core.NewVec2(0.5, 0.5), angle, color,
	)
}