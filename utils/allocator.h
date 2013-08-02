
#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "typedef.h"
#include "stdlib.h"

DECLES_BEGIN

struct  _Allocator;
typedef struct  _Allocator Allocator;

typedef void* (*AllocatorCallocFunc)(Allocator* thiz, size_t nmemb, size_t size);
typedef void* (*AllocatorAllocFunc)(Allocator* thiz, size_t size);
typedef void  (*AllocatorFreeFunc)(Allocator* thiz, void *ptr);
typedef void* (*AllocatorReallocFunc)(Allocator* thiz, void *ptr, size_t size);
typedef void  (*AllocatorDestroyFunc)(Allocator* thiz);

struct _Allocator
{
	AllocatorCallocFunc  calloc;
	AllocatorAllocFunc   alloc;
	AllocatorFreeFunc    free;
	AllocatorReallocFunc realloc;
	AllocatorDestroyFunc destroy;

	char priv[0];
};

static inline void* allocator_calloc(Allocator* thiz, size_t nmemb, size_t size)
{
    return_val_if_fail(nmemb > 0 && size > 0, NULL);

    if (thiz != NULL && thiz->calloc != NULL) {
        return thiz->calloc(thiz, nmemb, size);
    } else {
        return calloc(nmemb, size);
    }
}

static inline void* allocator_alloc(Allocator* thiz, size_t size)
{
    return_val_if_fail(size > 0, NULL);

    if (thiz != NULL && thiz->alloc != NULL) {
        return thiz->alloc(thiz, size);
    } else {
        return malloc(size);
    }
}

static inline void  allocator_free(Allocator* thiz, void *ptr)
{
	return_if_fail(ptr != NULL);

    if (thiz != NULL && thiz->free != NULL) {
        thiz->free(thiz, ptr);
    } else {
        free(ptr);
    }
    
	return;
}

static inline void* allocator_realloc(Allocator* thiz, void *ptr, size_t size)
{
	return_val_if_fail(ptr != NULL && size > 0, NULL);

    if (thiz != NULL && thiz->realloc != NULL) {
        return thiz->realloc(thiz, ptr, size);
    } else {
        return realloc(ptr, size);
    }
}

static inline void  allocator_destroy(Allocator* thiz)
{
	return_if_fail(thiz != NULL && thiz->destroy != NULL);

	return thiz->destroy(thiz);
}

DECLES_END

#endif/*ALLOCATOR_H*/

