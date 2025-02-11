#pragma once
#include "raylib.h"

void __st_init_audio__();

void __st_free_audio__();

/// i can't include raylib in my header files so this is a disguised path that's referred in a hashmap
typedef const char* StAudio;

/// loads audio from a path. supported formats are WAV, OGG, MP3, FLAC, XM, MOD, and QOA
StAudio StAudio_new(const char* path);

/// plays audio.
void StAudio_play(StAudio a);