#ifndef WINDOW_H
#define WINDOW_H

#ifdef _WIN32
typedef HWND Window_Handle;
#else
typedef void* Window_Handle;
#endif

static inline Window_Handle 
window_create(S32 width, S32 height, const char* title, Vec4 bg_color)
{
    #ifdef _WIN32
    return window_create_win32(width, height, title, bg_color);
    #else
    return NULL;
    #endif
}

static inline void 
window_destroy(Window_Handle handle)
{
    #ifdef _WIN32
    return window_destroy_win32(handle);
    #endif
}

#endif