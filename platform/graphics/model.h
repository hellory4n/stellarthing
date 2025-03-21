#pragma once

// I can't include raylib in my header files
typedef void StModel;

void st_init_models(void);

void st_free_models(void);

// Loads a model. Must be in GLTF/GLB format
StModel* StModel_new(const char* path);

// Frees a model.
void StModel_free(StModel* m);
