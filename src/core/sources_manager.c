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
 */

#include <stdlib.h>

#include "sources_manager.h"
#include "source_primary.h"
#include "dlist.h"


struct _SourcesManager {
    int need_refresh;
    Source* primary;
    DList* sources_pool;
    Logger* logger
};

static Ret sources_manager_on_event(void* user_data, Event* event);
static int sources_cmp(void* ctx, void* data);
static void sources_node_destroy(void* ctx, void* data);

static Ret sources_manager_on_event(void* user_data, Event* event)
{
    return_val_if_fail(user_data != NULL && event != NULL, RET_INVALID_PARAMS);
    SourcesManager* manager = (SourcesManager*)user_data;

    switch(event->type) 
    {
    case EVT_ADD_SOURCE:
    {
        sources_manager_add_source(manager, (Source*)(event->u.extra));
        break;
    }
    case EVT_REMOVE_SOURCE:
    {
        sources_manager_del_source(manager, (Source*)(event->u.extra));
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
    SourcesManager* thiz = (SourcesManager*)malloc(sizeof(SourcesManager));

    if (thiz != NULL) {
        thiz->logger = logger;
        thiz->sources_pool = dlist_create(sources_node_destroy, NULL, NULL, NULL);
        Source* primary_source = source_primary_create(sources_manager_on_event, (void*)thiz);
        thiz->primary = primary_source;
        dlist_append(thiz->sources_pool, (void*)primary_source);

        source_ref(primary_source);
        thiz->need_refresh = 0;
    }

    return thiz;
}

Ret sources_manager_add_source(SourcesManager* thiz, Source* source)
{
    return_val_if_fail(thiz != NULL && source != NULL, RET_INVALID_PARAMS);

    return dlist_append(thiz->sources_pool, (void*)source);
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

Source* sources_manager_get(SourcesManager* thiz, int i)
{
    return_val_if_fail(thiz != NULL && i >= 0, NULL);

    Source* source = NULL;
    dlist_get_by_index(thiz->sources_pool, i, (void**)&source);

    return source;
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
    return;
}
