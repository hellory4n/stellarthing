package graphics

import (
	"fmt"

	rl "github.com/gen2brain/raylib-go/raylib"
	"github.com/hellory4n/stellarthing/core"
)

// texture :)
type Texture struct {
	// these are used for converting to raylib textures
	id      uint32
	width   int32
	height  int32
	mipmaps int32
	format  rl.PixelFormat
	path    string
}

var textureCache map[string]Texture

func init() {
	textureCache = make(map[string]Texture)
}

// supported formats are PNG, BMP, TGA, JPG, GIF, QOI, PSD, DDS, HDR, KTX, ASTC, PKM, and PVR
func LoadTexture(path string) Texture {
	texture, ok := textureCache[path]
	if !ok {
		var txddrx rl.Texture2D = rl.LoadTexture(core.AssetPath(path))
		texture = Texture{
			id:      txddrx.ID,
			width:   txddrx.Width,
			height:  txddrx.Height,
			mipmaps: txddrx.Mipmaps,
			format:  txddrx.Format,
			path:    path,
		}
		textureCache[path] = texture
		fmt.Printf("[GRAPHICS] Loaded texture at %v\n", path)
	}
	return texture
}

// returns the size of the texture in pixels
func (t Texture) Size() core.Vec2i {
	return core.Vec2i{int64(t.width), int64(t.height)}
}

// frees the texture and removes it from the cache. if you want to reload the texture, use this
func (t Texture) Free() {
	var rltltx rl.Texture2D = rl.Texture2D{
		ID:      t.id,
		Width:   t.width,
		Height:  t.height,
		Mipmaps: t.mipmaps,
		Format:  t.format,
	}
	rl.UnloadTexture(rltltx)
	delete(textureCache, t.path)
	fmt.Printf("[GRAPHICS] Freed texture at %v\n", t.path)
}

func FreeAllTextures() {
	for _, v := range textureCache {
		v.Free()
	}
}
