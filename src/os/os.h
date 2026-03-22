
#ifndef OS_H
#define OS_H

// ===================================================
// @Region: Dependencies
// ===================================================

#include "base/base.h"

// ===================================================
// @Region: Graphics API
// ===================================================

#ifdef ENGINE_OS_WINDOWS
    #ifdef ENGINE_API_GL
        #include "GL/GL.h"
        #include "3rd/khr/glext.h"
        #include "os/os_gl.h"
    #else
        #error "Unsupported API!"
    #endif
#endif

// ===================================================
// @Region: OS
// ===================================================

#include "os/os_input_state.h"

#ifdef ENGINE_OS_WINDOWS
    #include "os/win32/os_input_win32.h"
    #include "os/win32/os_window_win32.h"
#endif

#include "os/os_window.h"
#include "os/os_input.h"

#endif // OS_H