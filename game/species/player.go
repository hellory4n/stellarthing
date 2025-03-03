package species

import (
	"fmt"
	"path/filepath"

	"github.com/hellory4n/stellarthing/core"
	"github.com/hellory4n/stellarthing/modules/bobx"
	"github.com/hellory4n/stellarthing/modules/entities"
	"github.com/hellory4n/stellarthing/modules/graphics"
	"github.com/hellory4n/stellarthing/modules/platform"
)

type Player struct {
	tile graphics.Tile
}

type LaData struct {
	Thingy string `json:"thingy"`
}

func (p *Player) EntityType() entities.EntityType {
	return entities.EntityTypeGameWorld
}

func (p *Player) OnCreate() {
	fmt.Println("Good morning.")

	// bob := graphics.LoadTexture("assets/bob_guy.png")

	platform.AddKeymap("move_left", platform.KeyA)
	platform.AddKeymap("move_left", platform.KeyLeft)
	platform.AddKeymap("move_right", platform.KeyD)
	platform.AddKeymap("move_right", platform.KeyRight)
	platform.AddKeymap("move_up", platform.KeyW)
	platform.AddKeymap("move_up", platform.KeyUp)
	platform.AddKeymap("move_down", platform.KeyS)
	platform.AddKeymap("move_down", platform.KeyDown)

	// world := graphics.NewTileWorld(core.NewVec2i(250, 250))
	// graphics.CurrentWorld = world

	// p.tile = *graphics.CurrentWorld.NewTile(core.NewVec3(5, 5, 0), false, bob, bob, bob, bob)

	uuuuuy, _ := bobx.Open(filepath.Join(core.GetUserDir(), "test.bobx"))
	fmt.Println(filepath.Join(core.GetUserDir(), "test.bobx"))
	uuuuuy.Save()
	uuuuuy.Write("mate.json", LaData{Thingy: "TTTTTTTT"})
	uuuuuy.Save()
	SOFGMA, _ := uuuuuy.Read("mate.json", LaData{Thingy: "Oi mate"})
	fmt.Println(SOFGMA.(string))
	uuuuuy.Save()
}

func (p *Player) OnUpdate(delta float64) {
	if platform.IsKeymapHeld("move_left") {
		p.tile.Position = p.tile.Position.Add(core.NewVec3(-0.25 * delta, 0, 0))
	}

	if platform.IsKeymapHeld("move_right") {
		p.tile.Position = p.tile.Position.Add(core.NewVec3(0.25 * delta, 0, 0))
	}

	if platform.IsKeymapHeld("move_up") {
		p.tile.Position = p.tile.Position.Add(core.NewVec3(0, -0.25 * delta, 0))
	}

	if platform.IsKeymapHeld("move_down") {
		p.tile.Position = p.tile.Position.Add(core.NewVec3(0, 0.25 * delta, 0))
	}
}

func (p *Player) OnDraw() {
	graphics.CurrentWorld.Draw()
}

func (p *Player) OnFree() {
	fmt.Println("rip")
}