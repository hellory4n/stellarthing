package core

import (
	"fmt"
	"os"
	"path/filepath"
	"runtime"
)

// enables/disables some features such as assert
const Debug = true

// engine version string
const StarryVersionStr = "v4.0.0-dev"

// engine version
var StarryVersion Vec3i = NewVec3i(4, 0, 0)

// game version string
const GameVersionStr = "v1.0.0-alpha"

// game version
var GameVersion Vec3i = NewVec3i(1, 0, 0)

// yeah
const GameName = "stellarthing"

// panics if a condition isn't met but only in debug. useful for not making dumb mistakes
func Assert(msg string, condition bool) {
	if !Debug {
		return
	}
	
	if !condition {
		panic(fmt.Sprintf("assert failed: %v\n", msg))
	}
}

// gets the directory where saves go. %APPDATA% on windows, ~/.local/share on linux
func GetUserDir() string {
	switch runtime.GOOS {
	case "windows":
		path := filepath.Join(os.Getenv("APPDATA"), GameName)
		os.MkdirAll(path, os.ModePerm)
		return path
	case "linux", "freebsd", "openbsd", "netbsd", "dragonfly":
		home, err := os.UserHomeDir()
		if err != nil {
			panic("your OS has a skill issue and couldn't find your home folder")
		}

		path := filepath.Join(home, ".local", "share", GameName)
		os.MkdirAll(path, os.ModePerm)
		return path
	default:
		panic(fmt.Sprintf("unsupported OS: %v\n", runtime.GOOS))
	}
}