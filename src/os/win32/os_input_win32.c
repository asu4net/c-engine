#include "os/win32/os_input_win32.h"

Key _input_key_from_vk_win32(WPARAM wParam)
{
    // *** ASCII KEYS ***
    if (wParam >= '0' && wParam <= '9')
    {
        return (Key) wParam;
    }

    if (wParam >= 'A' && wParam <= 'Z')
    {
        return (Key) wParam;
    }

    // *** NON ASCII ***
    switch (wParam)
    {
    case VK_BACK:       return Key_Backspace;
    case VK_TAB:        return Key_Tab;
    case VK_RETURN:     return Key_Enter;
    case VK_ESCAPE:     return Key_Escape;
    case VK_SPACE:      return Key_Space;
    case VK_DELETE:     return Key_Delete;
    case VK_UP:         return Key_Arrow_Up;
    case VK_DOWN:       return Key_Arrow_Down;
    case VK_LEFT:       return Key_Arrow_Left;
    case VK_RIGHT:      return Key_Arrow_Right;
    case VK_PRIOR:      return Key_Page_Up;
    case VK_NEXT:       return Key_Page_Down;
    case VK_HOME:       return Key_Home;
    case VK_END:        return Key_End;
    case VK_INSERT:     return Key_Insert;
    case VK_PAUSE:      return Key_Pause;
    case VK_SCROLL:     return Key_Scroll_Lock;
    case VK_MENU:       return Key_Alt;
    case VK_CONTROL:    return Key_Ctrl;
    case VK_SHIFT:      return Key_Shift;
    case VK_LWIN:
    case VK_RWIN:       return Key_CMD;
    case VK_SNAPSHOT:   return Key_Print_Screen;

    // @Note: Apparently this doesn't work.
    //case VK_LBUTTON:    return Key_Mouse_Left;
    //case VK_MBUTTON:    return Key_Mouse_Middle;
    //case VK_RBUTTON:    return Key_Mouse_Right;
    }
    
    // *** FUNCTION KEYS ***
    if (wParam >= VK_F1 && wParam <= VK_F24)
    {
        return (Key) (Key_F1 + (wParam - VK_F1));
    }

    return Key_Unknown;
}

void _input_update_cursor_state_win32() 
{
    if (input_cursor_mode == Cursor_Mode_Default)
    return;

    HWND fg = GetForegroundWindow();
    
    RECT rect;
    GetClientRect(fg, &rect);
    
    POINT ul = { rect.left,  rect.top };
    POINT lr = { rect.right, rect.bottom };

    ClientToScreen(fg, & ul);
    ClientToScreen(fg, &lr);

    rect.left = ul.x;
    rect.top = ul.y;
    rect.right = lr.x;
    rect.bottom = lr.y;
    
    ClipCursor(&rect);
    
    if (input_cursor_mode == Cursor_Mode_Hidden)
    {
        // @Note: We center the cursor.
        SetCursorPos
        (
            (rect.left + rect.right) / 2,
            (rect.top + rect.bottom) / 2
        );
    }
}

