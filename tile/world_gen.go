package tile

import (
	"math/rand"

	"github.com/hellory4n/stellarthing/core"
)

func GenerateChunk(randgen *rand.Rand, chunkPos core.Vec3i) (ground map[core.Vec3i]*Tile,
	objects map[core.Vec3i]*Tile) {
	ground = make(map[core.Vec3i]*Tile)
	objects = make(map[core.Vec3i]*Tile)

	chunkStartX := chunkPos.X * ChunkSize
	chunkStartY := chunkPos.Y * ChunkSize
	chunkEndX := chunkPos.X*ChunkSize + ChunkSize
	chunkEndY := chunkPos.Y*ChunkSize + ChunkSize

	for x := chunkStartX; x < chunkEndX; x++ {
		for y := chunkStartY; y < chunkEndY; y++ {
			ground[core.Vec3i{x, y, chunkPos.Z}] = &Tile{
				TileId: MarsRock,
			}
		}
	}
	return ground, objects
}
