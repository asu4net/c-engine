#include "engine/core/arena.h"

// ==================================
// @Region: Arena
// ==================================

Arena arena_make(U64 size)
{
    Arena arena;
    arena.size = size == 0 ? arena_default_size : size;
    arena.data = (U8*) calloc(1, arena.size);
    arena.used = 0;
    return arena;
}

void* arena_push(Arena* arena, U64 size, U64 align)
{
    if (arena->data == NULL) 
    {
        *arena = arena_make(0);
    }

    if (align == 0)
    {
        align = 8;
    }

    U64 used = arena->used;
    used = AlignPow2(used, align);

    if (used + size > arena->size)
    {
        CheckMsg(0, "Error: Requested %llu, bytes on arena, but only %llu left.", size, arena->size - arena->used);
        return NULL;
    }

    arena->used = used + size;
    return arena->data + used;
}

void arena_reset_keeping_memory(Arena* arena)
{
    arena->used = 0;
}

void arena_reset(Arena* arena)
{
    free(arena->data);
    arena->data = NULL;
    arena->used = 0;
    arena->size = 0;
}

Temp temp_init(Arena* arena)
{
    Temp temp;
    temp.arena = arena;
    temp.pos = arena->used;
    return temp;
}

void temp_done(Temp temp)
{
    temp.arena->used = temp.pos;
} 