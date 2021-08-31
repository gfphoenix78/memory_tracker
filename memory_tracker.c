#include "memory_tracker.h"
#ifdef USE_MEMORY_TRACKER

void memory_track_alloc(void *ctx, void *p, size_t size, const char *filename, int lineno)
{
}

void memory_track_realloc(void *ctx, void *old_ptr, void *new_ptr, size_t size, const char *filename, int lineno)
{
}

void memory_track_free(void *ctx, void *p, const char *filename, int lineno)
{
}

void memory_track_reset(void *ctx, const char *filename, int lineno)
{
}

void memory_track_destroy(void *ctx, const char *filename, int lineno)
{
}

#endif
