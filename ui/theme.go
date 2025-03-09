package ui

import (
	// it can get fucky
	gocolor "image/color"

	rl "github.com/gen2brain/raylib-go/raylib"
	"github.com/hellory4n/stellarthing/core"
)

// themes work as a bunch of callback things :)
// if you want to change the look of the stuff, just change the functions

// yeah
const DefaultFontSize int = 26
// yeah
const Separation int = 8
// yeah
const ButtonHeight float64 = 40

var regularFont rl.Font
var boldFont rl.Font
var italicFont rl.Font

// sets up theme stuff
func LoadTheme() {
	// this is just the first 2 blocks of unicode
	chars := []rune("!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHI\nJKLMNOPQRSTUVWXYZ[]^_`abcdefghijklmn\nopqrstuvwxyz{|}~¡¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓ\nÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷\nøùúûüýþÿ")
	regularFont = rl.LoadFontEx("assets/Figtree/Figtree-Regular.ttf", 64, chars, 250)
	boldFont = rl.LoadFontEx("assets/Figtree/Figtree-Bold.ttf", 64, chars, 250)
	italicFont = rl.LoadFontEx("assets/Figtree/Figtree-Italic.ttf", 64, chars, 250)

	// yeah
	rl.SetTextLineSpacing(16)
}

// similar to LoadTheme but in reverse
func FreeTheme() {
	rl.UnloadFont(regularFont)
	rl.UnloadFont(boldFont)
	rl.UnloadFont(italicFont)
}

// as the name implies, it draws regular text
func DrawRegularText(text string, pos core.Vec2, fontSize int, color core.Color) {
	rl.DrawTextEx(
		regularFont,
		text,
		rl.Vector2{X: float32(pos.X), Y: float32(pos.Y)},
		float32(fontSize),
		1,
		gocolor.RGBA{R: color.R, G: color.G, B: color.B, A: color.A},
	)
}

// as the name implies, it draws bold text
func DrawBoldText(text string, pos core.Vec2, fontSize int, color core.Color) {
	rl.DrawTextEx(
		boldFont,
		text,
		rl.Vector2{X: float32(pos.X), Y: float32(pos.Y)},
		float32(fontSize),
		1,
		gocolor.RGBA{R: color.R, G: color.G, B: color.B, A: color.A},
	)
}

// as the name implies, it draws italic text
func DrawItalicText(text string, pos core.Vec2, fontSize int, color core.Color) {
	rl.DrawTextEx(
		italicFont,
		text,
		rl.Vector2{X: float32(pos.X), Y: float32(pos.Y)},
		float32(fontSize),
		1,
		gocolor.RGBA{R: color.R, G: color.G, B: color.B, A: color.A},
	)
}

// as the name implies, it draws a primary button
func DrawPrimaryButton(pos core.Vec2, size core.Vec2) {
	rl.DrawRectangleRounded(
		rl.NewRectangle(float32(pos.X), float32(pos.Y), float32(size.X), float32(size.Y)),
		0.4, 4, gocolor.RGBA{0x7c, 0x4d, 0xff, 0xff},
	)
	rl.DrawRectangleRoundedLinesEx(
		rl.NewRectangle(float32(pos.X), float32(pos.Y), float32(size.X), float32(size.Y)),
		0.4, 4, 2, gocolor.RGBA{0x7b, 0x1f, 0xa2, 0xff},
	)
}

// as the name implies, it draws a secondary button
func DrawSecondaryButton(pos core.Vec2, size core.Vec2) {
	rl.DrawRectangleRounded(
		rl.NewRectangle(float32(pos.X), float32(pos.Y), float32(size.X), float32(size.Y)),
		0.4, 4, gocolor.RGBA{0x26, 0x09, 0x2b, 0xff},
	)
	rl.DrawRectangleRoundedLinesEx(
		rl.NewRectangle(float32(pos.X), float32(pos.Y), float32(size.X), float32(size.Y)),
		0.4, 4, 2, gocolor.RGBA{0x12, 0x04, 0x14, 0xff},
	)
}

