# Examples

## Graphics

### Draw texture

```c
#include "modules/graphics/graphics.h"

// first load it
// textures are cached btw
StTexture* bob = StTexture_new("assets/bob_guy.png");

// then draw it
StGraphics_draw_texture(bob, (stvec2){30, 40}, 0);

// freeing is handled by the engine
```

## Tweens

```c
#include "modules/util/tween.h"

// just call one of the tween functions
StTween_float(&rot, -360, 360, 5, ST_EASING_LINEAR);
StTween_vec2(&pos, (stvec2){ 40, 60}, (stvec2){600, 400}, 5, ST_EASING_LINEAR);
StTween_color(&color, ST_WHITE, ST_TRANSPARENT, 5, ST_EASING_LINEAR);
```

## Audio

```c
#include "modules/audio/audio.h"

// load
StAudio audio = StAudio_new("assets/epic_audio_file.ogg");

// play
StAudio_play(audio);

// directional audio is supported too
StAudio_set_position(audio, (stvec3){60, 50, 0});

// freeing is handled by the engine
```

## Input

```c
#include "modules/platform/input.h"

// just check for the key
if (StInput_is_key_just_pressed(ST_KEY_A)) {}

// or the mouse button
if (StInput_is_mouse_button_just_pressed(ST_MOUSE_BUTTON_LEFT)) {}

// just have your editor suggest the functions
```

### Keymaps

```c
#include "modules/platform/input.h"

// setup keymaps
StInput_add_keymap("some_keymap", ST_KEY_SPACE);
StInput_add_keymap("some_keymap", ST_KEY_ENTER);

// now you can check it e.g.
if (StInput_is_keymap_just_pressed("some_keymap")) {}
```

## Tilemap

### Managing worlds

```c
#include "modules/graphics/tilemap.h"

StWorld* handsome_world = StWorld_new();

// you can set the current world for convenience
StWorld_set_current(handsome_world);

// draw the world
StWorld_draw(StWorld_current());

// remember to free it
StWorld_free(StWorld_current());
```

### Tiles

```c
#include "modules/graphics/tilemap.h"

// add a tile
// z is for the layer
StTile* tile = StWorld_new_tile(StWorld_current(), (stvec3){5, 3, 5}, false, texture1, texture2, texture3, texture4);

// get a tile from a position
StTile* tile = StWorld_get_tile(StWorld_current(), (stvec3){5, 3, 5}, false);
```

## Timers

```c
#include "modules/util/timer.h"

static void callback() {
    printf("mate\n");
}

StTimer* eltimer = StTimer_new(3, true, &callback);
StTimer_start(eltimer);

// freeing is handled by the engine
```