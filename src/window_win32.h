
#ifndef WINDOW_WIN32_H
#define WINDOW_WIN32_H

HWND 
window_create_win32(S32 width, S32 height, const char* title, Vec4 bg_color);

void 
window_destroy_win32(HWND hwnd);

#endif
