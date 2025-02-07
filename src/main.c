#include "raylib.h"
//#define NK_INCLUDE_FIXED_TYPES
//#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
//#define NK_INCLUDE_DEFAULT_ALLOCATOR
//#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
//#define NK_INCLUDE_FONT_BAKING
//#define NK_INCLUDE_DEFAULT_FONT
#define RAYLIB_NUKLEAR_IMPLEMENTATION
#define RAYLIB_NUKLEAR_INCLUDE_DEFAULT_FONT
#include "lib/raylib_nuklear.h"
#define LUA_IMPL
// TURNS OUT LUA INCLUDES WINDOWS.H AND THAT CONFLICTS WITH RAYLIB
//#include "lib/minilua.h"
#include "core/math/math.h"
#include <stdio.h>
#include "core/starry.h"

int main() {
    st_new();
    
    char shia_labuffer[11];
    st_rand_base64(10, shia_labuffer);
    st_log("hehehehhea", NULL, ST_LOG_TYPE_ADDRESS);
    printf("bmgmgm, %s\n", shia_labuffer);

    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(1280, 720, "Example");
    SetTargetFPS(144);

    // TURNS OUT LUA INCLUDES WINDOWS.H AND THAT CONFLICTS WITH RAYLIB
    // lua_State* L = luaL_newstate();
    // luaL_openlibs(L);
    // luaL_loadstring(L, "print 'hello from lua'");
    // lua_call(L, 0, 0);

    Font font = LoadFontFromNuklear(13);
    struct nk_context *ctx = InitNuklearEx(font, 13);
    struct nk_colorf bg = {
        .r = 0.10f,
        .g = 0.18f,
        .b = 0.24f,
        .a = 1.00f,
    };

    while (!WindowShouldClose()) {
        UpdateNuklear(ctx);
        
        BeginDrawing();
            ClearBackground(DARKGRAY);
            DrawText("Hello Raylib!", 10, 10, 20, RED);

            /* GUI */
            if (nk_begin(ctx, "Demo", nk_rect(50, 50, 230, 250),
                NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
                NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
            {
                enum {EASY, HARD};
                static int op = EASY;
                static int property = 20;

                nk_layout_row_static(ctx, 30, 80, 1);
                if (nk_button_label(ctx, "button"))
                    TraceLog(LOG_INFO, "button pressed!");
                nk_layout_row_dynamic(ctx, 30, 2);
                if (nk_option_label(ctx, "easy", op == EASY)) op = EASY;
                if (nk_option_label(ctx, "hard", op == HARD)) op = HARD;
                nk_layout_row_dynamic(ctx, 22, 1);
                nk_property_int(ctx, "Compression:", 0, &property, 100, 10, 1);

                nk_layout_row_dynamic(ctx, 20, 1);
                nk_label(ctx, "background:", NK_TEXT_LEFT);
                nk_layout_row_dynamic(ctx, 25, 1);
                if (nk_combo_begin_color(ctx, nk_rgb_cf(bg), nk_vec2(nk_widget_width(ctx),400))) {
                    nk_layout_row_dynamic(ctx, 120, 1);
                    bg = nk_color_picker(ctx, bg, NK_RGBA);
                    nk_layout_row_dynamic(ctx, 25, 1);
                    bg.r = nk_propertyf(ctx, "#R:", 0, bg.r, 1.0f, 0.01f,0.005f);
                    bg.g = nk_propertyf(ctx, "#G:", 0, bg.g, 1.0f, 0.01f,0.005f);
                    bg.b = nk_propertyf(ctx, "#B:", 0, bg.b, 1.0f, 0.01f,0.005f);
                    bg.a = nk_propertyf(ctx, "#A:", 0, bg.a, 1.0f, 0.01f,0.005f);
                    nk_combo_end(ctx);
                }
            }
            nk_end(ctx);

            DrawNuklear(ctx);
        EndDrawing();
    }

    UnloadNuklear(ctx);
    CloseWindow();
    // TURNS OUT LUA INCLUDES WINDOWS.H AND THAT CONFLICTS WITH RAYLIB
    //lua_close(L);

    return 0;
}