
#ifndef ENGINE_OS_H
#define ENGINE_OS_H

// ===================================================
// @Region: Dependencies
// ===================================================

#include "engine/core.h"

// ===================================================
// @Region: Graphics API
// ===================================================

#ifdef ENGINE_OS_WINDOWS
    #ifdef ENGINE_API_GL
        #include "GL/GL.h"
        #include "3rd/khr/glext.h"
        #include "engine/os/gl/functions_gl.h"
    #else
        #error "Unsupported API!"
    #endif
#endif

// ===================================================
// @Region: OS
// ===================================================

#include "engine/os/input_state.h"

#ifdef ENGINE_OS_WINDOWS
    #include "os/win32/input_win32.h"
    #include "os/win32/window_win32.h"
#endif

#include "engine/os/window.h"
#include "engine/os/input.h"

#endif // OS_H