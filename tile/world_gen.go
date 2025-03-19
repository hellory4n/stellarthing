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

	var noiseMap = w.GenerateNoiseMap(chunkStartX, chunkStartY, ChunkSize, ChunkSize, 352.146271962453)

	for y := range int(ChunkSize) {
		for x := range int(ChunkSize) {
			var tile Id
			switch {
			case noiseMap[y][x] > 0.8:
				tile = Snow
			case noiseMap[y][x] > 0.7:
				tile = Mountain
			case noiseMap[y][x] > 0.5:
				tile = Stone
			case noiseMap[y][x] > 0.3:
				tile = HighGrass
			case noiseMap[y][x] > 0.25:
				tile = LowGrass
			case noiseMap[y][x] > 0.2:
				tile = Sand
			case noiseMap[y][x] > 0.15:
				tile = ShallowOcean
			case noiseMap[y][x] > 0.1:
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
func (w *World) GenerateNoiseMap(chunkX, chunkY, width, height int64, scale float64) [][]float64 {
	m := make([][]float64, height)
	for i := range m {
		m[i] = make([]float64, width)
	}

	// just so we dont get a division by 0 error
	scale = core.Clamp(scale, 0.001, math.MaxFloat64)

	for y := range height {
		for x := range width {
			var sampleX float64 = float64(x+chunkX) / scale
			var sampleY float64 = float64(y+chunkY) / scale

			baseNoise := w.perlinGen.Noise2D(sampleX, sampleY)
			detailNoise := w.perlinGen.Noise2D(sampleX*2, sampleY*2) * 0.5
			fineNoise := w.perlinGen.Noise2D(sampleX*4, sampleY*4) * 0.25
			m[y][x] = (baseNoise*0.33 + detailNoise*0.33 + fineNoise*0.33)
		}
	}

	return m
}
