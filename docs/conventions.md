# Conventions

## Naming

Types start with `St` and are in `PascalCase`, e.g. `StObject`

Functions start with `st_` and are in `camel_case`, e.g. `st_log`

Member functions start with the type name and then are in `camel_case`, e.g. `StObject_annihilate_all_that_has_ever_lived`

Macros start with `ST_` and are in `UPPER_CASE`, e.g. `ST_IDK_MAN`

If you have something that's supposed to be private, put it between `__`, e.g. `__st_murder__`

Constructors are called `new` and destructors are called `free`, e.g. `StObject_new`, `StObject_free`

For member functions, instead of something like `self` or `this`, have the first letter of the type instead, e.g. `StEntity_update(StEntity* e);`

Arrays should have the actual array as `<name>v` along with the length as `<name>c`

## Spacing

Indentation is 4 spaces.

Brackets are K&R style:

```c
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

```c
if (is_busted) {
    die();
}
else {
    not_die();
}
```

Don't do this though:
```c
if (is_busted)
    die();
else
    not_die();
```

You're only allowed to have blocks without braces if it's tiny and on one line:

```c
if (is_busted) die();
else not_die();
```

Otherwise just use braces

```c
if (very_long_variable_name_agsrjhyrshyiuuydjt) {
    very_long_function_name_ugugujgu();
}
```

Switch statements are formatted like this:

```c
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

```c
switch (something) {
    case 1: do_something(); break;
    case 2: do_something(); break;
}
```

Pointers are aligned with the types, as it changes the type

```c
// do this
Mate* mate;
// not this
Mate *mate;
```

Documentation has 3 slashes:
```c
/// This does something.
void man();
```

## Misc

Functions with error handling should return true if they succeeded, and false otherwise

```c
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

Use `core/core.h` numbers instead of `stdint.h`, they're mostly the same except without the `_t` and `size_t` is `nint` (native int) because having "size" everywhere would be weird

Use `#pragma once`.

Includes should be in this order:
- Standard library stuff
- Other third party stuff (raylib, `src/lib`)
- Starry stuff
- Game stuff