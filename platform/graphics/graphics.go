// useful for when you're not blind
package graphics

import (
	"fmt"
	"image/color"
	"math"

	rl "github.com/gen2brain/raylib-go/raylib"
	"github.com/hellory4n/stellarthing/core"
)

// the resolution the game uses. the game isn't actually rendered at this size, it's scaled
// with high DPI support
var RenderSize core.Vec2i

// scale for stuff
var scale float64 = 1
// not everything scales perfectly
var offset core.Vec2 = core.NewVec2(0, 0)
var windowSize core.Vec2i = core.NewVec2i(0, 0)

// clears the screen
func Clear(color core.Color) {
	// calculate scale
	width := rl.GetRenderWidth()
	height := rl.GetRenderHeight()
	windowSize = core.NewVec2i(int64(width), int64(height))

	scale = math.Min(
		float64(windowSize.X / RenderSize.X),
		float64(windowSize.Y / RenderSize.Y),
	)
	offset = core.NewVec2(
		// idfk anymore
		-((float64(windowSize.X) - (float64(RenderSize.X) * scale) * 0.5) / 2),
		-((float64(windowSize.Y) - (float64(RenderSize.Y) * scale) * 0.5) / 2),
	)
	fmt.Println("hehe")
	fmt.Println(windowSize)
	fmt.Println(scale)
	fmt.Println(offset)
	
	rl.BeginDrawing()
	rl.ClearBackground(rl.NewColor(color.R, color.G, color.B, color.A))
}

// transforms a position to fit the fake resolution
func TransformPos(pos core.Vec2) core.Vec2 {
	return core.NewVec2(
		(pos.X * scale) + offset.X,
		(pos.Y * scale) + offset.Y,
	)
}

// transforms a size to fit the fake resolution
func TransformSize(size core.Vec2) core.Vec2 {
	return core.NewVec2(
		size.X * scale,
		size.Y * scale,
	)
}

// as the name implies, it ends drawing
func EndDrawing() {
	rl.EndDrawing()
}

// this is utter insanity. srcPos and srcSize are used for cropping the image, dstPos and dstSize
// are the actual position and size, origin is a multiplier so (0, 0) is the top left, (0.5, 0.5)
// is the center, and (1, 1) is the bottom right. everything else is self-explanatory
func DrawTextureExt(texture Texture, srcPos core.Vec2, srcSize core.Vec2, dstPos core.Vec2,
dstSize core.Vec2, origin core.Vec2, angle float64, tint core.Color) {
	// scale :)
	dstPos = TransformPos(dstPos)
	dstSize = TransformSize(dstSize)

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
		core.NewVec2(0, 0), angle, color,
	)
}