#ifndef OS_WIN32_H
#define OS_WIN32_H

// ============================
// @Region: External includes.
// ============================

#ifdef _WIN32
#define UNICODE
#define _UNICODE
#include "Windows.h"
#else
#error "Unsupported OS!"
#endif

// ==================================
// @Region: Window.
// ==================================

HWND window_create_win32(S32 width, S32 height, const char* title, Vec4 bg_color);
void window_destroy_win32(HWND hwnd);

#endif