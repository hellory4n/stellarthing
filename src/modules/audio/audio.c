#include <stdio.h>
#include "raylib.h"
#include "core/collections/sthashmap.h"
#include "audio.h"

/// keys are strings, values are raylib Sound
StHashMap* __st_audio__;

void __st_init_audio__()
{
    InitAudioDevice();
    __st_audio__ = StHashMap_new(0);
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