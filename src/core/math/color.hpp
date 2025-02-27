#ifndef ST_COLOR_H
#define ST_COLOR_H
#include "core/core.hpp"

namespace starry {

struct Color {
    /// red
    uint8 r = 0;
    /// green
    uint8 g = 0;
    /// blue
    uint8 b = 0;
    /// alpha
    uint8 a = 0;

    Color(uint8 r, uint8 g, uint8 b) {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = 255;
    }

    Color(uint8 r, uint8 g, uint8 b, uint8 a) {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }
};

/// white
#define ST_COLOR_WHITE Color(255, 255, 255, 255)

/// black
#define ST_COLOR_BLACK Color(0, 0, 0, 255)

/// transparent
#define ST_COLOR_TRANSPARENT Color(0, 0, 0, 0)

}

#endif // ST_COLOR_H
