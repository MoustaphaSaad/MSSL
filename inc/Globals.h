#pragma once

#if defined(WIN32)||defined(_WIN32)||defined(__WIN32__)||defined(_WIN64)||defined(WIN64)||defined(__MINGW32__)||defined(__MINGW64__)
    #define OS_WINDOWS
#elif defined(__linux__) || defined(__unix__)
    #define OS_LINUX
#endif

#ifdef OS_WINDOWS
#ifdef COMPILE_DLL
    #define MSSL_API __declspec(dllexport)
#else
	#define MSSL_API __declspec(dllimport)
#endif
#endif

#ifdef OS_LINUX
    #define MSSL_API
#endif
