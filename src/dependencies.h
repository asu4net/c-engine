#ifndef DEPENDENCIES_H
#define DEPENDENCIES_H

// ===================================================
// @Region: External Header Files.
// ===================================================

#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef _WIN32
#define UNICODE
#define _UNICODE
#include "Windows.h"
#else
#error "Unsupported OS!"
#endif

// ===================================================
// @Region: Header Files
// ===================================================

#include "core.h"
#include "alg.h"

#include "input_state.h"

#ifdef _WIN32
#include "input_win32.h"
#include "window_win32.h"
#endif

#include "input.h"
#include "window.h"

// ===================================================
// @Region: Translation Units
// ===================================================

#include "core.c"
#include "alg.c"

#ifdef _WIN32
#include "input_win32.c"
#include "window_win32.c"
#endif

#endif