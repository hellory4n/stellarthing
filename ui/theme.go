package ui

import (
	// mate
	gocolor "image/color"
	
	rl "github.com/gen2brain/raylib-go/raylib"
	"github.com/hellory4n/stellarthing/core"
)

// themes work as a bunch of callback things :)
// if you want to change the look of the stuff, just change the functions

var regularFont rl.Font
// shut up marge shut up
// var boldFont rl.Font
// var italicFont rl.Font

// sets up theme stuff
func LoadTheme() {
	// this is just the first 2 blocks of unicode
	chars := []rune("!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHI\nJKLMNOPQRSTUVWXYZ[]^_`abcdefghijklmn\nopqrstuvwxyz{|}~¡¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓ\nÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷\nøùúûüýþÿ")
	regularFont = rl.LoadFontEx("assets/Figtree/Figtree-Regular.ttf", 64, chars, 250)
	// shut up marge shut up
	// boldFont = rl.LoadFontEx("assets/Figtree/Figtree-Bold.ttf", 64, chars, 250)
	// italicFont = rl.LoadFontEx("assets/Figtree/Figtree-Italic.ttf", 64, chars, 250)

	// yeah
	rl.SetTextLineSpacing(16)
}

// similar to LoadTheme but in reverse
func FreeTheme() {
	rl.UnloadFont(regularFont)
	// shut up marge shut up
	// rl.UnloadFont(boldFont)
	// rl.UnloadFont(italicFont)
}

// as the name implies, it draws text
func DrawText(text string, pos core.Vec2, fontSize int, color core.Color) {
	rl.DrawTextEx(
		regularFont,
		text,
		rl.Vector2{X: float32(pos.X), Y: float32(pos.Y)},
		float32(fontSize),
		1,
		gocolor.RGBA{R: color.R, G: color.G, B: color.B, A: color.A},
	)
}