#include <stdio.h>
#include <stdlib.h>
#include "core.h"

void st_assert(bool x, const char* msg)
{
	if (!x) {
		printf("failed assert: %s\n", msg);
		fflush(stdout);
		exit(1);
	}
}