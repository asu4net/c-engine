#include "core.h"

// ==================================
// @Region: Log and Assert/Check.
// ==================================

#ifdef DEBUG
    void log_(const char* fmt, ...) 
    {
        va_list args;
        va_start(args, fmt);
        vprintf(fmt, args);
        va_end(args);
        printf("\n");
    }
#endif

void check_(B8 expr, const char* fmt, ...) 
{
    if (expr == 0) 
    {
        va_list args;
        va_start(args, fmt);
        vprintf(fmt, args);
        va_end(args);
        printf("\n");
        DebugBreak();
    }
}

B8 ensure_(B8 expr, const char* fmt, ...) 
{
    if (expr == 0) 
    {
        va_list args;
        va_start(args, fmt);
        vprintf(fmt, args);
        va_end(args);
        printf("\n");
        DebugBreak();
    }
    return expr != 0;
}

// ==================================
// @Region: Arena
// ==================================

Arena arena_make(U64 size)
{
    Arena arena;
    arena.size = size == 0 ? arena_default_size : size;
    arena.base = (U8*) calloc(1, arena.size);
    arena.used = 0;
    return arena;
}

void* arena_push(Arena* arena, U64 size, U64 align)
{
    if (arena->base == NULL) 
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
    return arena->base + used;
}

void arena_reset_keeping_memory(Arena* arena)
{
    arena->used = 0;
}

void arena_reset(Arena* arena)
{
    free(arena->base);
    arena->base = NULL;
    arena->used = 0;
    arena->size = 0;
}