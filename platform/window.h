#pragma once
#include "core/core.h"
#include "core/math/vec.h"

/// Makes a window
void st_window_new(const char* title, StVec2i size);

/// Toggles fullscreen
void st_window_toggle_fullscreen(void);

/// If true, the window is closing
bool st_window_closing(void);

/// Requests the window to be closed. This doesn't free the window stuff.
void st_window_request_close(void);

/// Frees the window and stuff.
void st_window_free();

/// If true, there is, in fact, a window
bool st_window_is_ready();

/// Returns seconds since the window was opened
f64 st_window_get_time();

/// Returns time between frames in seconds. Look up delta time
f64 st_window_get_delta_time();

/// Returns the frame rate the game is running at
i64 st_window_get_fps();

/// Gets the window size in pixels
StVec2i st_window_get_size();