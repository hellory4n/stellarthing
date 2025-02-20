#ifndef ST_COLOR_H
#define ST_COLOR_H
#include "core/core.hpp"

namespace starry {

struct color {
    /// red
    uint8 r;
    /// green
    uint8 g;
    /// blue
    uint8 b;
    /// alpha
    uint8 a;

    color(uint8 r, uint8 g, uint8 b) {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = 255;
    }

    color(uint8 r, uint8 g, uint8 b, uint8 a) {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }
};

/// white
#define COLOR_WHITE color(255, 255, 255, 255)

/// black
#define COLOR_BLACK color(0, 0, 0, 255)

/// transparent
#define COLOR_TRANSPARENT color(0, 0, 0, 0)

}

#endif // ST_COLOR_H