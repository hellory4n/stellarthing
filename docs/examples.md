# Examples

## Vectors

They exist.

There's vec2, vec3, and for integer versions there's vec2i and vec3i.

```cpp
#include "core/vectors.hpp"
using namespace starry;

vec2 a = vec2(1, 2);
vec2 b = vec2(3, 4);
vec2 c = a + b;
printf("%f, %f\n", c.x, c.y);
```

## Lists

They're like arrays, but dynamically sized.

Similar to `std::vector`

```cpp
#include "core/collections/list.hpp"
using namespace starry;

auto mate = new List<int32>();
mate->add(1);
mate->add(2);
mate->set(0, 50);
printf("%f\n", mate->at(0));
```

## Hashmaps

Hashmaps exists too.

Similar to `std::unordered_map`

```cpp
#include "core/collections/hashmap.hpp"
#include "core/string.hpp"
using namespace starry;

auto map = new HashMap<const char*, const char*>();
map->set("key", "value");
printf("%s", map->get("key"));
```