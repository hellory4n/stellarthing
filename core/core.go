package core

import (
	"fmt"
	"os"
	"path/filepath"
	"runtime"
)

// enables/disables some features such as assert
const Debug = true

// engine version
const StarryVersion = "v4.0.0"

// game version
const GameVersion = "v0.11.0"

// yeah
const GameName = "stellarthing"

// panics if a condition isn't met but only in debug. useful for not making dumb mistakes
func Assert(msg string, condition bool) {
	if !condition {
		panic(fmt.Sprintf("assert failed: %v\n", msg))
	}
}

// gets the directory where saves go. %APPDATA% on windows, ~/.local/share
func GetUserDir() string {
	switch runtime.GOOS {
	case "windows":
		return filepath.Join(os.Getenv("APPDATA"), GameName)
	case "linux", "freebsd", "openbsd", "netbsd":
		home, err := os.UserHomeDir()
		if err != nil {
			panic("your OS has a skill issue and couldn't find your home folder")
		}

		return filepath.Join(home, ".local", "share", GameName)
	default:
		panic(fmt.Sprintf("unsupported OS: %v\n", runtime.GOOS))
	}
}