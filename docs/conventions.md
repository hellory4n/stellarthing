# Conventions

## Naming

Types are in `PascalCase`, e.g. `StObject`

Please note acronyms and abbreviations are NOT capitalized, so for example it would be `Id`, not `ID`

Functions are in `snake_case`, e.g. `the_function`

Macros start with `ST_` and are in `UPPER_CASE`, e.g. `ST_IDK_MAN`

If you have something that's supposed to be private, put a `__` at the start, e.g. `__murder`

You should use `this`

## Spacing

Indentation is 4 spaces.

Brackets are K&R style:

```cpp
int main(int argc, char *argv[])
{
    while (x == y) {
        do_something();
        do_something_else();
    }
    final_thing();
}
```

You may think the functions being different is inconsistent, to which I say "wrong."

If-else statements are a bit different:

```cpp
if (is_busted) {
    die();
}
else {
    not_die();
}
```

Don't do this though:
```cpp
if (is_busted)
    die();
else
    not_die();
```

You're only allowed to have blocks without braces if it's tiny and on one line:

```cpp
if (is_busted) die();
else not_die();
```

Otherwise just use braces

```cpp
if (very_long_variable_name_agsrjhyrshyiuuydjt) {
    very_long_function_name_ugugujgu();
}
```

Switch statements are formatted like this:

```cpp
switch (something) {
case 1:
    do_something();
    break;

case 2:
    do_something();
    break;
}
```

This is also allowed:

```cpp
switch (something) {
    case 1: do_something(); break;
    case 2: do_something(); break;
}
```

Pointers are aligned with the types, as it changes the type

```cpp
// do this
Mate* mate;
// not this
Mate *mate;
```

Documentation has 3 slashes:
```cpp
/// This does something.
void man();
```

## Misc

Functions with error handling should return true if they succeeded, and false otherwise

```cpp
bool function_that_busts()
{
    printf("Oh look, function's busted.\n");
    return false;
}

if (!function_that_busts()) {
    printf("the function busted :(\n");
}
else {
    printf("yippeee\n");
}
```

But if the functions are supposed to return something, return null if it fails

Use `const char*` for strings, conveniently UTF-8 supports comes (mostly) for free

Use `core/core.hpp` numbers instead of `stdint.h`, they're mostly the same except without the `_t` and `size_t` is `nint` (native int) because having "size" everywhere would be weird

Use include guards instead of `#pragma once`. Why? Sometimes `#pragma once` busted with global variables in C so I think include guards are safer

Includes should be in this order:
- Standard library stuff
- Other third party stuff (`lib` folder)
- `src/core` folder
- `src/modules` folder
- `src/game` folder
- If it's a `.cpp` file, include the header file last

Speaking of header files, use the `.hpp` extension, not `.h`. `.h` is for C.

In my humble opinion, the STL is a piece of crap and you should avoid it at all costs.

Use C libraries and the `core` folder instead.

## More C++ insanity

Don't initialize stuff like this:

```cpp
ObjectObject obj;
```

It looks weird.

Do this instead:

```cpp
ObjectObject obj = ObjectObject();
// or
// auto is allowed here because you can see the type
auto obj = ObjectObject();
```

Speaking of auto, you should only use it in variables when using a constructor:

```cpp
// allowed
auto obj = ObjectObject();

// not allowed
auto obj = get_object();

// dear god
auto func(auto param);
```