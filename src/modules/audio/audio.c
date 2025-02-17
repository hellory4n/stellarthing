#include <stdio.h>
#include <math.h>
#include "raylib.h"
#include "core/collections/sthashmap.h"
#include "core/math/math.h"
#include "audio.h"

/// keys are strings, values are raylib Sound
StHashMap* __st_audio__;
/// keys are strings, values are float64s
StHashMap* __st_prev_volume__;

void __st_init_audio__()
{
    InitAudioDevice();
    __st_audio__ = StHashMap_new(0);
    __st_prev_volume__ = StHashMap_new(0);
}

void __st_free_audio__()
{
    StList* items = StHashMap_items(__st_audio__);
    for (nint i = 0; i < items->length; i++) {
        StTuple2* kvp = (StTuple2*)items->items[i];
        UnloadSound(*(Sound*)(kvp->item2));
        free(kvp->item2);
        printf("[ASSETS] Freed audio file at %s\n", (const char*)kvp->item1);
    }
    StList_free_with_items(items);

    StHashMap_free(__st_audio__);
    StHashMap_free(__st_prev_volume__);

    CloseAudioDevice();
}

StAudio StAudio_new(const char* path)
{
    if (StHashMap_contains(__st_audio__, path)) {
        return path;
    }

    // actually load
    Sound soundButLocal = LoadSound(path);
    Sound* sound = malloc(sizeof(Sound));
    *sound = soundButLocal;
    StHashMap_set(__st_audio__, path, sound);

    nint please_let_me_use_a_float_as_a_void_ptr;
    float64 man = 1.0;
    memcpy(&please_let_me_use_a_float_as_a_void_ptr, &man, sizeof(float64));
    StHashMap_set(__st_prev_volume__, path, (void*)please_let_me_use_a_float_as_a_void_ptr);
    printf("[ASSETS] Loaded audio file at %s\n", path);

    return path;
}

void StAudio_play(StAudio a)
{
    Sound* sound = StHashMap_get(__st_audio__, a);
    if (sound == NULL) {
        printf("[AUDIO] Audio at %s is invalid\n", a);
    }
    else {
        PlaySound(*sound);
    }
}

void StAudio_stop(StAudio a)
{
    Sound* sound = StHashMap_get(__st_audio__, a);
    if (sound == NULL) {
        printf("[AUDIO] Audio at %s is invalid\n", a);
    }
    else {
        StopSound(*sound);
    }
}

void StAudio_pause(StAudio a, bool pause)
{
    Sound* sound = StHashMap_get(__st_audio__, a);
    if (sound == NULL) {
        printf("[AUDIO] Audio at %s is invalid\n", a);
    }
    else {
        if (pause) PauseSound(*sound);
        else ResumeSound(*sound);
    }
}

void StAudio_set_pan(StAudio a, float64 pan)
{
    Sound* sound = StHashMap_get(__st_audio__, a);
    if (sound == NULL) {
        printf("[AUDIO] Audio at %s is invalid\n", a);
    }
    else {
        SetSoundPan(*sound, (pan + 1) / 2);
    }
}

void StAudio_set_volume(StAudio a, float64 vol)
{
    Sound* sound = StHashMap_get(__st_audio__, a);
    if (sound == NULL) {
        printf("[AUDIO] Audio at %s is invalid\n", a);
    }
    else {
        StHashMap_set(__st_prev_volume__, a, (void*)(uintptr_t)vol);
    }
}

stvec3 listener;

void StAudio_set_listener(stvec3 pos)
{
    listener = pos;
}

void StAudio_set_position(StAudio a, stvec3 pos)
{
    stvec3 delta = stvec3_sub(pos, listener);
    float64 distance = sqrt(delta.x * delta.x + delta.y * delta.y);
    StAudio_set_pan(a, st_clamp(delta.x / distance, -1, 1));
    float64 vol = (float64)(uintptr_t)StHashMap_get(__st_audio__, a);
    StAudio_set_volume(a, vol / vol + distance);
}