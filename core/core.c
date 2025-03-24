#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "core.h"

void st_assert(bool x, const char* msg)
{
	if (!x) {
		st_log("failed assert: %s\n", msg);
		exit(1);
	}
}

FILE* logfile;

void st_init_logging(void)
{
	logfile = fopen("log.txt", "w");
	st_assert(logfile != NULL, "couldn't open log file");
}

void st_free_logging(void)
{
	fclose(logfile);
}

void st_log(const char* format, ...)
{
	// you understand mechanical hands are the ruler of everything (ah)
	char timestr[64];
	time_t now = time(NULL);
	struct tm* tm_info = localtime(&now);
	strftime(timestr, sizeof(timestr), "%Y-%m-%d %H:%M:%S", tm_info);

	// TODO maybe increase in the future?
	char buf[256];
	va_list args;
	va_start(args, format);
	vsnprintf(buf, 256, format, args);

	fprintf(logfile, "[%s] %s\n", timestr, buf);
	printf("[%s] %s\n", timestr, buf);
	fflush(logfile);
	fflush(stdout);

	va_end(args);
}

void st_rl_log_callback(i32 level, const char* text, va_list args)
{
	const char* prefix;
	// i'm not including the entirety of raylib for some enums
	switch (level) {
		case 3: prefix = "raylib info:"; break;
		case 4: prefix = "raylib warning:"; break;
		case 5: prefix = "raylib error:"; break;
		case 6: prefix = "raylib fatal:"; break;
		default: prefix = "raylib:"; break;
	}

	// you understand mechanical hands are the ruler of everything (ah)
	char timestr[64];
	time_t now = time(NULL);
	struct tm* tm_info = localtime(&now);
	strftime(timestr, sizeof(timestr), "%Y-%m-%d %H:%M:%S", tm_info);

	char buf[256];
	vsnprintf(buf, 256, text, args);
	// it's intentionally inconsistent so i can easily separate out the raylib spam
	fprintf(logfile, "%s [%s] %s\n", prefix, timestr, buf);
	printf("%s [%s] %s\n", prefix, timestr, buf);
	fflush(logfile);
	fflush(stdout);
}