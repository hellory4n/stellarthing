#include <stdio.h>
#include "modules/platform/window.h"
#include "core/collections/sthashmap.h"
#include "core/collections/sttuple.h"

int main(int argc, char const *argv[])
{
    // mann
    StHashMap* man = StHashMap_new(0);
    StHashMap_set(man, "mate", "mann");
    StHashMap_set(man, "dude, dude, dude, what?", "GOOD NEWS GOOD NEWS GOOD NEWS");

    StList* oy = StHashMap_items(man);
    for (nint i = 0; i < oy->length; i++) {
        StTuple2* mate = StList_at(oy, i);
        printf("Mmm: %s: %s\n", mate->item1, mate->item2);
    }
    StList_free_with_items(oy);

    StHashMap_free(man);

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
