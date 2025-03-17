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

	// :(
	var noiseMap = w.GenerateNoiseMap(chunkStartX, chunkStartY, ChunkSize, ChunkSize, 126.5, 2, 0.5, 1.87)

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
func (w *World) GenerateNoiseMap(chunkX, chunkY, width, height int64, scale float64,
	octaves int, persistance float64, lacunarity float64) [][]float64 {
	m := make([][]float64, height)
	for i := range m {
		m[i] = make([]float64, width)
	}

	// help
	octaveOffsets := make([]core.Vec2, octaves)
	for i := range octaveOffsets {
		// ¿que?
		offsetEcks := (w.randGen.Float64() * 100_000) + -100_000
		offsetWhy := (w.randGen.Float64() * 100_000) + -100_000
		octaveOffsets[i] = core.Vec2{offsetEcks, offsetWhy}
	}

	// just so we dont get a division by 0 error
	scale = core.Clamp(scale, 0.001, math.MaxFloat64)

	// so we can normalize back to the range of 0-1
	maxNoiseHeight := -math.MaxFloat64
	minNoiseHeight := math.MaxFloat64

	for y := range height {
		for x := range width {
			amplitude := 1.0
			frequency := 1.0
			noiseHeight := 0.0

			for i := range octaves {
				var sampleX float64 = float64(x+chunkX)/scale*frequency + octaveOffsets[i].X
				var sampleY float64 = float64(y+chunkY)/scale*frequency + octaveOffsets[i].Y

				var perlinma float64 = w.perlinGen.Noise2D(sampleX, sampleY)*2 - 1
				noiseHeight = perlinma * amplitude

				amplitude *= persistance
				frequency *= lacunarity
			}

			if noiseHeight > maxNoiseHeight {
				maxNoiseHeight = noiseHeight
			} else if noiseHeight < minNoiseHeight {
				minNoiseHeight = noiseHeight
			}

			m[y][x] = noiseHeight
		}
	}

	// normalize to 0-1
	for y := range height {
		for x := range width {
			m[y][x] = core.InverseLerp(minNoiseHeight, maxNoiseHeight, m[y][x])
		}
	}

	return m
}
