#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>
#include <stdio.h>
#include <string.h>
#include "graphics.h"
#include "core/math/math.h"
#include "platform/input.h"

StObject3D objs[ST_MAX_3D_OBJECTS];
nint obj_len = 0;

void st_clear(StColor color)
{
	BeginDrawing();
	ClearBackground((Color){ .r = color.r, .g = color.g, .b = color.b, .a = color.a });
}

void st_end_drawing(void)
{
	EndDrawing();
}

void st_draw_texture(StTexture* texture, StVec2 pos, f64 degrees)
{
	st_draw_texture_ext(
		texture,
		(StVec2){0, 0},
		(StVec2){texture->width, texture->height},
		pos,
		(StVec2){texture->width, texture->height},
		(StVec2){0.5, 0.5},
		degrees,
		ST_WHITE
	);
}

void st_draw_texture_ext(StTexture* texture, StVec2 src_pos, StVec2 src_size, StVec2 dst_pos,
	StVec2 dst_size, StVec2 origin, f64 degrees, StColor tint)
{
	// akson dendryt
	DrawTexturePro(
		(Texture2D){
			.id = texture->id,
			.width = texture->width,
			.height = texture->height,
			.format = texture->format,
			.mipmaps = texture->mipmaps,
		},
		(Rectangle){ .x = src_pos.x, .y = src_pos.y, .width = src_size.x, .height = src_size.y },
		(Rectangle){ .x = dst_pos.x, .y = dst_pos.y, .width = dst_size.x, .height = dst_size.y },
		(Vector2){ .x = origin.x * dst_size.x, .y = origin.y * dst_size.y },
		degrees,
		(Color){ .r = tint.r, .g = tint.g, .b = tint.b, .a = tint.a }
	);
}

Camera3D rlcam;
StCamera stcam;
// enable with f5
bool wireframe_mode = false;
Shader light_shader;

void st_init_lighting()
{
	light_shader = LoadShader("assets/light.vert", "assets/light.frag");
	Vector3 light_dir = { -0.5f, -1.0f, -0.5f };
	SetShaderValue(light_shader, GetShaderLocation(light_shader, "lightDir"), &light_dir, SHADER_UNIFORM_VEC3);

	Vector4 ambient = { 0.2f, 0.2f, 0.2f, 1.0f };
	SetShaderValue(light_shader, GetShaderLocation(light_shader, "ambient"), &ambient, SHADER_UNIFORM_VEC4);
}

void st_free_lighting()
{
	UnloadShader(light_shader);
}

StCamera st_camera(void)
{
	return stcam;
}

/// Sets the current camera
void st_set_camera(StCamera cam)
{
	stcam = cam;
	rlcam = (Camera3D){
		.position = (Vector3){cam.position.x, cam.position.y, cam.position.z},
		.target = (Vector3){cam.target.x, cam.target.y, cam.target.z},
		.fovy = cam.fov,
		.up = (Vector3){0, 1, 0},
		.projection = cam.perspective ? CAMERA_PERSPECTIVE : CAMERA_ORTHOGRAPHIC,
	};
}

/// As the name implies, it draws a 3D object
void st_draw_object_3d(StObject3D obj)
{
	// not a huge fan of segfaults
	if (obj_len >= ST_MAX_3D_OBJECTS) {
		st_log("[GRAPHICS] Couldn't render object; object limit was achieved (%i objects)", ST_MAX_3D_OBJECTS);
		return;
	}

	objs[obj_len] = obj;
	obj_len++;
}

/// Does exactly what the name says
void st_draw_all_3d_objects(void)
{
	if (st_is_key_just_pressed(ST_KEY_F5)) {
		wireframe_mode = !wireframe_mode;
	}

	BeginMode3D(rlcam);

	// why not
	DrawGrid(100, 1);

	if (wireframe_mode) {
		rlEnableWireMode();
	}
	else {
		BeginShaderMode(light_shader);
	}

	// we don't iterate over the max objs because what if i make that ridiculously big
	// it'll be wasting time on nothing
	for (nint i = 0; i < obj_len; i++) {
		StObject3D obj = objs[i];

		// raylib's DrawModelEx() has a weird rotation parameter
		// to get our full fancy rotation we have to make our own drawing
		// this is just raylib's DrawModelEx() with the rotation fixed

		// Calculate transformation matrix from function parameters
		// Get transform matrix (rotation -> scale -> translation)
		Matrix mat_scale = MatrixScale(obj.scale.x, obj.scale.y, obj.scale.z);
		Matrix mat_rotation = MatrixRotateXYZ((Vector3){st_deg2rad(obj.rotation.x), st_deg2rad(obj.rotation.y), st_deg2rad(obj.rotation.z)});
		Matrix mat_translation = MatrixTranslate(obj.position.x, obj.position.y, obj.position.z);

		Matrix mat_transform = MatrixMultiply(MatrixMultiply(mat_scale, mat_rotation), mat_translation);

		// Combine model transformation matrix (model.transform) with matrix generated by function parameters (matTransform)
		Model model = *(Model*)obj.model;
		model.transform = MatrixMultiply(MatrixIdentity(), mat_transform);

		for (int i = 0; i < model.meshCount; i++) {
			Color color = model.materials[model.meshMaterial[i]].maps[MATERIAL_MAP_DIFFUSE].color;

			Color color_tint = WHITE;
			color_tint.r = (unsigned char)(((int)color.r*(int)obj.tint.r)/255);
			color_tint.g = (unsigned char)(((int)color.g*(int)obj.tint.g)/255);
			color_tint.b = (unsigned char)(((int)color.b*(int)obj.tint.b)/255);
			color_tint.a = (unsigned char)(((int)color.a*(int)obj.tint.a)/255);

			if (!wireframe_mode) {
				model.materials[model.meshMaterial[i]].shader = light_shader;
				Vector4 please = {color_tint.r / 256.0f, color_tint.g / 256.0f, color_tint.b / 256.0f, color_tint.a / 256.0f};
				SetShaderValue(light_shader, GetShaderLocation(light_shader, "materialColor"), &please, SHADER_UNIFORM_VEC4);
			}
			else {
				// use default shader
				model.materials[model.meshMaterial[i]].shader = LoadShader(NULL, NULL);
			}
			model.materials[model.meshMaterial[i]].maps[MATERIAL_MAP_DIFFUSE].color = color_tint;
			DrawMesh(model.meshes[i], model.materials[model.meshMaterial[i]], model.transform);
			model.materials[model.meshMaterial[i]].maps[MATERIAL_MAP_DIFFUSE].color = color;
		}
	}

	if (wireframe_mode) {
		rlDisableWireMode();
	}
	else {
		EndShaderMode(); // light_shader
	}
	EndMode3D();

	// it'll just start overwriting things
	obj_len = 0;
}