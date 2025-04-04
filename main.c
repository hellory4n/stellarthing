#include "libtrippin.h"
#include "raylib.h"

void frame() {
	BeginDrawing();

	ClearBackground(RAYWHITE);

	DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

	EndDrawing();
}

int main(int argc, const char* argv[]) {
	InitWindow(800, 450, "stellarthing");
	tr_init("log.txt");
	tr_log(TR_LOG_INFO, "man");

	SetTargetFPS(60);

	while(!WindowShouldClose()) {
		frame();
	}
	CloseWindow();

	tr_free();
	return 0;
}