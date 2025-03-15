package player

import (
	"fmt"

	"github.com/hellory4n/stellarthing/core"
	"github.com/hellory4n/stellarthing/entity"
	"github.com/hellory4n/stellarthing/platform"
	"github.com/hellory4n/stellarthing/tile"
	"github.com/hellory4n/stellarthing/ui"
)

const speed float64 = 5

type Player struct {
	tile             *tile.Tile
	tileData         *tile.TileData
	currentHotbarIdx int
	hotbar           [9]tile.Tile
}

func (p *Player) EntityType() entity.Type {
	return entity.TypeGameWorld
}

func (p *Player) OnCreate(ent entity.Ref) {
	fmt.Println("Good morning.")

	platform.AddKeymap("move_left", platform.KeyA)
	platform.AddKeymap("move_left", platform.KeyLeft)
	platform.AddKeymap("move_right", platform.KeyD)
	platform.AddKeymap("move_right", platform.KeyRight)
	platform.AddKeymap("move_up", platform.KeyW)
	platform.AddKeymap("move_up", platform.KeyUp)
	platform.AddKeymap("move_down", platform.KeyS)
	platform.AddKeymap("move_down", platform.KeyDown)

	p.initHotbar()
	p.setupSave(ent)
}

func (p *Player) OnUpdate(ent entity.Ref, delta float64) {
	// move.
	var move core.Vec3
	if platform.IsKeymapHeld("move_left") {
		move = core.Vec3{-speed * delta, 0, 0}
	}
	if platform.IsKeymapHeld("move_right") {
		move = core.Vec3{speed * delta, 0, 0}
	}
	if platform.IsKeymapHeld("move_up") {
		move = core.Vec3{0, -speed * delta, 0}
	}
	if platform.IsKeymapHeld("move_down") {
		move = core.Vec3{0, speed * delta, 0}
	}
	p.tileData.Position = tile.ThisWorld.Collide(p.tileData.Position, move)
	tile.ThisWorld.SetCameraPosition(p.tileData.Position)

	p.updateHotbar()
}

func (p *Player) OnGui(ent entity.Ref) {}

func (p *Player) OnDraw(ent entity.Ref) {
	p.drawHotbar()

	ui.DrawRegularText(
		`wasd to move
		1-9 to change hotbar crap
		left click to place
		right click to break
		f3 shows some crap
		restart to test saving pls`,
		core.Vec2{950, 500}, ui.DefaultFontSize, core.ColorWhite,
	)
}

func (p *Player) OnFree(ent entity.Ref) {
	// just in case
	p.saveTilemap()
}
