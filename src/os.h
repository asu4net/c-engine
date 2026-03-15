#ifndef OS_H
#define OS_H

// ==================================
// @Region: Platform includes.
// ==================================

#ifdef _WIN32
#include "os_win32.h"
#else
#error "Unsupported OS!"
#endif

// ==================================
// @Region: Window.
// ==================================

#ifdef _WIN32
typedef HWND Window_Handle;
#else
#error "Unsupported OS!"
#endif

static inline Window_Handle  window_create(S32 width, S32 height, const char* title, Vec4 bg_color)
{
#ifdef _WIN32
    return  window_create_win32(width, height, title, bg_color);
#else
#error "Unsupported OS!"
#endif
}

static inline void  window_destroy(Window_Handle handle)
{
#ifdef _WIN32
    return  window_destroy_win32(handle);
#else
#error "Unsupported OS!"
#endif
}

#endif