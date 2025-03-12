package graphics

import (
	"bytes"
	"encoding/gob"
	"errors"
	"fmt"
	"path/filepath"
	"strings"
	"unicode"

	"github.com/hellory4n/stellarthing/core"
	"github.com/hellory4n/stellarthing/core/bobx"
	"github.com/spf13/afero"
)

// i cant be bothered to design a good saving system
func IsUniverseNameValid(universe string) bool {
	if universe == "" {
		return false
	}

	if len(universe) > 100 {
		return false
	}

	for _, r := range universe {
		if !unicode.IsLetter(r) && !unicode.IsDigit(r) && r != ' ' {
			return false
		}
	}

	// lmao
	switch strings.ToLower(universe) {
	case "con", "prn", "aux", "nul",
		"com1", "com2", "com3", "com4", "com5", "com6", "com7", "com8", "com9",
		"lpt1", "lpt2", "lpt3", "lpt4", "lpt5", "lpt6", "lpt7", "lpt8", "lpt9":
		return false
	}

	return true
}

// saves the tilemap lol. name must be smaller than 100 characters and only have alphanumeric
// characters (including latin extended) and spaces
func (t *TileWorld) Save(universe string) error {
	if !IsUniverseNameValid(universe) {
		fmt.Printf("[TILEMAP] Failed to save world %v (universe %v): invalid name\n", t.Name, universe)
		return errors.New("invalid universe name")
	}

	b, err := bobx.Open(filepath.Join(core.GetUserDir(), "saves", universe))
	if err != nil {
		fmt.Printf("[TILEMAP] Failed to save world %v (universe %v): bobx error\n", t.Name, universe)
		return err
	}

	// gob
	var file afero.File
	if b.Exists(t.Name + ".gob") {
		file, err = b.Fs.Open(t.Name + ".gob")
		if err != nil {
			fmt.Printf("[TILEMAP] Failed to save world %v (universe %v): bobx error\n", t.Name, universe)
			return err
		}
	} else {
		file, err = b.Fs.Create(t.Name + ".gob")
		if err != nil {
			fmt.Printf("[TILEMAP] Failed to save world %v (universe %v): bobx error\n", t.Name, universe)
			return err
		}
	}

	// write :)
	var buf bytes.Buffer
	var encodedeez = gob.NewEncoder(&buf)
	if err := encodedeez.Encode(t); err != nil {
		fmt.Printf("[TILEMAP] Failed to save world %v (universe %v): couldn't encode\n", t.Name, universe)
		return err
	}
	file.Write(buf.Bytes())

	fmt.Printf("[TILEMAP] Saved world %v (universe %v)\n", t.Name, universe)
	return nil
}

// loads a world. wow. life changing i know.
func LoadWorld(universe, world string) (*TileWorld, error) {
	b, err := bobx.Open(universe)
	if err != nil {
		fmt.Printf("[TILEMAP] Failed to load world %v (universe %v): bobx error\n", world, universe)
		return nil, err
	}

	content, err := afero.ReadFile(b.Fs, world + ".gob")
	if err != nil {
		fmt.Printf("[TILEMAP] Failed to load world %v (universe %v): bobx error\n", world, universe)
		return nil, err
	}

	buf := bytes.NewBuffer(content)
	decodedeez := gob.NewDecoder(buf)
	t := &TileWorld{}
	if err := decodedeez.Decode(t); err != nil {
		return nil, err
	}

	return t, nil
}
