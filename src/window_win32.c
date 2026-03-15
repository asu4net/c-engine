#include "window_win32.h"

#define WindowClassNameWin32 L"Window Class"

#define WindowStyleWindowedWin32    WS_OVERLAPPEDWINDOW
#define WindowStyleFullscreenWin32  WS_VISIBLE | WS_POPUP
#define WindowStyleSecondaryWin32   WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME

#define WindowStyleDefaultWin32 WindowStyleWindowedWin32

static HWND main_window_win32 = NULL;  

HWND window_create_win32(S32 width, S32 height, const char* title, Vec4 bg_color)
{
    if (main_window_win32 == NULL)
    {
        SetProcessDPIAware(); // @Note(SetProcessDPIAware)
        timeBeginPeriod(1);   // @Note(timeBeginPeriod)

        // @Note: This is the handle of the calling process.
        // @Robustness: This does not work on dlls.
        HINSTANCE hInstance = GetModuleHandle(0);

        WNDCLASSEXW wc = {};
        //wc.lpfnWndProc = &Win32_Input::process_events;

        // @Note Use this to run the default event processing.
        wc.lpfnWndProc = &DefWindowProc;
        wc.cbSize = sizeof(WNDCLASSEXW);
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);     // Default cursor.
        wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);   // Default icon.
        wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION); // Small icon.
        wc.hInstance = hInstance;
        wc.lpszClassName = WindowClassNameWin32;
        // @Note: CreateSolidBrush changes the background color, I guess.
        wc.hbrBackground = CreateSolidBrush(RGB(bg_color.x * 255, bg_color.y * 255, bg_color.z * 255));

        if (!EnsureMsg(RegisterClassExW(&wc) != 0, "Error! Couldn't register the Win32 window class."))
        {
            return NULL;
        }

        Log("Win32 Window class registered!");
    }

    RECT rect;
    rect.top = 0;
    rect.left = 0;
    rect.right = width;
    rect.bottom = height;

    AdjustWindowRect(&rect, WindowStyleDefaultWin32, 0);

    S32 client_width = rect.right - rect.left;
    S32 client_height = rect.bottom - rect.top;

    // Convert title to wchar_t* -----------
    #define MaxTitleLen 256u
    wchar_t title_buffer[MaxTitleLen + 1];
    {
        U64 title_len = strlen(title);
        if (!EnsureMsg(title_len <= MaxTitleLen, "Error! The title len is %llu chars. Max is %llu.", title_len, MaxTitleLen))
        {
            return NULL;
        }

        S32 len = MultiByteToWideChar
        (
            CP_UTF8,
            0,                 // flags.
            title,             // input.
            -1,                // (-1 = null-terminated).
            title_buffer,      // output buffer.
            MaxTitleLen + 1    // buffer len.
        );

        if (len == 0) 
        {
            DWORD err = GetLastError();
            Log("Error! %lu\n", err);
            StopAtThisLine();
            return NULL;
        }
    }
    // --------------------------------------

    // @Note: Create the window.

    HWND hwnd = CreateWindowExW
    (
        0,                          // Optional window styles.
        WindowClassNameWin32,       // Window class.
        title_buffer,               // Window title
        WindowStyleDefaultWin32,    // Window style.
        CW_USEDEFAULT,              // X Pos.
        CW_USEDEFAULT,              // Y Pos.
        client_width,               // Width.
        client_height,              // Height.
        NULL,                       // Parent window.
        NULL,                       // Menu.
        0,                          // Instance handle. @Note: Apparently only required for Win98.
        NULL                        // Additional application data.
    );

    if (EnsureMsg(hwnd != 0, "Error! Couldn't create the Win32 window."))
    {
        UpdateWindow(hwnd);
        ShowWindow(hwnd, SW_SHOW);
    }

    Log("Win32 Window created!");

    if (main_window_win32 == NULL)
    {
        // @Note: Register the input device.
        RAWINPUTDEVICE rid;
        rid.usUsagePage = 0x01; // Generic Desktop
        rid.usUsage = 0x02;     // Mouse
        rid.dwFlags = RIDEV_INPUTSINK;
        rid.hwndTarget = hwnd;
        RegisterRawInputDevices(&rid, 1, sizeof(rid));
    }
    
    if (hwnd) 
    {
        SetForegroundWindow(hwnd);
    }

    return hwnd;
}

void window_destroy_win32(HWND hwnd)
{
    if (hwnd != NULL)
    {
        if (hwnd == main_window_win32)
        {
            // @Note: Unregister the input device.
            RAWINPUTDEVICE rid;
            rid.usUsagePage = 0x01; // Generic Desktop
            rid.usUsage = 0x02;     // Mouse
            rid.dwFlags = RIDEV_REMOVE;
            rid.hwndTarget = hwnd;
            RegisterRawInputDevices(&rid, 1, sizeof(rid));
        }

        DestroyWindow(hwnd);
        Log("Win32 Window destroyed!");
    }
}

// ===================================================
// @Notes:
// ===================================================

// @Note(SetProcessDPIAware):

// DPI (Dots Per Inch): Indican cuántos píxeles hay en una
// pulgada física de pantalla. Windows en monitores con alto
// DPI puede llegar a escalar automáticamente tu ventana para 
// que los elementos con pocos píxeles se continuen viendo.
// Con esta llamada le comunicas a Windows "I got u, buddy".

// @Note(timeBeginPeriod):

// El Kernel de windows tiene un tick rate con el que actualiza
// como el cambio de hilos (await/sleep) y la actualización de los
// timers. Con esta llamada especificas que lo haga con una frecuencia
// de un milisegundo, en vez de la default. Esto hace que esas 
// actualizaciones sucedan con más frecuencia. A coste de más consumo
// de CPU se gana más estabilidad en las partes de la aplicación que
// dependen de esto.
//
// SRC: https://hero.handmade.network/forums/game-discussion/t/8612-what_does_timebeginperiod_actually_do