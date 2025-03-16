package tile

import (
	"math"

	"github.com/hellory4n/stellarthing/core"
)

func (w *World) GenerateChunk(chunkPos core.Vec3i) {
	chunkStartX := chunkPos.X * ChunkSize
	chunkStartY := chunkPos.Y * ChunkSize
	// chunkEndX := chunkPos.X*ChunkSize + ChunkSize
	// chunkEndY := chunkPos.Y*ChunkSize + ChunkSize

	var noiseMap = w.GenerateNoiseMap(ChunkSize, ChunkSize, 5)

	for y := range int(ChunkSize) {
		for x := range int(ChunkSize) {
			var tile Id
			switch {
			case noiseMap[y][x] > 0.9:
				tile = Snow
			case noiseMap[y][x] > 0.8:
				tile = Mountain
			case noiseMap[y][x] > 0.7:
				tile = Stone
			case noiseMap[y][x] > 0.6:
				tile = HighGrass
			case noiseMap[y][x] > 0.5:
				tile = LowGrass
			case noiseMap[y][x] > 0.4:
				tile = Sand
			case noiseMap[y][x] > 0.3:
				tile = ShallowOcean
			case noiseMap[y][x] > 0.2:
				tile = MidOcean
			default:
				tile = DeepOcean
			}

			pos := core.Vec3i{int64(x) + chunkStartX, int64(y) + chunkStartY, chunkPos.Z}
			w.LoadedGroundTiles[pos] = &Tile{TileId: tile}
		}
	}
}

// idk whats going on anymore
func (w *World) GenerateNoiseMap(width int64, height int64, scale float64) [][]float64 {
	m := make([][]float64, height)
	for i := range m {
		m[i] = make([]float64, width)
	}

	// just so we dont get a division by 0 error
	scale = core.Clamp(scale, 0.001, math.MaxFloat64)

	for y := range height {
		for x := range width {
			var sampleX float64 = float64(x) / scale
			var sampleY float64 = float64(y) / scale

			var perlinma float64 = w.perlinGen.Noise2D(sampleX, sampleY)
			m[y][x] = perlinma
		}
	}

	return m
}
