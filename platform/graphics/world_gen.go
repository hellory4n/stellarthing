package graphics

import (
	"math/rand"

	"github.com/hellory4n/stellarthing/core"
)

// first result is ground tiles, 2nd is object tiles (cities use those)
func GenerateChunk(randgen *rand.Rand, chunkPos core.Vec3i) (map[core.Vec3i]*Tile, map[core.Vec3i]*Tile) {
	ground := make(map[core.Vec3i]*Tile)
	objects := make(map[core.Vec3i]*Tile)

	chunkStartX := chunkPos.X * ChunkSize
	chunkStartY := chunkPos.Y * ChunkSize
	chunkEndX := chunkPos.X*ChunkSize + ChunkSize
	chunkEndY := chunkPos.Y*ChunkSize + ChunkSize

	for x := chunkStartX; x < chunkEndX; x++ {
		for y := chunkStartY; y < chunkEndY; y++ {
			ground[core.NewVec3i(x, y, chunkPos.Z)] = &Tile{
				TileId: TileMarsRock,
			}
		}
	}
	return ground, objects
}