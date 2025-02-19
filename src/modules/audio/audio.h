#pragma once
#include "core/vectors.h"

void __st_init_audio__();

void __st_free_audio__();

/// i can't include raylib in my header files so this is a random id
typedef const char* StAudio;

/// loads audio from a path. supported formats are WAV, OGG, MP3, FLAC, XM, MOD, and QOA
StAudio StAudio_new(const char* path);

/// plays audio.
void StAudio_play(StAudio a);

/// stops audio
void StAudio_stop(StAudio a);

/// if true it's gonna pause, if false it's gonna resume
void StAudio_pause(StAudio a, bool pause);

/// sets the panning for the audio. -1 is on the left, 1 is on the right, and 0 is on the center.
void StAudio_set_pan(StAudio a, float64 pan);

/// sets the volume for the audio. works like a percentage so 0.5 would be 50% of the original volume
void StAudio_set_volume(StAudio a, float64 vol);

/// sets the position for the audio. the z axis isn't used, it's just so you can easily pass a tile position
void StAudio_set_position(StAudio a, stvec3 pos);

/// sets the position of the listener. used for directional audio. the z axis isn't used, it's just so you can easily pass a tile position
void StAudio_set_listener(stvec3 pos);