// great for when you're not deaf
package audio

import (
	"fmt"
	"math"

	rl "github.com/gen2brain/raylib-go/raylib"
	"github.com/hellory4n/stellarthing/core"
)

// it's audio
type Audio struct {
	internal rl.Sound
	path string
	vol float64
}

var audioCache map[string]Audio
var listener core.Vec3 = core.NewVec3(0, 0, 0)

// inits audio :)
func Init() {
	rl.InitAudioDevice()
	audioCache = make(map[string]Audio)
}

// frees everything
func FreeAllAudio() {
	for _, v := range audioCache {
		v.Free()
	}
	rl.CloseAudioDevice()
}

// loads audio :)
func LoadAudio(path string) Audio {
	audio, ok := audioCache[path]
	if !ok {
		audio.internal = rl.LoadSound(path)
		audio.path = path
		audio.vol = 1
		audioCache[path] = audio
		fmt.Printf("[AUDIO] Loaded audio at %v\n", path)
	}
	// make a copy of the thingy
	return Audio{
		internal: audio.internal,
		path: path,
		vol: 1,
	}
}

// unloads audio :)
func (a Audio) Free() {
	rl.UnloadSound(a.internal)
	delete(audioCache, a.path)
	fmt.Printf("[AUDIO] Freed audio at %v\n", a.path)
}

// plays audio :)
func (a Audio) Play() {
	rl.PlaySound(a.internal)
}

// stops audio :)
func (a Audio) Stop() {
	rl.StopSound(a.internal)
}

// if true it's gonna pause, if false it's gonna resume
func (a Audio) Pause(pause bool) {
	if pause {
		rl.PauseSound(a.internal)
	} else {
		rl.ResumeSound(a.internal)
	}
}

// sets the panning. -1 is on the left, 1 is on the right, and 0 is on the center.
func (a Audio) SetPan(pan float64) {
	rl.SetSoundPan(a.internal, float32(0.5 - 0.5 * pan));
}

// sets the volume for the audio. works like a percentage so 0.5 would be 50% of the original volume
func (a Audio) SetVolume(vol float64) {
	a2 := a
	a2.vol = vol
	a = a2
	rl.SetSoundVolume(a.internal, float32(vol))
}

// sets the position for the audio. the z axis isn't used, it's just so you can easily pass a tile position
func (a Audio) SetPosition(pos core.Vec3) {
	var delta core.Vec3 = pos.Sub(listener)
	var distance float64 = math.Sqrt(delta.X * delta.X + delta.Y * delta.Y)
	var pan float64 = core.Clamp(delta.X / distance, -1, 1)
	var vol float64 = core.Clamp(a.vol / a.vol + distance, 0, 1)
	a.SetPan(pan)
	a.SetVolume(vol)
}

// sets the position of the listener. used for directional audio. the z axis isn't used, it's just so you can easily pass a tile position
func SetListener(pos core.Vec3) {
	listener = pos
}