/*
 * File:    sources_manager.c
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
 * 2013-07-07 21:48 zxsu <suzp1984@gmail.com> created.
 * 2013-08-17 12:05 zxsu <suzp1984@gmail.com> support signal source.
 * 2013-08-19 10:29 zxsu <suzp1984@gmail.com> sources_manager_get refactor
 */

#include <stdlib.h>
#include <signal.h>

#include "sources_manager.h"
#include "source_primary.h"
#include "source_signal.h"
#include "dlist.h"


struct _SourcesManager {
    int need_refresh;
    Source* primary;
    DList* sources_pool;
    Logger* logger
};

static int signal_notice_fd = -1;
// Sources_manager should be single instance pattern.
// else signal sources did works rightly.
static SourcesManager* base_sources_manager = NULL;

static Ret sources_manager_on_event(void* user_data, Event* event);
static int sources_cmp(void* ctx, void* data);
static void sources_node_destroy(void* ctx, void* data);
static void _signal_handler(int signum);

static void _signal_handler(int signum)
{
    printf("%s: receive signal %d\n", __func__, signum);
    //TODO write something into signal_notice_fd;
    return_if_fail(base_sources_manager != NULL);
    Event event;
    event.type = EVT_SIGNAL;
    event.u.signum = signum;

    source_queue_event(base_sources_manager->primary, &event);
    return;
}

static Ret sources_manager_on_event(void* user_data, Event* event)
{
    return_val_if_fail(user_data != NULL && event != NULL, RET_INVALID_PARAMS);
    SourcesManager* manager = (SourcesManager*)user_data;
    
    switch(event->type) 
    {
    case EVT_ADD_SOURCE:
    {
        logger_debug(manager->logger, "%s: get EVT_ADD_SOURCE event", __func__);
        sources_manager_add_source(manager, (Source*)(event->u.extra));
        break;
    }
    case EVT_REMOVE_SOURCE:
    {
        logger_debug(manager->logger, "%s: get EVT_REMOVE_SOURCE event", __func__);
        sources_manager_del_source(manager, (Source*)(event->u.extra));
        break;
    }
    case EVT_SIGNAL:
    {
        int signum = event->u.signum;
        logger_debug(manager->logger, "%s: get EVT_SIGNAL event with value %d", __func__, signum);
        int count = sources_manager_get_count(manager);
        logger_debug(manager->logger, "%s: sources count = %d", __func__, count);
        Source* signal_source;
        int i = 0;
        for(i = 0; i < count; i++) {
            sources_manager_get(manager, i, &signal_source);
            if (source_get_type(signal_source) == SOURCE_SIGNAL
                && source_get_signal(signal_source) == signum) {
                logger_debug(manager->logger, "%s: active an signal_source", __func__);
                signal_source->active = 1;
            }
        }
        Event event;
        event.type = EVT_NOP;
        source_queue_event(manager->primary, &event);
        break;
    }
    default:
        break;
    }

    return RET_OK;
}

static void sources_node_destroy(void* ctx, void* data)
{
    return_if_fail(data != NULL);

    Source* source = (Source*)data;
    source_unref(source);

    return;
}

SourcesManager* sources_manager_create(Logger* logger)
{
    if (base_sources_manager != NULL) {
        return base_sources_manager;
    }

    SourcesManager* thiz = (SourcesManager*)malloc(sizeof(SourcesManager));

    if (thiz != NULL) {
        thiz->logger = logger;
        //TODO signal_notice_fd should be inited here

        thiz->sources_pool = dlist_create(sources_node_destroy, NULL, NULL, NULL);
        Source* primary_source = source_primary_create(sources_manager_on_event, (void*)thiz);
        thiz->primary = primary_source;
        dlist_append(thiz->sources_pool, (void*)primary_source);

        source_ref(primary_source);
        thiz->need_refresh = 0;
    }
// single instance 
    base_sources_manager = thiz;

    return thiz;
}

Ret sources_manager_add_source(SourcesManager* thiz, Source* source)
{
    return_val_if_fail(thiz != NULL && source != NULL, RET_INVALID_PARAMS);

    SourceType type = source_get_type(source);
    int signum = 0;
    if (type == SOURCE_NORMAL) {
        return dlist_append(thiz->sources_pool, (void*)source);
    } else if(type == SOURCE_SIGNAL) {
        signum = source_get_signal(source);
        signal(signum, _signal_handler);
        return dlist_append(thiz->sources_pool, (void*)source);
    }

    return RET_FAIL;
}

static int sources_cmp(void* ctx, void* data)
{
    return (ctx == data) ? 0 : -1;
}

Ret sources_manager_del_source(SourcesManager* thiz, Source* source)
{
    return_val_if_fail(thiz != NULL && source != NULL, RET_INVALID_PARAMS);

    int index = 0;
    int ret = RET_INVALID_PARAMS;

    index = dlist_find(thiz->sources_pool, sources_cmp, source);
    if (index >= 0) {
        ret = dlist_delete(thiz->sources_pool, index);
        //source_unref(source);
        sources_manager_set_need_refresh(thiz);
    }

    return ret;
}

int sources_manager_get_count(SourcesManager* thiz)
{
    return_val_if_fail(thiz != NULL, 0);

    return dlist_length(thiz->sources_pool);
}

Ret sources_manager_get(SourcesManager* thiz, int i, Source** source)
{
    return_val_if_fail(thiz != NULL && i >= 0 && source != NULL, RET_INVALID_PARAMS);
    logger_debug(thiz->logger, "%s: get num %d source", __func__, i);

    return dlist_get_by_index(thiz->sources_pool, i, (void**)source);
}

int sources_manager_need_refresh(SourcesManager* thiz)
{
    return_val_if_fail(thiz != NULL, 0);
    int ret = 0;

    if (thiz->need_refresh > 0) {
        ret = thiz->need_refresh;
        thiz->need_refresh--;
    }

    return ret;
}

Ret sources_manager_set_need_refresh(SourcesManager* thiz)
{
    return_val_if_fail(thiz != NULL, RET_INVALID_PARAMS);
    thiz->need_refresh++;

    return RET_OK;
}

Source* sources_manager_get_primary_source(SourcesManager* thiz)
{
    return_val_if_fail(thiz != NULL, NULL);

    return thiz->primary;
}

void sources_manager_destroy(SourcesManager* thiz)
{
    int i = 0;
    int count = 0;
    if (thiz != NULL) {
        count = sources_manager_get_count(thiz);
        for (i = 0; i < count; i++) {
            dlist_delete(thiz->sources_pool, 0);
        }

        source_unref(thiz->primary);
        dlist_destroy(thiz->sources_pool);
    }

    SAFE_FREE(thiz);
// single instance pattern destroy
    base_sources_manager = NULL;
    return;
}
