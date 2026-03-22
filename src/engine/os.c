#include "engine/os.h"

// ===================================================
// @Region: Dependencies
// ===================================================

#include "engine/core.c"

// ===================================================
// @Region: OS
// ===================================================

#ifdef ENGINE_OS_WINDOWS
#include "engine/os/win32/input_win32.c"
#include "engine/os/win32/window_win32.c"
#endif