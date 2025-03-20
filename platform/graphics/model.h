#pragma once

// I can't include raylib in my header files
typedef void StModel;

void __st_init_models(void);

void __st_free_models(void);

// Loads a model. Must be in OBJ format
StModel* StModel_new(const char* path);

// Frees a model.
void StModel_free(StModel* m);
