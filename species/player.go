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
	hotbar [9]graphics.Tile
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
	p.hotbar[0] = graphics.Tile{TileId: graphics.TileBlueGuy}
	p.hotbar[1] = graphics.Tile{TileId: graphics.TileGreenGuy}
	p.hotbar[2] = graphics.Tile{TileId: graphics.TileLife}

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

	// place the bloody tiles
	// this is sad
	// here at shell we are sad
	pos := graphics.CurrentWorld.ScreenToTile(platform.MousePosition(), core.NewVec2i(64, 64))
	if platform.IsMouseButtonJustPressed(platform.MouseButtonLeft) {
		if p.hotbar[p.currentHotbarIdx].TileId != graphics.TileAir {
			if graphics.CurrentWorld.GetTile(pos, true) == nil {
				graphics.CurrentWorld.NewTile(pos, true, p.hotbar[p.currentHotbarIdx].TileId,
					p.hotbar[p.currentHotbarIdx].EntityRef, p.hotbar[p.currentHotbarIdx].Variation)
			} else if graphics.CurrentWorld.GetTile(pos, true).TileId == graphics.TileAir {
				*graphics.CurrentWorld.GetTile(pos, true) = p.hotbar[p.currentHotbarIdx]
			} else if graphics.CurrentWorld.GetTile(pos, false) == nil {
				graphics.CurrentWorld.NewTile(pos, false, p.hotbar[p.currentHotbarIdx].TileId,
					p.hotbar[p.currentHotbarIdx].EntityRef, p.hotbar[p.currentHotbarIdx].Variation)
			} else if graphics.CurrentWorld.GetTile(pos, false).TileId == graphics.TileAir {
				*graphics.CurrentWorld.GetTile(pos, false) = p.hotbar[p.currentHotbarIdx]
			}
		}
	}

	// you can also remove the bloody tiles
	// this is also sad
	// here at shell we are still sad
	if platform.IsMouseButtonJustPressed(platform.MouseButtonRight) {
		// PLEASE FUCKING WORK
		if graphics.CurrentWorld.GetTile(pos, false) != nil {
			if graphics.CurrentWorld.GetTile(pos, false).TileId == graphics.TileAir {
				if graphics.CurrentWorld.GetTile(pos, true) != nil {
					graphics.CurrentWorld.GetTile(pos, true).TileId = graphics.TileAir
					return
				}
			}
		}

		if graphics.CurrentWorld.GetTile(pos, false) != nil {
			graphics.CurrentWorld.GetTile(pos, false).TileId = graphics.TileAir
			return
		}
		if graphics.CurrentWorld.GetTile(pos, true) != nil {
			graphics.CurrentWorld.GetTile(pos, true).TileId = graphics.TileAir
			return
		}
	}
}

func (p *Player) OnGui(entity entities.EntityRef) {
}

func (p *Player) OnDraw(entity entities.EntityRef) {
	// hover tiles and shit
	pos := graphics.CurrentWorld.ScreenToTile(platform.MousePosition(), core.NewVec2i(64, 64))
	graphics.DrawTexture(
		graphics.LoadTexture("assets/highlight.png"),
		graphics.CurrentWorld.TileToScreen(pos, core.NewVec2i(64, 64)),
		0, core.ColorWhite,
	)

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
			graphics.LoadTexture(graphics.Tiles[p.hotbar[i].TileId][0].Texture),
			core.NewVec2(x + 8, float64(core.RenderSize.Y) - 80 - 1),
			0, core.ColorWhite,
		)

		x += 80 + 8
	}
}

func (p *Player) OnFree(entity entities.EntityRef) {
	fmt.Println("rip")
}