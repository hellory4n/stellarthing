#pragma once
#include "core/core.h"

/// it's a timer.
typedef struct StTimer {
    /// if true the timer is gonna repeat when it's over
    bool repeat;
    /// if true, the timer is playing
    bool playing;
    /// how much time until the timer is done, in seconds
    float64 time_left;
    /// how long the timer lasts for, in seconds
    float64 duration;
    /// how many times the timer has repeated
    uint64 loops;
    /// called when the timer is over
    void (*timeout)(struct StTimer*)
} StTimer;

/// @brief makes a timer
/// @param duration how long the timer lasts, in seconds
/// @param repeat if true, the timer is gonna repeat when it's over 
/// @param timeout callback for when the timer is over
/// @return timer
StTimer* StTimer_new(float64 duration, bool repeat, void (*timeout)(StTimer*));

/// starts the timer
void StTimer_start(StTimer* timer);

void __st_init_timers__();

void __st_update_timers__();

void __st_free_timers__();