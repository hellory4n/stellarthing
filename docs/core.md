# Core

Basic classes and stuff because I don't like the STL.

## Arrays

They're like arrays, but less fucky.

They're stack allocated unless the size is bigger than 256, then it uses the heap instead

```cpp
#include "core/collections/array.hpp"
using namespace starry;

auto lol = Array<int32>(5);
*lol.at(0) = 789593;
printf("item at index 0: %li", *lol.at(0));
```

## Strings

Immutable UTF-8 strings :)

It's actually just an `Array<char>` so it's also stack allocated unless the size is bigger than 256.

```cpp
#include "core/string.hpp"
using namespace starry;

String hi = "太陽が漏れている。";
// usually you can just pass the string but it's explicit in printf so clang is happy
printf("%s\n", hi.cstr());
```

Formatting (similar to printf) is supported too:

```cpp
String fmt = String::fmt(256, "I have %i apples, but at what cost?", 678);
printf("%s\n", fmt.cstr());
```

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
*mate->at(0) = 50;
printf("%i\n", *mate->at(0));
```

## Hashmaps

Hashmaps exists too.

Similar to `std::unordered_map`

```cpp
#include "core/collections/hashmap.hpp"
#include "core/string.hpp"
using namespace starry;

auto map = new HashMap<String, String>();
map->set("key", "value");
printf("%s", map->get("key").cstr());
```