// as the name implies, it draws a danger button
func DrawDangerButton(pos core.Vec2, size core.Vec2) {
	rl.DrawRectangleRounded(
		rl.NewRectangle(float32(pos.X), float32(pos.Y), float32(size.X), float32(size.Y)),
		0.4, 4, gocolor.RGBA{0xf4, 0x43, 0x36, 0xff},
	)
	rl.DrawRectangleRoundedLinesEx(
		rl.NewRectangle(float32(pos.X), float32(pos.Y), float32(size.X), float32(size.Y)),
		0.4, 4, 2, gocolor.RGBA{0xd3, 0x2f, 0x2f, 0xff},
	)
}

// as the name implies, it draws a text input
func DrawTextInput(pos core.Vec2, size core.Vec2) {
	rl.DrawRectangleRounded(
		rl.NewRectangle(float32(pos.X), float32(pos.Y), float32(size.X), float32(size.Y)),
		0.4, 4, gocolor.RGBA{0x12, 0x04, 0x14, 0xff},
	)
	rl.DrawRectangleRoundedLinesEx(
		rl.NewRectangle(float32(pos.X), float32(pos.Y), float32(size.X), float32(size.Y)),
		0.4, 4, 2, gocolor.RGBA{0x26, 0x09, 0x2b, 0xff},
	)
}

// draw on top of a button/text input when it's focused
func DrawHoverOutline(pos core.Vec2, size core.Vec2) {
	rl.DrawRectangleRoundedLinesEx(
		rl.NewRectangle(float32(pos.X), float32(pos.Y), float32(size.X), float32(size.Y)),
		0.4, 4, 2, gocolor.RGBA{0xff, 0xff, 0xff, 0xff},
	)
}

// this is used for every button when pressed because i'm lazy
func DrawPressedButton(pos core.Vec2, size core.Vec2) {
	rl.DrawRectangleRounded(
		rl.NewRectangle(float32(pos.X), float32(pos.Y), float32(size.X), float32(size.Y)),
		0.4, 4, gocolor.RGBA{0xff, 0xff, 0xff, 0x55},
	)
}

// slider. grabber is on a range from 0 to 1
func DrawSlider(pos core.Vec2, size core.Vec2, grabber float64) {
	// background
	rl.DrawRectangleRounded(
		rl.NewRectangle(float32(pos.X), float32(pos.Y + (size.Y / 4)), float32(size.X), float32(size.Y / 2)),
		1, 12, gocolor.RGBA{0x26, 0x09, 0x2b, 0xff},
	)
	rl.DrawRectangleRoundedLinesEx(
		rl.NewRectangle(float32(pos.X), float32(pos.Y + (size.Y / 4)), float32(size.X), float32(size.Y / 2)),
		1, 12, 2, gocolor.RGBA{0x12, 0x04, 0x14, 0xff},
	)

	// grabber
	// im sorry... im sorry... im sorry...
	rl.DrawRectangleRounded(
		rl.NewRectangle(float32(core.Clamp(pos.X + (size.X * grabber) - size.Y / 1.75, 0 + size.Y / 2, size.X - size.Y / 2)), float32(pos.Y), float32(size.Y), float32(size.Y)),
		1, 12, gocolor.RGBA{0x7c, 0x4d, 0xff, 0xff},
	)
	rl.DrawRectangleRoundedLinesEx(
		rl.NewRectangle(float32(core.Clamp(pos.X + (size.X * grabber) - size.Y / 1.75, 0 + size.Y / 2, size.X - size.Y / 2)), float32(pos.Y), float32(size.Y), float32(size.Y)),
		1, 12, 2, gocolor.RGBA{0x7b, 0x1f, 0xa2, 0xff},
	)
}

// it's just a dark background
func DrawDialog(pos core.Vec2, size core.Vec2) {
	rl.DrawRectangleRounded(
		rl.NewRectangle(float32(pos.X), float32(pos.Y), float32(size.X), float32(size.Y)),
		0, 1, gocolor.RGBA{0x00, 0x00, 0x00, 0x77},
	)
	rl.DrawRectangleRoundedLinesEx(
		rl.NewRectangle(float32(pos.X), float32(pos.Y), float32(size.X), float32(size.Y)),
		0, 1, 2, gocolor.RGBA{0xff, 0xff, 0xff, 0x45},
	)
}