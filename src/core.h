#ifndef CORE_H
#define CORE_H

// ============================
// @Region: External includes.
// ============================

#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <string.h>
#include <stdint.h>

// ============================
// @Region: Base Types.
// ============================

typedef uint8_t  U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;
typedef int8_t   S8;
typedef int16_t  S16;
typedef int32_t  S32;
typedef int64_t  S64;
typedef S8       B8;
typedef S16      B16;
typedef S32      B32;
typedef S64      B64;
typedef float    F32;
typedef double   F64;

// ==================================
// @Region: Units.
// ==================================

#define KB(n)  (((U64)(n)) << 10)
#define MB(n)  (((U64)(n)) << 20)
#define GB(n)  (((U64)(n)) << 30)
#define TB(n)  (((U64)(n)) << 40)
#define Thousand(n)   ((n)*1000)
#define Million(n)    ((n)*1000000)
#define Billion(n)    ((n)*1000000000)

// ==================================
// @Region: Clamps, Min, Max.
// ==================================

#define Min(A,B) (((A)<(B))?(A):(B))
#define Max(A,B) (((A)>(B))?(A):(B))
#define ClampTop(A,X) Min(A,X)
#define ClampBot(X,B) Max(X,B)
#define Clamp(A,X,B) (((X)<(A))?(A):((X)>(B))?(B):(X))

#endif

// ==================================
// @Region: AlignOf.
// ==================================

// @PlatformIssue: This will work just in clang and msvc.
#define AlignOf(T) __alignof(T)

// ==================================
// @Region: Helpers.
// ==================================

#define Stringify_(S) #S
#define Stringify(S) Stringify_(S)

#define Glue_(A,B) A##B
#define Glue(A,B) Glue_(A,B)

#define EachIndex(it, count) (U64 it = 0; it < (count); it += 1)
#define DeferBlock(begin, end) for(int _i_ = ((begin), 0); !_i_; _i_ += 1, (end))

// ==================================
// @Region: Log and Assert/Check.
// ==================================

#ifdef DEBUG
    void _log_function(const char* fmt, ...);
#endif

#ifdef DEBUG
#   define Log(X, ...) (_log_function(X, ##__VA_ARGS__))
#else
#   define Log(X, ...)
#endif

// @Note: Debug break macro implementation.

#ifdef DEBUG
#   ifdef _WIN32
#       define DebugBreak() __debugbreak()
#   else
#       error "Unsupported OS!"
#   endif
#else
#   define DebugBreak()
#endif

// @Note: Assert macro implementation.

#ifdef DEBUG
void _check_function(B8 expr, const char* fmt, ...);
B8   _ensure_function(B8 expr, const char* fmt, ...);
#endif

#ifdef DEBUG
#   define Check(X, ...) (_check_function(X, __VA_ARGS__))
#   define Ensure(X, ...) (_ensure_function(X, __VA_ARGS__))
#else
#   define Check(...)
#   define Ensure(X, ...) (X)
#endif