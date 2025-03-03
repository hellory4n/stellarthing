package bobx

import (
	"context"
	"encoding/json"
	"errors"
	"io/fs"
	"os"
	"strings"

	"github.com/hellory4n/stellarthing/core"
	"github.com/mholt/archives"
)

// bestest format ever. pretty much just disguised zip + json
type Bobx struct {
	// where the bobx archive is
	Path string
	// internal virtual filesystem
	Fs fs.FS
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

// opens or creates a bobx archive. path is recommended to be .bobx.zip but most archive formats are supported, and regular directories are supported too if you want (end the path with /)
func Open(path string) (*Bobx, error) {
	// bobx doesnt exist
	if _, err := os.Stat(path); errors.Is(err, os.ErrNotExist) {
		return newBobxArchive(path)
	} else {
		// open existing bobx archive
		bobx := &Bobx{Path: path}
		ctx := context.TODO()
		fs, err := archives.FileSystem(ctx, path, nil)
		if err != nil {
			return nil, err
		}
		bobx.Fs = fs
		return bobx, nil
	}
}

func newBobxArchive(path string) (*Bobx, error) {
	ctx := context.TODO()

	if strings.HasSuffix(path, "/") {
		os.MkdirAll(path, os.ModePerm)
	} else {
		file, err := os.Open(path)
		if err != nil {
			return nil, err
		}
		defer file.Close()

		// make an archive
		format := archives.CompressedArchive{
			Compression: archives.Zlib{},
			Archival: archives.Zip{},
		}
		err = format.Archive(ctx, file, []archives.FileInfo{})
		if err != nil {
			return nil, err
		}
	}

	// now open and make a manifest file
	bobx := &Bobx{Path: path}
	fs, err := archives.FileSystem(ctx, path, nil)
	if err != nil {
		return nil, err
	}
	bobx.Fs = fs

	ccbbga

	return bobx, nil
}

// writes data to the bobx archive
func (b *Bobx) Write(path string, data any) error {
	file, err := b.Fs.Open(path)
	if err != nil {
		return err
	}
	defer file.Close()

	bytes, err := json.MarshalIndent(data, "", "\t")
	if err != nil {
		return err
	}
	
}

// reads data from bobx and returns the deserialized data. if it doesn't exist, it writes using defaultVal
func (b *Bobx) Read(path string, defaultVal any) (any, error) {
}
