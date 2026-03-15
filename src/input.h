#ifndef INPUT_H
#define INPUT_H

inline static void 
input_poll_events() 
{
    #ifdef _WIN32
    input_poll_events_win32();
    #endif
}

inline static void 
input_set_cursor_mode(Cursor_Mode mode) 
{
    #ifdef _WIN32
    input_set_cursor_mode(mode);
    #endif
}


inline static Input_Event_View 
input_events_this_frame() 
{
    return (Input_Event_View){};
}

inline static B32 
input_key_down(Key key) 
{
    return 0;
}

#endif