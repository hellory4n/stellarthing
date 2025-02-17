#pragma once
#include "core/core.h"
#include "core/vectors.h"
#include "core/math/stcolor.h"

typedef enum {
    ST_EASING_LINEAR,
    ST_EASING_QUAD_IN,
    ST_EASING_QUAD_OUT,
    ST_EASING_QUAD_IN_OUT,
} StEasingType;

void __st_init_tweens__();

void __st_update_tweens__();

void __st_free_tweens__();

/// tweens a float property :) (duration is in seconds)
void StTween_float(float64* prop, float64 from, float64 to, float64 duration, StEasingType easing);

/// tweens a vec2 property :) (duration is in seconds)
void StTween_vec2(stvec2* prop, stvec2 from, stvec2 to, float64 duration, StEasingType easing);

/// tweens a vec3 property :) (duration is in seconds)
void StTween_vec3(stvec3* prop, stvec3 from, stvec3 to, float64 duration, StEasingType easing);

/// tweens a color property :) (duration is in seconds)
void StTween_color(stcolor* prop, stcolor from, stcolor to, float64 duration, StEasingType easing);