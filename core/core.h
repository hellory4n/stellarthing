#pragma once
#include <__stdarg_va_list.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/// Random "size"s everywhere would be weird. This is equivalent to an uint64 on most pcs i think
typedef size_t nint;

/// 8-bit signed integer
typedef int8_t i8;
/// 16-bit signed integer
typedef int16_t i16;
/// 32-bit signed integer
typedef int32_t i32;
/// 64-bit signed integer
typedef int64_t i64;

/// 8-bit unsigned integer
typedef uint8_t u8;
/// 16-bit unsigned integer
typedef uint16_t u16;
/// 32-bit unsigned integer
typedef uint32_t u32;
/// 64-bit unsigned integer
typedef uint64_t u64;

/// 32-bit floating point number
typedef float f32;
/// 64-bit floating point number
typedef double f64;

// os crap
#if defined(_WIN32)
	#ifndef ST_WINDOWS
		#define ST_WINDOWS
	#endif
#elif defined(__unix__)
	#ifndef ST_LINUXBSD
		#define ST_LINUXBSD
	#endif
#endif

// versions
#ifndef ST_STARRY_VERSION
/// The engine version
#define ST_STARRY_VERSION "v4.1.0"
#endif

#ifndef ST_GAME_VERSION
/// The game version
#define ST_GAME_VERSION "v1.1.0"
#endif

/// `assert` is busted
void st_assert(bool x, const char* msg);

/// Similar to printf, but it also writes to a log file and adds a line break against your will
void st_log(const char* format, ...);

/// This is just the callback raylib is gonna use for logging
void st_rl_log_callback(i32 level, const char* text, va_list args);

/// uh
void st_init_logging(void);

/// uh
void st_free_logging(void);