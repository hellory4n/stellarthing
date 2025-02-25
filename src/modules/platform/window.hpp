#ifndef ST_WINDOW_H
#define ST_WINDOW_H
#include "core/math/vec2i.hpp"
#include "core/string.hpp"

namespace starry {

/// window
namespace window {
    /// makes a window
    void open(String title, Vec2i size);

    /// toggles fullscreen
    void toggle_fullscreen();

    /// if true, the window is closing
    bool closing();

    /// requests the window to be closed
    void request_close();

    /// updates the window. put this at the end of your main loop
    void update();

    /// sets the target frames per second
    void set_target_fps(uint32 fps);

    /// frees the window. if you want to kindly ask it to close, call `request_close()`
    void close();

    /// if true, there is, in fact, a window
    bool is_ready();

    /// returns seconds since the window was opened
    float64 get_time();

    /// returns time between frames in seconds. look up delta time
    float64 get_delta_time();

    /// returns the frame rate the game is running at
    int64 get_fps();
}

}

#endif // ST_WINDOW_H
