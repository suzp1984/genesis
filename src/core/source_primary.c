/*
 * File:    source_primary.c
 * Author:  zxsu <suzp1984@gmail.com>
 * Brief:   primary source implementation
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
 * 2013-07-22 00:39 zxsu <suzp1984@gmail.com> created.
 */
#include <stdlib.h>

#include "source_primary.h"

#include "pipe_default.h"

typedef struct {
    Pipe* pipe;
    OnEvent on_event;
    void* user_data;
} PrivInfo;

static int source_primary_get_fd(Source* thiz)
{
    DECLES_PRIV(priv, thiz);

    return pipe_get_read_fd(priv->pipe);
}

static int source_primary_check(Source* thiz)
{
    DECLES_PRIV(priv, thiz);

    return -1;
}

static Ret source_primary_dispatch(Source* thiz)
{
    DECLES_PRIV(priv, thiz);

    int ret;
    Event event;

    ret = pipe_read(priv->pipe, &event, sizeof(Event));
    return_val_if_fail(ret == sizeof(Event), RET_FAIL);

    switch(event.type)
    {
    case EVT_NOP:
        break;
    default:
    {
        if (priv->on_event != NULL) {
            priv->on_event(priv->user_data, &event);
        }
    }
    }

    return RET_OK;
}

static void source_primary_destroy(Source* thiz)
{
    if (thiz != NULL) {
        DECLES_PRIV(priv, thiz);
        pipe_destroy(priv->pipe);
        free(thiz);
    }
}

Source* source_primary_create(OnEvent on_event, void* userdata)
{
    Source* thiz = (Source*)malloc(sizeof(Source) + sizeof(PrivInfo));

    if (thiz != NULL) {
        DECLES_PRIV(priv, thiz);
        thiz->getfd = source_primary_get_fd;
        thiz->check = source_primary_check;
        thiz->dispatch = source_primary_dispatch;
        thiz->destroy = source_primary_destroy;

        thiz->ref = 1;
        thiz->source_type = SOURCE_NORMAL;

        priv->pipe = pipe_default_create();
        priv->on_event = on_event;
        priv->user_data = userdata;
    }

    return thiz;
}

Ret source_queue_event(Source* thiz, Event* event)
{
    return_val_if_fail(thiz != NULL && event != NULL, RET_INVALID_PARAMS);
    DECLES_PRIV(priv, thiz);

    int ret = 0;
    ret = pipe_write(priv->pipe, event, sizeof(Event));

    return (ret == sizeof(Event)) ? RET_OK : RET_FAIL;
}
