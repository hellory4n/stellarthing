#include "core/collections/stlist.h"
#include "modules/platform/window.h"
#include "timer.h"

/// list of timers
StList* __st_timers__;

void __st_init_timers__()
{
    __st_timers__ = StList_new(0);
}

void __st_update_timers__()
{
    for (nint i = 0; i < __st_timers__->length; i++) {
        StTimer* timer = __st_timers__->items[i];
        if (!timer->playing) continue;

        timer->time_left -= StWindow_get_delta_time();
        
        if (timer->time_left < 0.1) {
            timer->timeout(timer);
            timer->loops++;
            if (timer->repeat) {
                timer->time_left = timer->duration;
            }
        }
    }
}

void __st_free_timers__()
{
    StList_free_with_items(__st_timers__);
}

StTimer* StTimer_new(float64 duration, bool repeat, void (*timeout)(StTimer*))
{
    StTimer* timer = malloc(sizeof(StTimer));
    timer->repeat = repeat;
    timer->playing = false;
    timer->time_left = duration;
    timer->duration = duration;
    timer->loops = 0;
    timer->timeout = timeout;
    
    StList_add(__st_timers__, timer);
    return timer;
}

void StTimer_start(StTimer* timer)
{
    timer->playing = true;
    timer->time_left = timer->duration;
}