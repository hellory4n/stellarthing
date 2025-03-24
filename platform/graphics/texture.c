#include <raylib.h>
#include "core/hashmap.h"
#include "core/list.h"
#include "texture.h"

StHashMap* textures;

void st_init_textures(void)
{
	textures = StHashMap_new(0);
}

void st_free_textures(void)
{
	// free items in the hashmap
	StList* items = StHashMap_items(textures);
	for (nint i = 0; i < items->length; i++) {
		StTexture_free(((StKeyValue*)items->data[i])->val);
		st_log("[ASSETS] Freed texture at %s", (char*)((StKeyValue*)items->data[i])->key);
	}
	StList_free_all(items);

	StHashMap_free(textures);
}

StTexture* StTexture_new(const char* path)
{
	// loading the same textures 385980320859 times isn't very salubrious
	if (StHashMap_contains(textures, path)) {
		return StHashMap_get(textures, path);
	}

	StTexture* dog = malloc(sizeof(StTexture));
	Texture2D mate = LoadTexture(path);
	dog->id = mate.id;
	dog->width = mate.width;
	dog->height = mate.height;
	dog->mipmaps = mate.mipmaps;
	dog->format = mate.format;
	StHashMap_set(textures, path, dog);

	st_log("[ASSETS] Loaded texture at %s", path);
	return dog;
}

void StTexture_free(StTexture* t)
{
	// OH MY GAMMIT IT'S... tally hall
	Texture2D mmmm_mmmm_mmmm = {
		.id = t->id,
		.width = t->width,
		.height = t->height,
		.format = t->format,
		.mipmaps = t->mipmaps,
	};
	UnloadTexture(mmmm_mmmm_mmmm);
}