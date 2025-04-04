# Conventions

C can be tricky. That's why we choose conventions to make things less tricky.

## Style

Types are in `PascalCase`, e.g. `ObjectObject`

Please note acronyms and abbreviations are NOT capitalized, so for example it would be `ThingyId`, not `ThingyID`

Functions are in `snake_case`, e.g. `thingy_do_the_thing`

Macros start with `ST_` and are in `UPPER_CASE`, e.g. `ST_IDK_MAN`

If you have something that's supposed to be private, put a `__` prefix, e.g. `__st_send_nuke` (but private is bloat don't use this)

Constructors are called `new` and destructors are called `free`, e.g. `object_new`, `object_free`

Tabs are tabs with the size of 4 spaces

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

Documentation comments are just normal comments but with Very professional formatting.
```c
// This does something.
void man();
```

Use include guards

## Other crap

Use [libtrippin](https://github.com/hellory4n/libtrippin) and [stb_ds](https://nothings.org/stb_ds)

Functions with error handling should return true if they succeeded, and false otherwise

```c
bool function_that_busts()
{
    st_log("Oh look, function's busted.");
    return false;
}

if (!function_that_busts()) {
    st_log("the function busted :(");
}
else {
    st_log("yippeee");
}
```

But if the functions are supposed to return something, return null if it fails