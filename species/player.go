package species

import (
	"fmt"
	"time"

	"github.com/hellory4n/stellarthing/core"
	// "github.com/hellory4n/stellarthing/core/bobx"
	"github.com/hellory4n/stellarthing/entities"
	"github.com/hellory4n/stellarthing/platform"
	"github.com/hellory4n/stellarthing/platform/graphics"
	"github.com/hellory4n/stellarthing/ui"
)

const speed float64 = 5

type Player struct {
	tile *graphics.Tile
	tileData *graphics.TileData
	currentHotbarIdx int
	hotbarTiles [9]graphics.TileId
}

// type LaData struct {
// 	Thingy string
// }

func (p *Player) EntityType() entities.EntityType {
	return entities.EntityTypeGameWorld
}

func (p *Player) OnCreate(entity entities.EntityRef) {
	fmt.Println("Good morning.")

	platform.AddKeymap("move_left", platform.KeyA)
	platform.AddKeymap("move_left", platform.KeyLeft)
	platform.AddKeymap("move_right", platform.KeyD)
	platform.AddKeymap("move_right", platform.KeyRight)
	platform.AddKeymap("move_up", platform.KeyW)
	platform.AddKeymap("move_up", platform.KeyUp)
	platform.AddKeymap("move_down", platform.KeyS)
	platform.AddKeymap("move_down", platform.KeyDown)

	world := graphics.NewTileWorld(core.NewVec2i(-250, -250), core.NewVec2i(250, 250), time.Now().UnixNano())
	graphics.CurrentWorld = world

	p.tile = graphics.CurrentWorld.NewTile(core.NewVec3i(0, 0, 0), false, graphics.TileBobGuy,
		entity, graphics.VariationId(entity))
	p.tileData = p.tile.GetData()
	p.tileData.Position = core.NewVec3(15, 0, 0)
	graphics.CurrentWorld.SetCameraPosition(p.tileData.Position)
	p.tileData.UsingCustomPos = true

	// default hotbar crap or smth
	p.hotbarTiles[0] = graphics.TileGreenGuy
	p.hotbarTiles[1] = graphics.TileBlueGuy
	p.hotbarTiles[2] = graphics.TileLife

	// uuuuuy, _ := bobx.Open(filepath.Join(core.GetUserDir(), "test"))
	// var sogmaballs LaData
	// uuuuuy.Read("mate.json", LaData{Thingy: "Oi mate"}, &sogmaballs)
	// fmt.Println(sogmaballs.Thingy)
}

func (p *Player) OnUpdate(entity entities.EntityRef, delta float64) {
	// move.
	if platform.IsKeymapHeld("move_left") {
		p.tileData.Position = p.tileData.Position.Add(core.NewVec3(-speed * delta, 0, 0))
	}

	if platform.IsKeymapHeld("move_right") {
		p.tileData.Position = p.tileData.Position.Add(core.NewVec3(speed * delta, 0, 0))
	}

	if platform.IsKeymapHeld("move_up") {
		p.tileData.Position = p.tileData.Position.Add(core.NewVec3(0, -speed * delta, 0))
	}

	if platform.IsKeymapHeld("move_down") {
		p.tileData.Position = p.tileData.Position.Add(core.NewVec3(0, speed * delta, 0))
	}
	graphics.CurrentWorld.SetCameraPosition(p.tileData.Position)

	// THE GREAT HOTBAR FUCKERY
	if platform.IsKeyJustPressed(platform.KeyNum1) { p.currentHotbarIdx = 0 }
	if platform.IsKeyJustPressed(platform.KeyNum2) { p.currentHotbarIdx = 1 }
	if platform.IsKeyJustPressed(platform.KeyNum3) { p.currentHotbarIdx = 2 }
	if platform.IsKeyJustPressed(platform.KeyNum4) { p.currentHotbarIdx = 3 }
	if platform.IsKeyJustPressed(platform.KeyNum5) { p.currentHotbarIdx = 4 }
	if platform.IsKeyJustPressed(platform.KeyNum6) { p.currentHotbarIdx = 5 }
	if platform.IsKeyJustPressed(platform.KeyNum7) { p.currentHotbarIdx = 6 }
	if platform.IsKeyJustPressed(platform.KeyNum8) { p.currentHotbarIdx = 7 }
	if platform.IsKeyJustPressed(platform.KeyNum9) { p.currentHotbarIdx = 8 }
}

func (p *Player) OnGui(entity entities.EntityRef) {
}

func (p *Player) OnDraw(entity entities.EntityRef) {
	ui.DrawRegularText("wasd to move\n1-9 to change hotbar crap\nleft click to place\nright click to break\nf3 shows some crap",
		core.NewVec2(950, 500), ui.DefaultFontSize, core.ColorWhite)

	// hot-bloody-bar
	// abso-bloody-lutely
	var x float64 = 8
	for i := range 9 {
		if p.currentHotbarIdx == i {
			ui.DrawPrimaryButton(core.NewVec2(x, float64(core.RenderSize.Y) - 80 - 8), core.NewVec2(80, 80))
		} else {
			ui.DrawSecondaryButton(core.NewVec2(x, float64(core.RenderSize.Y) - 80 - 8), core.NewVec2(80, 80))
		}

		// icon
		graphics.DrawTexture(
			graphics.LoadTexture(graphics.Tiles[p.hotbarTiles[i]][0].Texture),
			core.NewVec2(x + 8, float64(core.RenderSize.Y) - 80 - 1),
			0, core.ColorWhite,
		)

		x += 80 + 8
	}
}

func (p *Player) OnFree(entity entities.EntityRef) {
	fmt.Println("rip")
}