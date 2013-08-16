/*
 * File:    source_signal.c
 * Author:  zxsu <suzp1984@gmail.com>
 * Brief:   signal source implementation
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
 * 2013-08-16 22:32 zxsu <suzp1984@gmail.com> created.
 */

#include "source_signal.h"

#include <stdlib.h>

typedef struct {
    int signum;
    SignalHandler handler;
    void* ctx;
} PrivInfo;

static int source_signal_get_fd(Source* thiz)
{
    return -1;
}

static int source_signal_check(Source* thiz)
{
    return -1;
}

static Ret source_signal_dispatch(Source* thiz)
{
    DECLES_PRIV(priv, thiz);
    
    if (priv->handler != NULL) {
        priv->handler(priv->signum, priv->ctx);
    }

    return RET_OK;
}

// TODO:XXX distroy a signal source stands for do not dispatch the handler again
static void source_signal_destroy(Source* thiz)
{
    SAFE_FREE(thiz);
}

Source* source_signal_create(int signum, SignalHandler handler, void* ctx)
{
    Source* thiz = (Source*)malloc(sizeof(Source) + sizeof(PrivInfo));

    if (thiz != NULL) {
        DECLES_PRIV(priv, thiz);

        thiz->getfd = source_signal_get_fd;
        thiz->check = source_signal_check;
        thiz->dispatch = source_signal_dispatch;
        thiz->destroy = source_signal_destroy;

        thiz->ref = 1;
        thiz->active = 0;
        thiz->source_type = SOURCE_SIGNAL;

        priv->signum = signum;
        priv->handler = handler;
        priv->ctx = ctx;
    }

    return thiz;
}

int source_get_signal(Source* thiz)
{
    return_val_if_fail(thiz != NULL, -1);
    DECLES_PRIV(priv, thiz);

    return priv->signum;
}
