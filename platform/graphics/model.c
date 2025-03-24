#include "core/hashmap.h"
#include "core/list.h"
#include "raylib.h"
#include "model.h"

typedef StHashMap StHashMapStringModel;
StHashMapStringModel* models;

void st_init_models(void)
{
	models = StHashMap_new(0);
}

void st_free_models(void)
{
	StListKeyValue* items = StHashMap_items(models);
	for (nint i = 0; i < items->length; i++) {
		StKeyValue* kvp = StList_at(items, i);
		StModel_free(kvp->val);
		st_log("[ASSETS] Freed model at %s", kvp->key);
	}
	StList_free_all(items);

	StHashMap_free(models);
}

StModel* StModel_new(const char* path)
{
	if (!StHashMap_contains(models, path)) {
		Model sir = LoadModel(path);
		Model* sir_with_a_chance_of_segfault = malloc(sizeof(Model));
		*sir_with_a_chance_of_segfault = sir;
		StHashMap_set(models, path, sir_with_a_chance_of_segfault);
		st_log("[ASSETS] Loaded model at %s", path);
	}

	return StHashMap_get(models, path);
}

void StModel_free(StModel* m)
{
	UnloadModel(*(Model*)m);
	free(m);
}