void input_poll_events_win32()
{
    if (input_events_arena.data == NULL)
    {
        input_events_arena = arena_make(input_events_arena_size);
    }

    arena_reset_keeping_memory(&input_events_arena);

    MSG msg = {};
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void input_set_cursor_mode_win32(Cursor_Mode mode)
{
    if (mode == input_cursor_mode)
    {
        return;
    }

    if (mode == Cursor_Mode_Default)
    {
        ClipCursor(NULL);

        // @Robustness: This won't work on multiple windows in different threads.
        while (ShowCursor(TRUE) < 0) {}
    }
    else
    {
        // @Robustness: This won't work on multiple windows in different threads.
        while (ShowCursor(FALSE) >= 0) {}
    }

    input_cursor_mode = mode;
}

CALLBACK LRESULT input_process_events_win32(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    // @Pending:
    //if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
    //{
        //return true;
    //}

    switch (msg) 
    {
        case WM_INPUT: 
        {
            UINT size = 0u;
            GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &size, sizeof(RAWINPUTHEADER));

            BYTE buffer[64];
            GetRawInputData((HRAWINPUT)lParam, RID_INPUT, buffer, &size, sizeof(RAWINPUTHEADER));
            
            RAWINPUT* raw = (RAWINPUT*)buffer;
            
            if (raw->header.dwType == RIM_TYPEMOUSE) {
                LONG dx = raw->data.mouse.lLastX;
                LONG dy = raw->data.mouse.lLastY;
                
                Input_Event* ev = ArenaPushStruct(&input_events_arena, Input_Event);
                ev->kind = Input_Event_Kind_Mouse_Move;
                
                ev->mouse_delta_x = dx;
                ev->mouse_delta_y = dy;

                ev->mouse_x = (S32)(short)LOWORD(lParam);
                ev->mouse_y = (S32)(short)HIWORD(lParam);
            }
            break;
        }
        case WM_SIZE: 
        {
            Input_Event* ev = ArenaPushStruct(&input_events_arena, Input_Event);
            ev->kind = Input_Event_Kind_Window;
            ev->window_x = LOWORD(lParam);
            ev->window_y = HIWORD(lParam);
            _input_update_cursor_state_win32();
        }
        break;

        case WM_MOVE: 
        {
            _input_update_cursor_state_win32();
        }
        break;

        case WM_KEYDOWN:
        case WM_SYSKEYDOWN: 
        {
            Input_Event* ev = ArenaPushStruct(&input_events_arena, Input_Event);
            ev->kind = Input_Event_Kind_Key;
            ev->key = _input_key_from_vk_win32(wParam);

            ev->key_state = Key_State_Down;

            B32 is_repeat = (lParam & (1 << 30)) != 0;

            if (!is_repeat)
            {
                ev->key_state |= Key_State_Start;
            }

            input_key_down_table[ev->key] = 1;
        }
        break;

        case WM_KEYUP:
        case WM_SYSKEYUP: 
        {
            Input_Event* ev = ArenaPushStruct(&input_events_arena, Input_Event);
            ev->kind = Input_Event_Kind_Key;
            ev->key = _input_key_from_vk_win32(wParam);

            ev->key_state = Key_State_End;

            input_key_down_table[ev->key] = 1;
        }
        break;

        case WM_MOUSEMOVE: 
        {
            _input_update_cursor_state_win32();
        }
        break;
        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP: {
            Input_Event* ev = ArenaPushStruct(&input_events_arena, Input_Event);
            ev->kind = Input_Event_Kind_Key;
            ev->key = Key_Mouse_Left;
            
            B32 down = msg == WM_LBUTTONDOWN;
            ev->key_state = down ? Key_State_Down : Key_State_End;
            input_key_down_table[ev->key] = down;
        }
        break;

        case WM_RBUTTONDOWN:
        case WM_RBUTTONUP: 
        {
            Input_Event* ev = ArenaPushStruct(&input_events_arena, Input_Event);
            ev->kind = Input_Event_Kind_Key;
            ev->key = Key_Mouse_Right;
            
            B32 down = msg == WM_RBUTTONDOWN;
            ev->key_state = down ? Key_State_Down : Key_State_End;
            input_key_down_table[ev->key] = down;
        }
        break;

        case WM_MBUTTONDOWN:
        case WM_MBUTTONUP: 
        {
            Input_Event* ev = ArenaPushStruct(&input_events_arena, Input_Event);
            ev->kind = Input_Event_Kind_Key;
            ev->key = Key_Mouse_Middle;
            
            B32 down = msg == WM_MBUTTONDOWN;
            ev->key_state = down ? Key_State_Down : Key_State_End;
            input_key_down_table[ev->key] = down;
        }
        break;

        case WM_MOUSEWHEEL: 
        {
            Input_Event* ev = ArenaPushStruct(&input_events_arena, Input_Event);
            ev->kind = Input_Event_Kind_Mouse_Wheel;
            ev->wheel_delta = (S32)GET_WHEEL_DELTA_WPARAM(wParam);
        }
        break;

        case WM_CLOSE:
        case WM_QUIT: 
        {
            Input_Event* ev = ArenaPushStruct(&input_events_arena, Input_Event);
            ev->kind = Input_Event_Kind_Quit;
        }
        break;
        case WM_KILLFOCUS:
            memset(input_key_down_table, 0, sizeof(input_key_down_table));
        break;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}