#pragma once
#include "core/core.h"

/// initializes the extension system
void StExtensions_new();

/// frees the extension system
void StExtensions_free();

/// runs a lua file
void StExtensions_run(const char* path);