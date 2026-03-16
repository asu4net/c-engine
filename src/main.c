#include "common.h"

S32 main() 
{
    Log("Hellope!");
    Window_Handle window = window_create(1270, 720, "Buenas tardes", Color_Corn_Flower_Blue);

    B32 quit = 0;
    while (!quit) 
    {
        input_poll_events();
        
        Input_Event_View events = input_events_this_frame();
        for EachIndex(i, events.count)
        {
            Input_Event* event = &events.data[i];

            if (event->kind == Input_Event_Kind_Quit)
            {
                quit = 1;
            }
            #ifdef DEBUG
            if (event->key == Key_Escape)
            {
                quit = 1;
            }
            #endif
        }
    }
    return 0;
}