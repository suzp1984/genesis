/*
 * File:    source.h
 * Author:  zxsu <suzp1984@gmail.com>
 * Brief:   event source interface
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
 * 2013-07-06 23:03 zxsu <suzp1984@gmail.com> created.
 * 2013-08-17 12:04 zxsu <suzp1984@gmail.com> add source type. 
 */

#ifndef _SOURCE_H
#define _SOURCE_H

#include "typedef.h"

DECLES_BEGIN

struct _Source;
typedef struct _Source Source;

typedef enum {
    SOURCE_NORMAL = 0,
    SOURCE_SIGNAL
} SourceType;

typedef int (*SourceGetFd)(Source* thiz);
typedef int (*SourceCheck)(Source* thiz);
typedef Ret (*SourceDispatch)(Source* thiz);
typedef void (*SourceDestroy)(Source* thiz);

struct _Source {
    SourceGetFd getfd;
    SourceCheck check;
    SourceDispatch dispatch;
    SourceDestroy destroy;

    int ref;
    int active;
    int disable;
    int source_type;
    char priv[1];
};

static inline int source_get_fd(Source* thiz)
{
    return_val_if_fail(thiz != NULL && thiz->getfd != NULL, -1);

    return thiz->getfd(thiz);
}

static inline int source_check(Source* thiz)
{
    return_val_if_fail(thiz != NULL && thiz->check != NULL, -1);

    return thiz->check(thiz);
}


static inline Ret source_dispatch(Source* thiz)
{
    return_val_if_fail(thiz != NULL && thiz->dispatch != NULL, RET_FAIL);

    return thiz->dispatch(thiz);
}

static inline void source_destroy(Source* thiz)
{
    return_if_fail(thiz != NULL && thiz->destroy != NULL);

    return thiz->destroy(thiz);
}

static inline Ret source_enable(Source* thiz)
{
    return_val_if_fail(thiz != NULL, RET_INVALID_PARAMS);

    if (thiz->disable > 0) {
        thiz->disable--;
    } else {
        thiz->disable = 0;
    }

    return RET_OK;
}

static inline Ret source_disable(Source* thiz)
{
    return_val_if_fail(thiz != NULL, RET_INVALID_PARAMS);

    thiz->disable++;

    return RET_OK;
}

static inline void source_ref(Source* thiz)
{
    return_if_fail(thiz != NULL);

    thiz->ref++;

    return;
}

static inline void source_unref(Source* thiz)
{
    return_if_fail(thiz != NULL);

    thiz->ref--;
    if (thiz->ref <= 0) {
        source_destroy(thiz);
    }

    return;
}

static inline int source_get_type(Source* thiz)
{
    return_if_fail(thiz != NULL);

    return thiz->source_type;
}

DECLES_END

#endif /* _SOURCE_H */
