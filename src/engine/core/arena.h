#ifndef ENGINE_CORE_ARENA_H
#define ENGINE_CORE_ARENA_H

// ==================================
// @Region: Arena
// ==================================

typedef struct Arena 
{
    U8* data;
    U64 used;
    U64 size;
} 
Arena;

typedef struct Temp 
{
    Arena* arena;
    U64 pos;
} 
Temp;

U64 arena_default_size = KB(64);

Arena 
arena_make(U64 size);

void* 
arena_push(Arena* arena, U64 size, U64 align);

void 
arena_reset_keeping_memory(Arena* arena);

void 
arena_reset(Arena* arena);

Temp 
temp_init(Arena* arena); 

void 
temp_done(Temp temp); 

#define ArenaPushStruct(arena, T) (T*) arena_push(arena, sizeof(T), AlignOf(T))
#define ArenaPushArray(arena, T, count) (T*) arena_push(arena, sizeof(T) * count, AlignOf(T))

#endif // ENGINE_CORE_ARENA_H.