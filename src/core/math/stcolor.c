#include "stcolor.h"

stcolor stcolor_new(uint8 r, uint8 g, uint8 b, uint8 a)
{
    return (stcolor){
        .r = r,
        .g = g,
        .b = b,
        .a = a,
    };
}