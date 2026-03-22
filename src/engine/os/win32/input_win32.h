#ifndef ENGINE_OS_INPUT_WIN32_H
#define ENGINE_OS_INPUT_WIN32_H

void 
input_poll_events_win32();

void 
input_set_cursor_mode_win32(Cursor_Mode mode); 

CALLBACK LRESULT 
input_process_events_win32(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

#endif // ENGINE_OS_INPUT_WIN32_H.