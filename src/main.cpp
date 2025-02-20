#include <stdio.h>
#include "core/vectors.hpp"
#include "core/collections/tuple.hpp"
#include "core/collections/list.hpp"
#include "core/collections/hashmap.hpp"

int main(int argc, char const *argv[])
{
    // cant be bothered
    using namespace starry;

    vec2 wec2 = vec2(1, 2) + vec2(1, 2);
    vec2i wec2i = vec2i(1, 2) + vec2i(1, 2);
    vec3 wec3 = vec3(1, 2, 3) + vec3(1, 2, 3);
    vec3i wec3i = vec3i(1, 2, 3) + vec3i(1, 2, 3);
    printf("vec2: %f, %f\n", wec2.x, wec2.y);
    printf("vec2i: %li, %li\n", wec2i.x, wec2i.y);
    printf("vec3: %f, %f, %f\n", wec3.x, wec3.y, wec3.z);
    printf("vec3i: %li, %li, %li\n", wec3i.x, wec3i.y, wec3i.z);

    auto mate = Tuple2<int64, int64>(69, 420);
    printf("tuple: %li, %li\n", mate.item1, mate.item2);

    auto leliste = new List<int64>(0);
    leliste->add(69);
    leliste->add(420);
    leliste->add(69420);
    leliste->add(42069);
    leliste[3] = -5;
    for (nint i = 0; i < leliste->length; i++) {
        printf("list: %li\n", leliste[i]);
    }

    auto lehashmape = new HashMap<const char, const char>();
    lehashmape->set("mate", "matemate");
    lehashmape->set("the sigma", "®®®®®®");
    lehashmape->set("mate", "BLAH BLAH BLAH BLAH BLAH BLAH BLAH BLAH BLAH BLAH");
    printf("Mate %s\n", lehashmape->get("mate"));
    printf("Mate %s\n", lehashmape->get("the sigma"));
    return 0;
}
