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
#define AlignPow2(x,b) (((x) + (b) - 1)&(~((b) - 1)))

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
#define Check(X) _check_function((X), "Check failed: %s\n", #X)
#define CheckMsg(X, ...) _check_function((X), __VA_ARGS__)
#define StaticAssert(C, ID) static U8 Glue(ID, __LINE__)[(C)?1:-1]

#define Ensure(X) _ensure_function((X), "Ensure failed: %s\n", #X)
#define EnsureMsg(X, ...) _ensure_function((X), __VA_ARGS__)
#else
#define Check(X) ((void)0)
#define CheckMsg(...) ((void)0)

#define Ensure(X) (X)
#define EnsureMsg(X, ...) (X)
#endif

// ==================================
// @Region: Arena
// ==================================

// Copyright (c) Epic Games Tools
// Licensed under the MIT license (https://opensource.org/license/mit/)

////////////////////////////////
//~ rjf: Arena Types

#define ARENA_HEADER_SIZE 128

typedef U64 ArenaFlags;
enum
{
  ArenaFlag_NoChain    = (1<<0),
  ArenaFlag_LargePages = (1<<1),
};

typedef struct ArenaParams ArenaParams;
struct ArenaParams
{
  ArenaFlags flags;
  U64 reserve_size;
  U64 commit_size;
  void *optional_backing_buffer;
  char *allocation_site_file;
  int allocation_site_line;
};

typedef struct Arena Arena;
struct Arena
{
  Arena *prev;    // previous arena in chain
  Arena *current; // current arena in chain
  ArenaFlags flags;
  U64 cmt_size;
  U64 res_size;
  U64 base_pos;
  U64 pos;
  U64 cmt;
  U64 res;
  char *allocation_site_file;
  int allocation_site_line;
#if ARENA_FREE_LIST
  Arena *free_last;
#endif
};
StaticAssert(sizeof(Arena) <= ARENA_HEADER_SIZE, arena_header_size_check);

typedef struct Temp Temp;
struct Temp
{
  Arena *arena;
  U64 pos;
};

////////////////////////////////
//~ rjf: Arena Functions

U64 arena_default_reserve_size = MB(64);
U64 arena_default_commit_size  = KB(64);
ArenaFlags arena_default_flags = 0;

//- rjf: arena creation/destruction
Arena *arena_alloc_(ArenaParams *params);
#define arena_alloc(...) arena_alloc_(&(ArenaParams){.reserve_size = arena_default_reserve_size, .commit_size = arena_default_commit_size, .flags = arena_default_flags, .allocation_site_file = __FILE__, .allocation_site_line = __LINE__, __VA_ARGS__})
void arena_release(Arena *arena);

//- rjf: arena push/pop/pos core functions
void *arena_push(Arena *arena, U64 size, U64 align, B32 zero);
U64   arena_pos(Arena *arena);
void  arena_pop_to(Arena *arena, U64 pos);

//- rjf: arena push/pop helpers
void arena_clear(Arena *arena);
void arena_pop(Arena *arena, U64 amt);

//- rjf: temporary arena scopes
Temp temp_begin(Arena *arena);
void temp_end(Temp temp);

//- rjf: push helper macros
#define push_array_no_zero_aligned(a, T, c, align) (T *)arena_push((a), sizeof(T)*(c), (align), (0))
#define push_array_aligned(a, T, c, align) (T *)arena_push((a), sizeof(T)*(c), (align), (1))
#define push_array_no_zero(a, T, c) push_array_no_zero_aligned(a, T, c, Max(8, AlignOf(T)))
#define push_array(a, T, c) push_array_aligned(a, T, c, Max(8, AlignOf(T)))

#endif 