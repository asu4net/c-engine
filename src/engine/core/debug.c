#include "engine/core/debug.h"

// ==================================
// @Region: Log and Assert/Check.
// ==================================

#ifdef ENGINE_CONFIG_DEBUG
    void log_(const char* fmt, ...) 
    {
        va_list args;
        va_start(args, fmt);
        vprintf(fmt, args);
        va_end(args);
        printf("\n");
    }
#endif

void check_(B8 expr, const char* fmt, ...) 
{
    if (expr == 0) 
    {
        va_list args;
        va_start(args, fmt);
        vprintf(fmt, args);
        va_end(args);
        printf("\n");
        StopAtThisLine();
    }
}

B8 ensure_(B8 expr, const char* fmt, ...) 
{
    if (expr == 0) 
    {
        va_list args;
        va_start(args, fmt);
        vprintf(fmt, args);
        va_end(args);
        printf("\n");
        StopAtThisLine();
    }
    return expr != 0;
}