#include <stdio.h>
#include "modules/platform/window.h"
#include "modules/graphics/graphics.h"
#include "modules/platform/input.h"
#include "modules/util/debug_mode.h"
#include "modules/audio/audio.h"
#include "modules/util/timer.h"
#include "modules/util/tween.h"
#include "modules/graphics/tilemap.h"
#include "modules/extensions/extensions.h"

StAudio leaudio;
bool paus = false;

static void __timer_callback__(StTimer* timer)
{
    paus = !paus;
    StAudio_pause(leaudio, paus);
}

int main(int argc, char const *argv[])
{
    StWindow_new("Stellarthing", (stvec2i){ 640, 480 });
    StWindow_toggle_fullscreen();
    //StWindow_set_target_fps(144);

    //
    StDebugMode_new();

    // mate
    StInput_add_keymap("test_move", ST_KEY_SPACE);
    StInput_add_keymap("test_move", ST_KEY_NUM6);
    StInput_add_keymap("test_move", ST_KEY_J);

    StTexture* m = StTexture_new("assets/test.png");
    leaudio = StAudio_new("assets/ross_tibeeth_jr_hhhh.ogg");
    //StAudio_play(leaudio);
    StTimer* TIMERULESALL = StTimer_new(3, true, &__timer_callback__);
    //StTimer_start(TIMERULESALL);
    stvec2 pos = (stvec2){ 40, 60 };
    float64 rot = 0;
    stcolor color = ST_WHITE;
    stvec3 sndpos = (stvec3){0.1, 0.1, 0.1};

    // the infamous tilemap
    StTexture* bob = StTexture_new("assets/bob_guy.png");
    StWorld_set_current(StWorld_new());
    StWorld_new_tile(StWorld_current(), (stvec3){0, 0, 0}, false, bob, bob, bob, bob);
    StWorld_new_tile(StWorld_current(), (stvec3){1, 0, 0}, false, bob, bob, bob, bob);
    StWorld_new_tile(StWorld_current(), (stvec3){0, 1, 0}, false, bob, bob, bob, bob);
    StWorld_new_tile(StWorld_current(), (stvec3){2, 0, 0}, false, bob, bob, bob, bob);
    StWorld_new_tile(StWorld_current(), (stvec3){3, 0, 0}, false, bob, bob, bob, bob);
    StWorld_new_tile(StWorld_current(), (stvec3){5, 5, 0}, false, bob, bob, bob, bob);

    // im in tremendous pain
    StExtensions_new();
    StExtensions_run("scripts/main.lua");

    while (!StWindow_closing()) {
        if (StInput_is_keymap_just_pressed("test_move")) {
            StTween_float(&rot, -360, 360, 5, ST_EASING_QUAD_IN_OUT);
            StTween_vec2(&pos, (stvec2){ 40, 60}, (stvec2){600, 400}, 5, ST_EASING_QUAD_IN_OUT);
            StTween_color(&color, ST_WHITE, ST_TRANSPARENT, 5, ST_EASING_QUAD_IN_OUT);
        }

        if (StInput_is_key_just_pressed(ST_KEY_F9)) {
            StAudio_set_position(leaudio, (stvec3){-60, 0, 0});
            //StTween_vec3(&sndpos, (stvec3){ 0, 0, 0 }, (stvec3){-60, 0, 0}, 5, ST_EASING_QUAD_IN_OUT);
        }

        if (StInput_is_key_just_pressed(ST_KEY_F10)) {
            StAudio_set_position(leaudio, (stvec3){60, 0, 0});
            //StTween_vec3(&sndpos, (stvec3){ 0, 0, 0 }, (stvec3){60, 0, 0}, 5, ST_EASING_QUAD_IN_OUT);
        }

        StGraphics_clear((stcolor){9, 154, 206, 255});

        StGraphics_draw_texture_ext(
            m, STVEC2_ZERO, (stvec2){m->width, m->height}, pos, (stvec2){m->width, m->height},
            (stvec2){0.5, 0.5}, rot, color
        );

        StDebugMode_update();
        StWorld_draw(StWorld_current());
        StGraphics_end_drawing();
        StWindow_update();
    }

    StExtensions_free();
    StWorld_free(StWorld_current());
    StDebugMode_free();
    StWindow_free();
    return 0;
}
