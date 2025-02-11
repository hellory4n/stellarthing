#pragma once
#include "core/vectors.h"

/// makes a window
void StWindow_create(const char* title, stvec2i size);

/// if true, the window becomes fullscreen
void StWindow_set_fullscreen(bool fullscreen);

/// if true, the window becomes fullscreen
bool StWindow_fullscreen();

/// if true, the window is closing
bool StWindow_closing();

/// requests the window to be closed. this doesn't free the window stuff.
void StWindow_close();

/// updates the window. put this at the end of your main loop
void StWindow_update();

/// sets the target frames per second
void StWindow_set_target_fps(uint32 fps);

/// frees the window
void StWindow_free();

/// if true, there is in fact a window
bool StWindow_is_ready();

/// returns seconds since the window was opened
float64 StWindow_get_time();

/// returns time between frames in seconds. look up delta time
float64 StWindow_get_delta_time();