#ifndef OS_INPUT_STATE_H
#define OS_INPUT_STATE_H

typedef enum Cursor_Mode Cursor_Mode;
enum Cursor_Mode
{
      Cursor_Mode_Default
    , Cursor_Mode_Confined
    , Cursor_Mode_Hidden
};

// @Note: Common use case.
// 
// Key_State_Pressed  -> Key_State_Start | Key_State_Down
// Key_State_Repeat   -> Key_State_Down
// Key_State_Released -> Key_State_End

typedef enum Key_State Key_State;
enum Key_State
{
      Key_State_None  = 1 << 0
    , Key_State_Down  = 1 << 1
    , Key_State_Start = 1 << 2 
    , Key_State_End   = 1 << 3
};

typedef enum Key Key;
enum Key
{
      Key_Unknown = 0
    
    // *** ASCII (REAL CODES) ***

    , Key_Backspace    = 8
    , Key_Tab          = 9
    , Key_Linefeed     = 10
    , Key_Enter        = 13
    , Key_Escape       = 27
    , Key_Space        = 32

    // @Note: Here live ASCII letters, digits and symbols via direct char input.
    // They are not enumerated because they are received as char or UTF-32 text.

    // *** END OF ASCII ***
    // Begin custom keycodes (physical keys)

    , _Key_BEGIN_NON_ASCII = 512 // @Note: Explicit boundary to avoid collisions.

    , Key_Delete       
    , Key_Arrow_Up     
    , Key_Arrow_Down   
    , Key_Arrow_Left   
    , Key_Arrow_Right  
    , Key_Page_Up      
    , Key_Page_Down    
    , Key_Home         
    , Key_End          
    , Key_Insert       
    , Key_Pause        
    , Key_Scroll_Lock  
    , Key_Alt          
    , Key_Ctrl         
    , Key_Shift        
    , Key_CMD          

    // *** FUNCTION KEYS ***
    , Key_F1  , Key_F2  , Key_F3  , Key_F4  , Key_F5  , Key_F6  , Key_F7  , Key_F8  , Key_F9 , Key_F10
    , Key_F11 , Key_F12 , Key_F13 , Key_F14 , Key_F15 , Key_F16 , Key_F17 , Key_F18 , Key_F19
    , Key_F20 , Key_F21 , Key_F22 , Key_F23 , Key_F24

    , Key_Print_Screen

    // *** MOUSE AS BUTTON INPUT KEYS ***
    , Key_Mouse_Left
    , Key_Mouse_Middle
    , Key_Mouse_Right

    // *** End ***
    , Key_Count
};

typedef enum Input_Event_Kind Input_Event_Kind;
enum Input_Event_Kind 
{
      Input_Event_Kind_None
    , Input_Event_Kind_Key
    , Input_Event_Kind_Window
    , Input_Event_Kind_Mouse_Move
    , Input_Event_Kind_Mouse_Wheel
    , Input_Event_Kind_Quit
};

typedef struct Input_Event Input_Event;
struct Input_Event
{
    Input_Event_Kind kind;

    Key key;
    U32 key_state;
    S32 wheel_delta;

    S32 window_x;
    S32 window_y;

    S32 mouse_x;
    S32 mouse_y;

    S32 mouse_delta_x;
    S32 mouse_delta_y;
};

typedef struct Input_Event_View Input_Event_View;
struct Input_Event_View
{
    Input_Event* data;
    S32 count;
};

U64         input_events_arena_size         = MB(64);
Arena       input_events_arena              = {0};
U32         input_events_count              = 0;
Key_State   input_key_states[Key_Count]     = {0};
B32         input_key_down_table[Key_Count] = {0};
Cursor_Mode input_cursor_mode               = Cursor_Mode_Default;

#endif // OS_INPUT_STATE_H