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
};

static Ret sources_manager_on_event(void* user_data, Event* event);

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

SourcesManager* sources_manager_create()
{
    SourcesManager* thiz = (SourcesManager*)malloc(sizeof(SourcesManager));

    if (thiz != NULL) {
        thiz->sources_pool = dlist_create(NULL, NULL, NULL);
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

Ret sources_manager_del_source(SourcesManager* thiz, Source* source);

int sources_manager_get_count(SourcesManager* thiz);
Source* sources_manager_get(SourcesManager* thiz, int i)
{
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
}
