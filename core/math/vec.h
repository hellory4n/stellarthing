#pragma once
#include "core/core.h"

/// Vector2 with floats
typedef struct {
	/// x
	f64 x;
	/// y
	f64 y;
} StVec2;

/// Vector2 with ints
typedef struct {
	/// x
	i64 x;
	/// y
	i64 y;
} StVec2i;

/// Vector3 with floats
typedef struct {
	/// x
	f64 x;
	/// y
	f64 y;
	/// z
	f64 z;
} StVec3;

/// Vector3 with ints
typedef struct {
	/// x
	i64 x;
	/// y
	i64 y;
	/// z
	i64 z;
} StVec3i;

// Version.
typedef StVec3i StVersion;