#include "core.h"

#ifdef DEBUG
    void _log_function(const char* fmt, ...) {
        va_list args;
        va_start(args, fmt);
        vprintf(fmt, args);
        va_end(args);
        printf("\n");
    }
#endif

void _check_function(B8 expr, const char* fmt, ...) {
    if (expr == 0) {
        va_list args;
        va_start(args, fmt);
        vprintf(fmt, args);
        va_end(args);
        printf("\n");
        DebugBreak();
    }
}

B8 _ensure_function(B8 expr, const char* fmt, ...) {
    if (expr == 0) {
        va_list args;
        va_start(args, fmt);
        vprintf(fmt, args);
        va_end(args);
        printf("\n");
        DebugBreak();
    }
    return expr != 0;
}