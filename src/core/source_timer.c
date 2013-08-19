/*
 * File:    source_timer.c
 * Author:  zxsu <suzp1984@gmail.com>
 * Brief:   brief
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
 * 2013-07-08 10:32 zxsu <suzp1984@gmail.com> created.
 * 2013-08-19 10:54 zxsu <suzp1984@gmail.com> thiz->disable debugs, uninitiated variable
 */

#include <stdlib.h>
#include <sys/time.h>

#include "source_timer.h"

typedef struct _PrivInfo {
    int interval;
    TimerAction action;
    void* user_data;
    int next_time;
} PrivInfo;

static int get_relative_time(void)
{
    struct timeval now = {0};
    gettimeofday(&now, NULL);

    return now.tv_sec*1000 + now.tv_usec/1000;
}

static int source_timer_getfd(Source* thiz)
{
    return -1;
}

static int source_timer_check(Source* thiz)
{
    DECLES_PRIV(priv, thiz);

    int t = priv->next_time - get_relative_time();
    t = t < 0 ? 0 : t;

    return t;
}

static Ret source_timer_dispatch(Source* thiz)
{
    DECLES_PRIV(priv, thiz);
    Ret ret = RET_FAIL;

    if (thiz->disable <= 0)
    {
        ret = priv->action(priv->user_data);
    }

    priv->next_time = get_relative_time() + priv->interval;

    return ret;
}

static void source_timer_destroy(Source* thiz)
{
    SAFE_FREE(thiz);
}

Source* source_timer_create(int interval, TimerAction action, void* user_data)
{
    Source* thiz = (Source*)malloc(sizeof(Source) + sizeof(PrivInfo));
    
    if (thiz != NULL) {
        DECLES_PRIV(priv, thiz);
        thiz->getfd = source_timer_getfd;
        thiz->check = source_timer_check;
        thiz->dispatch = source_timer_dispatch;
        thiz->destroy = source_timer_destroy;

        thiz->ref = 1;
        thiz->source_type = SOURCE_NORMAL;
        thiz->disable = 0;

        priv->interval = interval;
        priv->action = action;
        priv->user_data = user_data;
        priv->next_time = get_relative_time() + interval;
    }

    return thiz;
}

Ret source_timer_reset(Source* thiz)
{
    DECLES_PRIV(priv, thiz);

    thiz->disable = 0;
    priv->next_time = get_relative_time() + priv->interval;

    return RET_OK;
}

Ret source_timer_modify(Source* thiz, int interval)
{
    DECLES_PRIV(priv, thiz);

    priv->interval = interval;
    priv->next_time = get_relative_time() + priv->interval;

    return RET_OK;
}
