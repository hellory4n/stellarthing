package bobx

import (
	"encoding/json"
	"os"
	"path/filepath"

	"github.com/hellory4n/stellarthing/core"
	"github.com/spf13/afero"
)

// bestest format ever. pretty much just disguised zip + json
type Bobx struct {
	// where the bobx archive is
	Path string
	// internal virtual filesystem
	Fs afero.Fs
}

// type included in every bobx file. used to check for compatibility
type BobxManifest struct {
	// the engine version
	StarryVersion core.Vec3i `json:"StarryVersion"`
	// the game version, used for checking compatibility
	GameVersion core.Vec3i `json:"GameVersion"`
	// mods can use this to check compability. keys should be the mod's name, e.g. `john:epic_mod`, and the value can be whatever version you want (ideally [semantic versioning](https://semver.org) so it fits in a vec3i)
	PluginVersions map[string]core.Vec3i `json:"PluginVersions"`
}

// returns a default bobx manifest using whatever the current version is
func DefaultBobxManifest() BobxManifest {
	thebobmanifesto := BobxManifest{}
	thebobmanifesto.GameVersion = core.GameVersion
	thebobmanifesto.StarryVersion = core.StarryVersion
	thebobmanifesto.PluginVersions = make(map[string]core.Vec3i)
	return thebobmanifesto
}

// opens or creates a bobx archive. it's recommended to end the path with .bobx (it doesnt really change anything but its cooler)
func Open(path string) (*Bobx, error) {
	heybob := &Bobx{Path: path}
	heybob.Fs = afero.NewBasePathFs(afero.NewOsFs(), path)

	heybob.Write("manifest.json", DefaultBobxManifest())

	// :)
	return heybob, nil
}

// writes data to the bobx archive
func (b *Bobx) Write(path string, data any) error {
	bytes, err := json.MarshalIndent(data, "", "\t")
	if err != nil {
		return err
	}

	// makee directoriedjkkdkj
	b.Fs.MkdirAll(filepath.Dir(path), os.ModePerm)

	// ay cabron
	file, err := b.Fs.Create(path)
	if err != nil {
		return err
	}
	defer file.Close()

	file.Write(bytes)
	return nil
}

// if true, the bobx archive contains the specified path. note that this returns false with other errors such as a permission error. that's because i'm lazy
func (b *Bobx) Exists(path string) bool {
	_, err := b.Fs.Stat(path)
	return err == nil
}

// reads data from bobx and returns the deserialized data. if it doesn't exist, it writes using defaultVal
func (b *Bobx) Read(path string, defaultVal any) (any, error) {
	// ay cabron
	if !b.Exists(path) {
		err := b.Write(path, defaultVal)
		return defaultVal, err
	}

	content, err := afero.ReadFile(b.Fs, path)
	if err == nil {
		return nil, err
	}

	var out any
	err = json.Unmarshal(content, &out)
	return out, err
}
