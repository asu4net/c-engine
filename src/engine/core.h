#ifndef ENGINE_CORE_H
#define ENGINE_CORE_H

// ===================================================
// @Region: Platform detection
// ===================================================

#ifdef _WIN32
	// Windows x64/x86.
	#ifdef _WIN64
		// Windows x64.
		#define ENGINE_OS_WINDOWS
        // Win32 API and Unicode proc versions.
        #define UNICODE
        #define _UNICODE
        #include "Windows.h"
	#else
		// Windows x86.
		#error "x86 Builds are not supported!"
	#endif
#else
    #error "Unsupported OS!"
#endif

// ===================================================
// @Region: External
// ===================================================

#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

// ===================================================
// @Region: Core
// ===================================================

#include "engine/core/basic.h"
#include "engine/core/debug.h"
#include "engine/core/math.h"
#include "engine/core/arena.h"

#endif // ENGINE_CORE_H.