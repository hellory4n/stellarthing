package species

import (
	"fmt"
	"path/filepath"
	"time"

	"github.com/hellory4n/stellarthing/core"
	"github.com/hellory4n/stellarthing/core/bobx"
	"github.com/hellory4n/stellarthing/entities"
	"github.com/hellory4n/stellarthing/platform"
	"github.com/hellory4n/stellarthing/platform/graphics"
	"github.com/hellory4n/stellarthing/ui"
)

// thats how fast the average person walks per second
const speed float64 = 1.42

type Player struct {
	tile *graphics.Tile
	tileData *graphics.TileData
	theButtonThatIsPress bool
	cycleState int
	ranje float64
}

type LaData struct {
	Thingy string
}

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

	uuuuuy, _ := bobx.Open(filepath.Join(core.GetUserDir(), "test"))
	var sogmaballs LaData
	uuuuuy.Read("mate.json", LaData{Thingy: "Oi mate"}, &sogmaballs)
	fmt.Println(sogmaballs.Thingy)
}

func (p *Player) OnUpdate(entity entities.EntityRef, delta float64) {
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
}

func (p *Player) OnDraw(entity entities.EntityRef) {
	graphics.CurrentWorld.Draw()

	// haha
	ui.DrawDialog(core.NewVec2(16, 16), core.NewVec2(250+16+16, 32+40+16+40+16+16))
	ui.Button(core.NewVec2(32, 32), core.NewVec2(250, ui.ButtonHeight), "Button", ui.ButtonStylePrimary, func() {})
	ui.ToggleButton(core.NewVec2(32, 32+40+8), core.NewVec2(250, ui.ButtonHeight), "Toggled", &p.theButtonThatIsPress)
	ui.CycleButton(core.NewVec2(32, 32+40+8+40+8), core.NewVec2(250, ui.ButtonHeight), &p.cycleState, "Option 1", "Option 2", "°ÁGKERYHKAEOHKERH", ".")
	ui.Slider(core.NewVec2(32, 32+40+8+40+8+40+8), core.NewVec2(250, ui.ButtonHeight), "Oi mate", 25, 50, &p.ranje)
}

func (p *Player) OnFree(entity entities.EntityRef) {
	fmt.Println("rip")
}