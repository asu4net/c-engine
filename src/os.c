#include "os.h"

// Here the generic code.

#ifdef _WIN32
#include "os_win32.c"
#else
#error "Unsupported OS!"
#endif