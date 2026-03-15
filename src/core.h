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
#include <stdlib.h>

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
#define AlignPow2(x,b) (((x) + (b) - 1)&(~((b) - 1))) // @Note: b has to be pow2. 

// ==================================
// @Region: Log and Assert/Check.
// ==================================

#ifdef DEBUG
void log_(const char* fmt, ...);
#endif

#ifdef DEBUG
#define Log(X, ...) (log_(X, ##__VA_ARGS__))
#else
#define Log(X, ...)
#endif

#ifdef DEBUG
#ifdef _WIN32
#define StopAtThisLine() __debugbreak()
#else
#error "Unsupported OS!"
#endif
#else
#define StopAtThisLine()
#endif

#ifdef DEBUG
#define Check(X) check_((X), "Check failed: %s\n", #X)
#define CheckMsg(X, ...) check_((X), __VA_ARGS__)
#define StaticCheck(C, ID) static U8 Glue(ID, __LINE__)[(C)?1:-1]
#define Ensure(X) ensure_((X), "Ensure failed: %s\n", #X)
#define EnsureMsg(X, ...) ensure_((X), __VA_ARGS__)
#else
#define Check(X) ((void)0)
#define CheckMsg(...) ((void)0)
#define Ensure(X) (X)
#define EnsureMsg(X, ...) (X)
#endif

// ==================================
// @Region: Arena
// ==================================

typedef struct Arena Arena;
struct Arena {
    U8* base;
    U64 used;
    U64 size;
};

typedef struct Temp Temp;
struct Temp 
{
    Arena* arena;
    U64 pos;
};

U64 arena_default_size = MB(64);

Arena arena_make(U64 size);
void* arena_push(Arena* arena, U64 size, U64 align);
void arena_reset_keeping_memory(Arena* arena);
void arena_reset(Arena* arena);

Temp temp_init(Arena* arena); 
void temp_done(Temp temp); 

#define ArenaPushStruct(arena, T) arena_push(arena, sizeof(T), AlignOf(T))
#define ArenaPushArray(arena, T, count) arena_push(arena, sizeof(T) * count, AlignOf(T))

#endif