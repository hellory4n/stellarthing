# Core

`core.h` has some numbers e.g. `i32`, `u8`, `f64`

There's also assert (`st_assert` e.g. `st_assert(0 == 0, "it seems the fabric of reality has corrupted")`),
and `st_log`, which is like `printf` but with a newline and it also writes to a log file (`log.txt`)

There's vectors and colors and rectangles

```c
#include "core/math/vec.h"
#include "core/math/color.h"
#include "core/math/rect.h"

StVec2 vec2 = {1.0, 2.0};
StVec2i vec2i = {1, 2};
StVec3 vec3 = {1.0, 2.0, 3.0};
StVec3i vec3i = {1, 2, 3};
StRect rect = {1, 2, 3, 4};
StColor color = st_rgb(255, 255, 255);
```

array but it grow

```c
#include "core/list.h"

// if you don't know how big it's gonna be, use 0
StList* list = StList_new(capacity);

StList_add(list, something);
Thingamabob* mm = StList_at(list, 0);
StList_set(mm, 0, something_else);

// iterate over a list
for (nint i = 0; i < list->length; i++) {
	Thingamabob* item = StList_at(list, i);
}

StList_free(list);
```

mashhap

```c
#include "core/hashmap.h"

StHashMap* map = StHashMap_new(capacity);

StHashMap_set(map, "map_deez", something);
Thingamabob* mm = StHashMap_get(map, "map_deez");

// iterate over a hashmap
StListKeyValue* items = StHashMap_items(map);
for (nint i = 0; i < items->length, i++) {
	StKeyValue* kv = StList_at(items, i);
}
StList_free(items);

StHashMap_free(map);
```

stack deez

```c
#include "core/stack.h"

StStack* pain = StStack_new();
StStack_push(something);
while (pain->length > 0) {
	Thingamabob* sir = StStack_pop(pain);
}
StStack_free(pain);
```
