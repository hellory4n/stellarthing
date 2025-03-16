package tile

import (
	"math"

	"github.com/hellory4n/stellarthing/core"
)

// checks for collisions in the surrounding tiles, returns a new position that collided.
// keep in mind move is gonna be added to pos
func (w *World) Collide(pos core.Vec3, move core.Vec3) core.Vec3 {
	newPos := pos

	newPos.X += move.X
	if mateDoesItCollideImBefuddled(w, newPos) {
		newPos.X = pos.X
	}

	newPos.Y += move.Y
	if mateDoesItCollideImBefuddled(w, newPos) {
		newPos.Y = pos.Y
	}

	return newPos
}

func mateDoesItCollideImBefuddled(w *World, pos core.Vec3) bool {
	// theres some padding so its less janky
	leftTile := math.Floor(pos.X + 0.1)
	rightTile := math.Floor(pos.X + 0.8)
	topTile := math.Floor(pos.Y + 0.1)
	bottomTile := math.Floor(pos.Y + 0.8)

	for x := leftTile; x <= rightTile; x++ {
		for y := topTile; y <= bottomTile; y++ {
			tile, ok := w.LoadedObjectTiles[core.Vec3i{int64(x), int64(y), int64(w.CameraPosition.Z)}]
			if ok && tile.TileId != Air {
				return true
			}
		}
	}
	return false
}
