#ifndef ENGINE_OS_INPUT_H
#define ENGINE_OS_INPUT_H

inline static void 
input_poll_events() 
{
    #ifdef ENGINE_OS_WINDOWS
    input_poll_events_win32();
    #endif
}

inline static void 
input_set_cursor_mode(Cursor_Mode mode) 
{
    #ifdef ENGINE_OS_WINDOWS
    input_set_cursor_mode(mode);
    #endif
}

inline static Input_Event_View 
input_events_this_frame() 
{
    return (Input_Event_View) 
    {
        .data  = (Input_Event*) input_events_arena.data,
        .count = input_events_count,
    };
}

inline static B32 
input_key_down(Key key) 
{
    return input_key_down_table[key];
}

#endif // ENGINE_OS_INPUT_H.