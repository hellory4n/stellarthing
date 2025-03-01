package platform

import rl "github.com/gen2brain/raylib-go/raylib"

/*bool StInput_is_keymap_just_pressed(const char* keymap)
{
    if (!StHashMap_contains(__st_keymaps__, keymap)) return false;

    StList* keys = StHashMap_get(__st_keymaps__, keymap);
    for (nint i = 0; i < keys->length; i++) {
        if (StInput_is_key_just_pressed((StKey)keys->items[i])) return true;
    }
    return false;
}*/

var keymapma map[string][]Key

func init() {
	keymapma = make(map[string][]Key)
}

func AddKeymap(keymap string, key Key) {
	keymapma[keymap] = append(keymapma[keymap], key)
}

func IsKeyJustPressed(key Key) bool {
	return rl.IsKeyPressed(int32(key))
}

func IsKeyJustReleased(key Key) bool {
	return rl.IsKeyReleased(int32(key))
}

func IsKeyJustHeld(key Key) bool {
	return rl.IsKeyDown(int32(key))
}

func IsKeyNotPressed(key Key) bool {
	return rl.IsKeyUp(int32(key))
}

func IsMouseButtonJustPressed(btn MouseButton) bool {
	return rl.IsMouseButtonPressed(rl.MouseButton(btn))
}

func IsMouseButtonJustReleased(btn MouseButton) bool {
	return rl.IsMouseButtonReleased(rl.MouseButton(btn))
}

func IsMouseButtonJustHeld(btn MouseButton) bool {
	return rl.IsMouseButtonDown(rl.MouseButton(btn))
}

func IsMouseButtonNotPressed(btn MouseButton) bool {
	return rl.IsMouseButtonUp(rl.MouseButton(btn))
}

func IsKeymapJustPressed(keymap string) bool {
	keymapdeez, ok := keymapma[keymap]

	// i'm not ok :(
	if !ok {
		return false
	}

	for _, v := range keymapdeez {
		if (IsKeyJustPressed(v)) {
			return true
		}
	}
	return false
}

func IsKeymapJustReleased(keymap string) bool {
	keymapdeez, ok := keymapma[keymap]

	// i'm not ok :(
	if !ok {
		return false
	}

	for _, v := range keymapdeez {
		if (IsKeyJustReleased(v)) {
			return true
		}
	}
	return false
}

func IsKeymapJustHeld(keymap string) bool {
	keymapdeez, ok := keymapma[keymap]

	// i'm not ok :(
	if !ok {
		return false
	}

	for _, v := range keymapdeez {
		if (IsKeyJustHeld(v)) {
			return true
		}
	}
	return false
}

func IsKeymapNotPressed(keymap string) bool {
	keymapdeez, ok := keymapma[keymap]

	// i'm not ok :(
	if !ok {
		return false
	}

	for _, v := range keymapdeez {
		if (IsKeyNotPressed(v)) {
			return true
		}
	}
	return false
}