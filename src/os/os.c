#include "os/os.h"

// ===================================================
// @Region: Dependencies
// ===================================================

#include "base/base.c"

// ===================================================
// @Region: OS
// ===================================================

#ifdef ENGINE_OS_WINDOWS
#include "os/win32/os_input_win32.c"
#include "os/win32/os_window_win32.c"
#endif