package player

import (
	"github.com/hellory4n/stellarthing/core"
	"github.com/hellory4n/stellarthing/platform"
	"github.com/hellory4n/stellarthing/platform/graphics"
	"github.com/hellory4n/stellarthing/tile"
	"github.com/hellory4n/stellarthing/ui"
)

func (p *Player) initHotbar() {
	// default hotbar crap or smth
	p.hotbar[0] = tile.Tile{TileId: tile.BlueGuy}
	p.hotbar[1] = tile.Tile{TileId: tile.GreenGuy}
	p.hotbar[2] = tile.Tile{TileId: tile.Life}
}

func (p *Player) updateHotbar() {
	// THE GREAT HOTBAR FUCKERY
	if platform.IsKeyJustPressed(platform.KeyNum1) {
		p.currentHotbarIdx = 0
	}
	if platform.IsKeyJustPressed(platform.KeyNum2) {
		p.currentHotbarIdx = 1
	}
	if platform.IsKeyJustPressed(platform.KeyNum3) {
		p.currentHotbarIdx = 2
	}
	if platform.IsKeyJustPressed(platform.KeyNum4) {
		p.currentHotbarIdx = 3
	}
	if platform.IsKeyJustPressed(platform.KeyNum5) {
		p.currentHotbarIdx = 4
	}
	if platform.IsKeyJustPressed(platform.KeyNum6) {
		p.currentHotbarIdx = 5
	}
	if platform.IsKeyJustPressed(platform.KeyNum7) {
		p.currentHotbarIdx = 6
	}
	if platform.IsKeyJustPressed(platform.KeyNum8) {
		p.currentHotbarIdx = 7
	}
	if platform.IsKeyJustPressed(platform.KeyNum9) {
		p.currentHotbarIdx = 8
	}

	// place the bloody tiles
	// this is sad
	// here at shell we are sad
	pos := tile.ThisWorld.ScreenToTile(platform.MousePosition(), core.Vec2i{64, 64})
	if platform.IsMouseButtonJustPressed(platform.MouseButtonLeft) {
		if p.hotbar[p.currentHotbarIdx].TileId != tile.Air {
			if tile.ThisWorld.GetTile(pos, true) == nil {
				tile.ThisWorld.NewTile(pos, true, p.hotbar[p.currentHotbarIdx].TileId,
					p.hotbar[p.currentHotbarIdx].EntityRef, p.hotbar[p.currentHotbarIdx].Variation)
			} else if tile.ThisWorld.GetTile(pos, true).TileId == tile.Air {
				*tile.ThisWorld.GetTile(pos, true) = p.hotbar[p.currentHotbarIdx]
			} else if tile.ThisWorld.GetTile(pos, false) == nil {
				tile.ThisWorld.NewTile(pos, false, p.hotbar[p.currentHotbarIdx].TileId,
					p.hotbar[p.currentHotbarIdx].EntityRef, p.hotbar[p.currentHotbarIdx].Variation)
			} else if tile.ThisWorld.GetTile(pos, false).TileId == tile.Air {
				*tile.ThisWorld.GetTile(pos, false) = p.hotbar[p.currentHotbarIdx]
			}
		}
	}

	// you can also remove the bloody tiles
	// this is also sad
	// here at shell we are still sad
	if platform.IsMouseButtonJustPressed(platform.MouseButtonRight) {
		// PLEASE FUCKING WORK
		if tile.ThisWorld.GetTile(pos, false) != nil {
			if tile.ThisWorld.GetTile(pos, false).TileId == tile.Air {
				if tile.ThisWorld.GetTile(pos, true) != nil {
					tile.ThisWorld.GetTile(pos, true).TileId = tile.Air
					return
				}
			}
		}

		if tile.ThisWorld.GetTile(pos, false) != nil {
			tile.ThisWorld.GetTile(pos, false).TileId = tile.Air
			return
		}
		if tile.ThisWorld.GetTile(pos, true) != nil {
			tile.ThisWorld.GetTile(pos, true).TileId = tile.Air
			return
		}
	}
}

func (p *Player) drawHotbar() {
	// hover tiles and shit
	pos := tile.ThisWorld.ScreenToTile(platform.MousePosition(), core.Vec2i{64, 64})
	graphics.DrawTexture(
		graphics.LoadTexture("assets/highlight.png"),
		tile.ThisWorld.TileToScreen(pos, core.Vec2i{64, 64}),
		0, core.ColorWhite,
	)

	// hot-bloody-bar
	// abso-bloody-lutely
	var x float64 = 8
	for i := range 9 {
		if p.currentHotbarIdx == i {
			ui.DrawPrimaryButton(core.Vec2{x, float64(core.RenderSize.Y) - 80 - 8}, core.Vec2{80, 80})
		} else {
			ui.DrawSecondaryButton(core.Vec2{x, float64(core.RenderSize.Y) - 80 - 8}, core.Vec2{80, 80})
		}

		// icon
		graphics.DrawTexture(
			graphics.LoadTexture(tile.Tiles[p.hotbar[i].TileId][0].Texture),
			core.Vec2{x + 8, float64(core.RenderSize.Y) - 80 - 1},
			0, core.ColorWhite,
		)

		x += 80 + 8
	}
}
