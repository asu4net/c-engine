#ifndef ENGINE_CORE_BASIC_H
#define ENGINE_CORE_BASIC_H

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

#endif // ENGINE_CORE_BASIC_H