/*
 * File:    allocator_default.c
 * Author:  zxsu <suzp1984@gmail.com>
 * Brief:   default allocator by posix's api
 *
 * Copyright (c) zxsu
 *
 * Licensed under the Academic Free License version 2.1
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 * History:
 * ================================================================
 * 2013-07-07 11:00 zxsu <suzp1984@gmail.com> created.
 */

#include <stdlib.h>

#include "allocator_default.h"

static void* allocator_default_calloc(Allocator* thiz, size_t nmemb, size_t size)
{
    return calloc(nmemb, size);
}

static void* allocator_default_alloc(Allocator* thiz, size_t size)
{
    return malloc(size);
}

static void allocator_default_free(Allocator* thiz, void* ptr)
{
    return free(ptr);
}

static void* allocator_default_realloc(Allocator* thiz, void* ptr, size_t size)
{
    return realloc(ptr, size);
}

static void allocator_default_destroy(Allocator* thiz)
{
    SAFE_FREE(thiz);
    return;
}

Allocator* allocator_default_create()
{
    Allocator* thiz = (Allocator*)malloc(sizeof(Allocator));

    if (thiz != NULL) {
        thiz->calloc = allocator_default_calloc;
        thiz->alloc = allocator_default_alloc;
        thiz->free = allocator_default_free;
        thiz->realloc = allocator_default_realloc;
        thiz->destroy = allocator_default_destroy;
    }

    return thiz;
}

#ifdef ALLOCATOR_DEFAULT_TEST

#include "allocator_default.h"

int main(int argc, char* argv[])
{
    void* ptr;
    Alloctor* thiz = allocator_default_create();

    ptr = allocator_alloc(thiz, 512);
    allocator_free(thiz, ptr);

    allocator_destroy(thiz);
}

#endif // ALLOCATOR_DEFAULT_TEST
