package species

import (
	"fmt"

	"github.com/hellory4n/stellarthing/core"
	"github.com/hellory4n/stellarthing/modules/entities"
	"github.com/hellory4n/stellarthing/modules/graphics"
	"github.com/hellory4n/stellarthing/modules/platform"
)

type Player struct {
	pos core.Vec2
	texture graphics.Texture
}

func (p *Player) EntityType() entities.EntityType {
	return entities.EntityTypeGameWorld
}

func (p *Player) OnCreate() {
	fmt.Println("Good morning.")
	p.texture = graphics.LoadTexture("assets/bob_guy.png")
	platform.AddKeymap("move_left", platform.KeyA)
	platform.AddKeymap("move_left", platform.KeyLeft)
	platform.AddKeymap("move_right", platform.KeyD)
	platform.AddKeymap("move_right", platform.KeyRight)
	platform.AddKeymap("move_up", platform.KeyW)
	platform.AddKeymap("move_up", platform.KeyUp)
	platform.AddKeymap("move_down", platform.KeyS)
	platform.AddKeymap("move_down", platform.KeyDown)

}

func (p *Player) OnUpdate(delta float64) {
	if (platform.IsKeymapHeld("move_left")) {
		p.pos = p.pos.Add(core.NewVec2(-100 * delta, 0))
	}

	if (platform.IsKeymapHeld("move_right")) {
		p.pos = p.pos.Add(core.NewVec2(100 * delta, 0))
	}

	if (platform.IsKeymapHeld("move_up")) {
		p.pos = p.pos.Add(core.NewVec2(0, -100 * delta))
	}

	if (platform.IsKeymapHeld("move_down")) {
		p.pos = p.pos.Add(core.NewVec2(0, 100 * delta))
	}
}

func (p *Player) OnDraw() {
	graphics.DrawTexture(p.texture, p.pos, 0, core.ColorWhite)
}

func (p *Player) OnFree() {
	fmt.Println("rip")
}