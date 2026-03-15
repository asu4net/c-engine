#include "os/os.h"

// ===================================================
// @Region: Dependencies
// ===================================================

#include "base/base.c"

// ===================================================
// @Region: OS
// ===================================================

#ifdef _WIN32
#include "os/win32/os_input_win32.c"
#include "os/win32/os_window_win32.c"
#endif