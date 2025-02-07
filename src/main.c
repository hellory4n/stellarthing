#include <stdio.h>
#include "modules/platform/window.h"

int main(int argc, char const *argv[])
{
    StWindow_create("Stellarthing", stvec2i_new(640, 480));
    StWindow_set_fullscreen(true);
    StWindow_set_target_fps(144);

    if (!StWindow_closing()) {
        printf("help me axon dendrite\n");
        StWindow_update();
    }

    StWindow_free();
    return 0;
}
