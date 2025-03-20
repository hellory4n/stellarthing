#include <stdio.h>
#include <raylib.h>
#include "core/hashmap.h"
#include "core/list.h"
#include "texture.h"

StHashMap* textures;

void __st_init_textures__(void)
{
	textures = StHashMap_new(0);
}

void __st_free_textures__(void)
{
	// free items in the hashmap
	StList* items = StHashMap_items(textures);
	for (nint i = 0; i < items->length; i++) {
		StTexture_free(((StKeyValue*)items->data[i])->val);
		printf("[ASSETS] Freed texture at %s\n", (char*)((StKeyValue*)items->data[i])->val);
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

	printf("[ASSETS] Loaded texture at %s\n", path);
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