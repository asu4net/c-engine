
#ifndef BASE_H
#define BASE_H

// ===================================================
// @Region: External
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
// @Region: Base
// ===================================================

#include "base/base_core.h"
#include "base/base_math.h"

#endif // BASE_H