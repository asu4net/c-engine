#include "common.h"

S32 main() 
{
    Log("Hello, World!");
    Window_Handle window = window_create(1270, 720, "Buenas tardes", Color_Corn_Flower_Blue);
    B32 quit = 0;
    while (!quit) 
    {
        input_poll_events();
    }
    return 0;
}