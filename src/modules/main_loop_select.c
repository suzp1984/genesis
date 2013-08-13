/*
 * File:    main_loop_select.c
 * Author:  zxsu <suzp1984@gmail.com>
 * Brief:   main_loop implementation by select api
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
 * 2013-07-08 15:47 zxsu <suzp1984@gmail.com> created.
 */

#include <sys/select.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include "main_loop_select.h"
#include "event.h"
//#include "sources_manager.h"
//#include "source_primay

typedef struct _PrivInfo {
    int running;
    fd_set fdset;
    fd_set err_fdset;
    SourcesManager* sources_manager;
    Logger* logger;
} PrivInfo;

static Ret main_loop_select_run(MainLoop* thiz)
{
    DECLES_PRIV(priv, thiz);

    int i = 0;
    int n = 0;
    int fd = -1;
    int mfd = -1;
    int wait_time = 3600 * 3000;
//    int wait_time = 1000;
    int source_wait_time = 0;
    int ret = 0;
    struct timeval tv = {0};
    Source* source = NULL;

    priv->running = 1;
    while(priv->running) {
        FD_ZERO(&(priv->fdset));
        FD_ZERO(&(priv->err_fdset));

        for (i = 0; i < sources_manager_get_count(priv->sources_manager); i++) {
            source = sources_manager_get(priv->sources_manager, i);
            if ((fd = source_get_fd(source)) >= 0) {
                FD_SET(fd, &(priv->fdset));
                FD_SET(fd, &(priv->err_fdset));
                if (fd > mfd) mfd = fd;
                ++n;
            }

            source_wait_time = source_check(source);
            logger_debug(priv->logger, "%s: source_wait_time = %d", __func__, source_wait_time);
            if (source_wait_time >= 0 && source_wait_time < wait_time) {
                wait_time = source_wait_time;
            }
        }
        
        logger_debug(priv->logger, "%s: wait_time = %d", __func__, wait_time);

        tv.tv_sec = wait_time / 1000;
        tv.tv_usec = (wait_time % 1000)*1000;

        ret = select(mfd + 1, &(priv->fdset), NULL, &(priv->err_fdset), &tv);

        for (i = 0; i < sources_manager_get_count(priv->sources_manager); ) {
            if (sources_manager_need_refresh(priv->sources_manager)) {
                break;
            }
            source = sources_manager_get(priv->sources_manager, i);

            if (source->disable > 0) {
                sources_manager_del_source(priv->sources_manager, source);
                continue;
            }

            if ((fd = source_get_fd(source)) >= 0 && ret != 0) {
                if (ret > 0 && FD_ISSET(fd, &(priv->fdset))) {
                    if (source_dispatch(source) != RET_OK) {
                        sources_manager_del_source(priv->sources_manager, source);
                    } else {
                        ++i;
                    }
                    continue;
                }
            } else if (FD_ISSET(fd, &(priv->fdset))) {
                sources_manager_del_source(priv->sources_manager, source);
                continue;
            }

            if ((source_wait_time = source_check(source)) == 0) {
                if (source_dispatch(source) != RET_OK) {
                    sources_manager_del_source(priv->sources_manager, source);
                } else {
                    ++i;
                }
                continue;
            }

            ++i;
        }
    }

    return RET_OK;
}

static Ret main_loop_select_quit(MainLoop* thiz)
{
    DECLES_PRIV(priv, thiz);

    priv->running = 0;
    return RET_OK;
}

static Ret main_loop_select_add_source(MainLoop* thiz, Source* source)
{
    DECLES_PRIV(priv, thiz);
    Event event;

    event_init(&event, EVT_ADD_SOURCE);
    event.u.extra = source;

    source->active = 1;
    source_enable(source);
    
    logger_debug(priv->logger, "%s: add sources", __func__);
    return source_queue_event(sources_manager_get_primary_source(priv->sources_manager),
                              &event);
}

static Ret main_loop_select_remove_source(MainLoop* thiz, Source* source)
{
    DECLES_PRIV(priv, thiz);
    Event event;

    event_init(&event, EVT_REMOVE_SOURCE);
    event.u.extra = source;

    source_disable(source);

    return source_queue_event(sources_manager_get_primary_source(priv->sources_manager),
                              &event);
}

static void main_loop_select_destroy(MainLoop* thiz)
{
    DECLES_PRIV(priv, thiz);
    
//    modules_manager_destroy(priv->sources_manager);

    SAFE_FREE(thiz);
}

MainLoop* main_loop_select_create(SourcesManager* sources_manager, Logger* logger)
{
    MainLoop* thiz = (MainLoop*)malloc(sizeof(MainLoop) + sizeof(PrivInfo));

    if (thiz != NULL) {
        DECLES_PRIV(priv, thiz);

        priv->logger = logger;
        thiz->run = main_loop_select_run;
        thiz->quit = main_loop_select_quit;
        thiz->add_source = main_loop_select_add_source;
        thiz->remove_source = main_loop_select_remove_source;
        thiz->destroy = main_loop_select_destroy;

        priv->sources_manager = sources_manager;
        FD_ZERO(&(priv->fdset));
        FD_ZERO(&(priv->err_fdset));
        priv->running = 0;
    }

    return thiz;
}
