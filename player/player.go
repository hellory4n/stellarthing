package player

import (
	"fmt"

	"github.com/hellory4n/stellarthing/core"
	"github.com/hellory4n/stellarthing/entity"
	"github.com/hellory4n/stellarthing/platform"
	"github.com/hellory4n/stellarthing/tile"
	"github.com/hellory4n/stellarthing/ui"
)

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
	var speed float64
	if platform.IsKeyHeld(platform.KeyLeftControl) {
		speed = 35
	} else {
		speed = 5
	}

	// move.
	var move core.Vec3
	if platform.IsKeymapHeld("move_left") {
		move = move.Add(core.Vec3{-1, 0, 0})
	}
	if platform.IsKeymapHeld("move_right") {
		move = move.Add(core.Vec3{1, 0, 0})
	}
	if platform.IsKeymapHeld("move_up") {
		move = move.Add(core.Vec3{0, -1, 0})
	}
	if platform.IsKeymapHeld("move_down") {
		move = move.Add(core.Vec3{0, 1, 0})
	}
	// death and destructio n
	p.tileData.Position = tile.ThisWorld.Collide(p.tileData.Position, move.Normalize().Smul(speed).Smul(delta))
	tile.ThisWorld.SetCameraPosition(p.tileData.Position)

	p.updateHotbar()

	// zoom in/out :)
	if platform.GetScroll() > 0.9 {
		tile.ThisWorld.CameraScale = tile.ThisWorld.CameraScale.Smul(1.5)
	} else if platform.GetScroll() < -0.9 {
		tile.ThisWorld.CameraScale = tile.ThisWorld.CameraScale.Sdiv(1.5)
	}
}

func (p *Player) OnGui(ent entity.Ref) {}

func (p *Player) OnDraw(ent entity.Ref) {
	p.drawHotbar()

	ui.DrawRegularText(
		`wasd to move
1-9 to change hotbar crap
left click to place
right click to break
scroll to zoom
hold ctrl to get really fast
f3 shows some crap
restart to test saving pls`,
		core.Vec2{950, 500}, ui.DefaultFontSize, core.ColorWhite,
	)
}

func (p *Player) OnFree(ent entity.Ref) {
	// just in case
	p.saveTilemap()
}
