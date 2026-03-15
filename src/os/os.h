
#ifndef OS_H
#define OS_H

// ===================================================
// @Region: Dependencies
// ===================================================

#include "base/base.h"

// ===================================================
// @Region: External
// ===================================================

#ifdef _WIN32
#define UNICODE
#define _UNICODE
#include "Windows.h"
#else
#error "Unsupported OS!"
#endif

// ===================================================
// @Region: OS
// ===================================================

#include "os/os_input_state.h"

#ifdef _WIN32
#include "os/win32/os_input_win32.h"
#include "os/win32/os_window_win32.h"
#endif

#include "os/os_window.h"
#include "os/os_input.h"

#endif // OS_H