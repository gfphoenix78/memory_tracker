#ifdef USE_MEMORY_TRACKER
#include <stddef.h>

extern void memory_track_init(void  *ctx, const char *filename, int lineno);
extern void memory_track_alloc(void *ctx, void *p, size_t size, const char *filename, int lineno);
extern void memory_track_realloc(void *ctx, void *old_ptr, void *new_ptr, size_t size, const char *filename, int lineno);
extern void memory_track_free(void *ctx, void *p, const char *filename, int lineno);
extern void memory_track_reset(void *ctx, const char *filename, int lineno);
extern void memory_track_destroy(void *ctx, const char *filename, int lineno);


#define MEMORY_POOL_TRACK_ALLOC(__alloc_func, ctx, size, ...) ({ \
      void *p = (__alloc_func)((ctx), (size), ## __VA_ARGS__); \
      memory_track_alloc((ctx), p, (size), __FILE__, __LINE__); \
      p; \
    })

#define MEMORY_POOL_TRACK_REALLOC(__realloc_func, ctx, ptr, size) ({ \
      void *new_ptr = (__realloc_func)((ctx), (ptr), (size)); \
      memory_track_realloc((ctx), (ptr), new_ptr, (size), __FILE__, __LINE__); \
      new_ptr; \
    })

#define MEMORY_POOL_TRACK_FREE(__free_func, ctx, ptr) do{ \
      memory_track_free((ctx), (ptr), __FILE__, __LINE__); \
      (__free_func)((ctx), (ptr)); \
    }while(0)

#define MEMORY_POOL_TRACK_FREE0(__free_func, ctx, ptr) do{ \
      memory_track_free((ctx), (ptr), __FILE__, __LINE__); \
      (__free_func)((ctx), (ptr)); \
      (ptr) = (void*)0; \
    }while(0)

#define MEMORY_POOL_TRACK_RESET(__reset_func, ctx) do{ \
      memory_track_reset(ctx, __FILE__, __LINE__); \
      (__reset_func)(ctx); \
    }while(0);

#define MEMORY_POOL_TRACK_DESTROY(__destroy_func, ctx) do{ \
      memory_track_destroy(ctx, __FILE__, __LINE__); \
      (__destroy_func)(ctx); \
    }while(0);


#define MEMORY_TRACK_ALLOC(__alloc_func, size, ...) ({ \
      void *p = (__alloc_func)((size), ## __VA_ARGS__); \
      memory_track_alloc((void*)0, p, (size), __FILE__, __LINE__); \
      p; \
    })

#define MEMORY_TRACK_REALLOC(__realloc_func, ptr, size) ({ \
      void *new_ptr = (__realloc_func)((ptr), (size)); \
      memory_track_realloc((void*)0, (ptr), new_ptr, (size), __FILE__, __LINE__); \
      new_ptr; \
    })

#define MEMORY_TRACK_FREE(__free_func, ptr) do{ \
      memory_track_free((void*)0, (ptr), __FILE__, __LINE__); \
      (__free_func)(ptr); \
    }while(0)

#define MEMORY_TRACK_FREE0(__free_func, ptr) do{ \
      memory_track_free((void*)0, (ptr), __FILE__, __LINE__); \
      (__free_func)(ptr); \
      (ptr) = (void*)0; \
    }while(0)

#else

#define MEMORY_POOL_TRACK_ALLOC(__alloc_func, ctx, size, ...) (__alloc_func)((ctx), (size), ## __VA_ARGS__)
#define MEMORY_POOL_TRACK_REALLOC(__realloc_func, ctx, ptr, size) (__realloc_func)((ctx), (ptr), (size))
#define MEMORY_POOL_TRACK_FREE(__free_func, ctx, ptr) (__free_func)((ctx), (ptr))
#define MEMORY_POOL_TRACK_FREE0(__free_func, ctx, ptr) do{ \
      (__free_func)((ctx), (ptr)); \
      (ptr) = (void*)0; \
    }while(0)
#define MEMORY_POOL_TRACK_RESET(__reset_func, ctx)       (__reset_func)(ctx)
#define MEMORY_POOL_TRACK_DESTROY(__destroy_func, ctx)   (__destroy_func)(ctx)


#define MEMORY_TRACK_ALLOC(__alloc_func, size, ...) (__alloc_func)(size, ## __VA_ARGS__)
#define MEMORY_TRACK_REALLOC(__realloc_func, ptr, size) (__realloc_func)((ptr), (size))
#define MEMORY_TRACK_FREE(__free_func, ptr) (__free_func)(ptr)
#define MEMORY_TRACK_FREE0(__free_func, ptr) do{ \
      (__free_func)(ptr); \
      (ptr) = (void*)0; \
    }while(0)

#endif

