/*
 * File:    gs_string.c
 * Author:  zxsu <suzp1984@gmail.com>
 * Brief:   string object
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
 * 2013-07-31 23:29 zxsu <suzp1984@gmail.com> created.
 */

#include "gs_string.h"

#include <string.h>

struct _GsString {
    size_t n;
    void* data;
    Allocator* alloc;
};

GsString* gs_string_create(Allocator* alloc, const void* str, size_t n)
{
    return_val_if_fail(alloc != NULL && n > 0, NULL);

    GsString* thiz = (GsString*)allocator_alloc(alloc, sizeof(GsString));

    if (thiz != NULL) {
        thiz->alloc = alloc;
        thiz->n = n;
        thiz->data = allocator_alloc(alloc, n);
        memcpy(thiz->data, str, n);
    }

    return thiz;
}

GsString* gs_string_dup(GsString* thiz, Allocator* alloc)
{
    return_val_if_fail(thiz != NULL && alloc != NULL, NULL);

    GsString* str = gs_string_create(alloc, thiz->data, thiz->n);

    return str;
}

int gs_string_cmp(GsString* thiz, GsString* target)
{
    return_val_if_fail(thiz != NULL && target != NULL, -1);

    if (thiz->n != target->n) {
        return (thiz->n - target->n);
    }

    return memcmp(thiz->data, target->data, thiz->n);
}

int gs_string_len(GsString* thiz)
{
    return_val_if_fail(thiz != NULL, 0);

    return thiz->n;
}

void gs_string_destroy(GsString* thiz)
{
    return_if_fail(thiz != NULL);

    allocator_free(thiz->alloc, thiz->data);
    allocator_free(thiz->alloc, thiz);

    return;
}
