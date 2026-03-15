#include "core.h"
#include "alg.h"
#include "os.h"

#include "core.c"
#include "alg.c"
#include "os.c"

S32 main() 
{
    Log("Hello, World!");
    Window_Handle window = window_create(1270, 720, "Buenas tardes", Color_Corn_Flower_Blue);
    for (;;) {}
    return 0;
}