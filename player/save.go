package player

import (
	"bytes"
	"encoding/gob"
	"fmt"
	"os"
	"path/filepath"
	"time"

	"github.com/hellory4n/stellarthing/core"
	"github.com/hellory4n/stellarthing/core/util"
	"github.com/hellory4n/stellarthing/entity"
	"github.com/hellory4n/stellarthing/tile"
)

const CurrentUniverse string = "the big dong theorem"
const CurrentWorld string = "sigmoid_curve"

var universePath string = filepath.Join(core.GetUserDir(), "saves", CurrentUniverse)
var worldPath string = filepath.Join(core.GetUserDir(), "saves", CurrentUniverse, CurrentWorld+".gob")

func (p *Player) setupSave(ent entity.Ref) {
	if _, err := os.Stat(worldPath); err != nil {
		p.firstTime(ent)
	} else {
		p.loadTilemap(ent)
	}

	timer := util.NewTimer(5, true)
	timer.Timeout = p.saveTilemap
}

func (p *Player) firstTime(ent entity.Ref) {
	// hehe
	os.MkdirAll(universePath, os.ModePerm)

	world := tile.NewWorld(core.Vec2i{-250, -250}, core.Vec2i{250, 250}, time.Now().UnixNano())
	tile.ThisWorld = world

	p.tile = tile.ThisWorld.NewTile(core.Vec3i{0, 0, 0}, false, tile.BobGuy, ent, tile.Variation(ent))
	p.tileData = p.tile.GetData()
	p.tileData.Position = core.Vec3{8, 8, 0}
	tile.ThisWorld.SetCameraPosition(p.tileData.Position)
	p.tileData.UsingCustomPos = true

	p.saveTilemap()

	fmt.Println("[SAVE] Setup tilemap for the first time")
}

func (p *Player) loadTilemap(ent entity.Ref) {
	bytema, err := os.ReadFile(worldPath)
	if err != nil {
		panic(fmt.Sprintf("[SAVE] couldn't load world: %v\n", err.Error()))
	}

	var uy *tile.World
	buf := bytes.NewBuffer(bytema)
	decodema := gob.NewDecoder(buf)
	if err := decodema.Decode(&uy); err != nil {
		panic(fmt.Sprintf("[SAVE] couldn't load world: %v\n", err.Error()))
	}
	tile.ThisWorld = uy

	// the player position is always the camera position
	p.tile = tile.ThisWorld.NewTile(core.Vec3i{0, 0, 0}, false, tile.BobGuy, ent, tile.Variation(ent))
	p.tileData = p.tile.GetData()
	p.tileData.Position = tile.ThisWorld.CameraPosition
	tile.ThisWorld.SetCameraPosition(p.tileData.Position)
	p.tileData.UsingCustomPos = true

	fmt.Println("[SAVE] Loaded tilemap")
}

func (p *Player) saveTilemap() {
	// stop busting
	if tile.ThisWorld == nil {
		return
	}

	var buf bytes.Buffer
	encodema := gob.NewEncoder(&buf)
	if err := encodema.Encode(tile.ThisWorld); err != nil {
		panic(fmt.Sprintf("[SAVE] couldn't save world: %v\n", err.Error()))
	}

	err := os.WriteFile(worldPath, buf.Bytes(), os.ModePerm)
	if err != nil {
		panic(fmt.Sprintf("[SAVE] couldn't save world: %v\n", err.Error()))
	}

	fmt.Println("[SAVE] Saved tilemap")
}
