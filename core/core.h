#ifndef ST_CORE_H
#define ST_CORE_H

// The game version
#define ST_VERSION "v1.1.0"

#if defined(_WIN32)
	#ifndef ST_WINDOWS
		#define ST_WINDOWS
	#endif
// TODO: linux, is, in fact, not unix
#elif defined(__unix__)
	#ifndef ST_LINUX
		#define ST_LINUX
	#endif
#endif

#endif // ST_CORE_H
