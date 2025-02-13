#include <math.h>
#include "core/collections/stlist.h"
#include "modules/platform/window.h"
#include "tween.h"

typedef struct {
    float64* prop;
    float64 from;
    float64 to;
    float64 duration;
    float64 elapsed;
    StEasingType easing;
    bool active;
} StTweenf;

typedef struct {
    stvec2* prop;
    stvec2 from;
    stvec2 to;
    float64 duration;
    float64 elapsed;
    StEasingType easing;
    bool active;
} StTweenv2;

typedef struct {
    stcolor* prop;
    stcolor from;
    stcolor to;
    float64 duration;
    float64 elapsed;
    StEasingType easing;
    bool active;
} StTweenc;

StList* __st_float_tweens__;
StList* __st_vec2_tweens__;
StList* __st_color_tweens__;

float64 __st_ease__(float64 t, StEasingType type)
{
    switch (type) {
    case ST_EASING_LINEAR:
        return t;
        break;
    case ST_EASING_QUAD_IN:
        return t * t;
        break;
    case ST_EASING_QUAD_OUT:
        return 1 - (1 - t) * (1 - t);
        break;
    case ST_EASING_QUAD_IN_OUT:
        return t < 0.5 ? 2 * t * t : 1 - pow(-2 * t + 2, 2) / 2;
        break;
    default:
        // you legumes
        return -1;
        break;
    }
}

void __st_init_tweens__()
{
    __st_float_tweens__ = StList_new(0);
    __st_vec2_tweens__ = StList_new(0);
    __st_color_tweens__ = StList_new(0);
}

void __st_update_tweens__()
{
    for (nint i = 0; i < __st_float_tweens__->length; i++) {
        StTweenf* tween = __st_float_tweens__->items[i];
        if (!tween->active) continue;

        tween->elapsed += StWindow_get_delta_time();
        if (tween->elapsed >= tween->duration) {
            // snap to the end value
            *(tween->prop) = tween->to;
            // it's joever
            tween->active = false;
            continue;
        }

        // actually tween
        float64 t = tween->elapsed / tween->duration;
        *(tween->prop) = tween->from + (tween->to - tween->from) * __st_ease__(t, 
            tween->easing);
    }

    for (nint i = 0; i < __st_vec2_tweens__->length; i++) {
        StTweenv2* tween = __st_vec2_tweens__->items[i];
        if (!tween->active) continue;

        tween->elapsed += StWindow_get_delta_time();
        if (tween->elapsed >= tween->duration) {
            // snap to the end value
            *(tween->prop) = tween->to;
            // it's joever
            tween->active = false;
            continue;
        }

        // actually tween
        float64 t = tween->elapsed / tween->duration;
        // my vectors suck but i cant be bothered to fix them
        *(tween->prop) = stvec2_mul(stvec2_add(tween->from, stvec2_sub(tween->to, tween->from)),
            (stvec2){ __st_ease__(t, tween->easing), __st_ease__(t, tween->easing) });
    }

    for (nint i = 0; i < __st_color_tweens__->length; i++) {
        StTweenc* tween = __st_color_tweens__->items[i];
        if (!tween->active) continue;

        tween->elapsed += StWindow_get_delta_time();
        if (tween->elapsed >= tween->duration) {
            // snap to the end value
            *(tween->prop) = tween->to;
            // it's joever
            tween->active = false;
            continue;
        }

        // actually tween
        float64 t = tween->elapsed / tween->duration;
        // man
        *(tween->prop) = (stcolor){
            (uint8)(tween->from.r + (tween->to.r - tween->from.r) * __st_ease__(t, tween->easing)),
            (uint8)(tween->from.g + (tween->to.g - tween->from.g) * __st_ease__(t, tween->easing)),
            (uint8)(tween->from.b + (tween->to.b - tween->from.b) * __st_ease__(t, tween->easing)),
            (uint8)(tween->from.a + (tween->to.a - tween->from.a) * __st_ease__(t, tween->easing))
        };
    }
}

void __st_free_tweens__()
{
    StList_free_with_items(__st_float_tweens__);
    StList_free_with_items(__st_vec2_tweens__);
    StList_free_with_items(__st_color_tweens__);
}

/// tweens a float property :) (duration is in seconds)
void StTween_float(float64* prop, float64 from, float64 to, float64 duration, StEasingType easing)
{
    // TODO don't malloc idiot
    StTweenf* tween = malloc(sizeof(StTweenf));
    tween->prop = prop;
    tween->from = from;
    tween->to = to;
    tween->duration = duration;
    tween->elapsed = 0;
    tween->easing = easing;
    tween->active = true;
    StList_add(__st_float_tweens__, tween);
}

/// tweens a vec2 property :) (duration is in seconds)
void StTween_vec2(stvec2* prop, stvec2 from, stvec2 to, float64 duration, StEasingType easing)
{
    // TODO don't malloc idiot
    StTweenv2* tween = malloc(sizeof(StTweenv2));
    tween->prop = prop;
    tween->from = from;
    tween->to = to;
    tween->duration = duration;
    tween->elapsed = 0;
    tween->easing = easing;
    tween->active = true;
    StList_add(__st_vec2_tweens__, tween);
}

/// tweens a color property :) (duration is in seconds)
void StTween_color(stcolor* prop, stcolor from, stcolor to, float64 duration, StEasingType easing)
{
    // TODO don't malloc idiot
    StTweenc* tween = malloc(sizeof(StTweenc));
    tween->prop = prop;
    tween->from = from;
    tween->to = to;
    tween->duration = duration;
    tween->elapsed = 0;
    tween->easing = easing;
    tween->active = true;
    StList_add(__st_color_tweens__, tween);
}