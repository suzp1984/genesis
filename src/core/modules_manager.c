/*
 * File:    modules_manager.c
 * Author:  zxsu <suzp1984@gmail.com>
 * Brief:   ModulesManager code
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
 * 2013-07-31 22:51 zxsu <suzp1984@gmail.com> created.
 */

#include "modules_manager.h"
#include "module.h"
#include "dlist.h"

struct _ModulesManager {
    DList* modules;
    Allocator* alloc;
};

static void _module_node_destroy(void* ctx, void* data)
{
    Module* module = (Module*)data;
    
    module_destroy(module);

    return;
}

ModulesManager* modules_manager_create(Allocator* alloc)
{
    ModulesManager* thiz = (ModulesManager*)allocator_alloc(alloc, sizeof(ModulesManager));

    if (thiz != NULL) {
        thiz->alloc = alloc;
        thiz->modules = dlist_create(_module_node_destroy, NULL, NULL, NULL);
    }

    return thiz;
}

Ret modules_manager_load(ModulesManager* thiz, const char* module, const char* lib_path, void* ctx)
{
    return_val_if_fail(thiz != NULL && module != NULL, RET_INVALID_PARAMS);

    Ret ret = RET_FAIL;
    Module* item = module_create(module, NULL, lib_path, thiz->alloc, ctx);
    if (item != NULL) {
        ret = dlist_append(thiz->modules, (void*)item);
    }

    return ret;
}

Ret modules_manager_unload(ModulesManager* thiz, const char* module)
{
    return_val_if_fail(thiz != NULL && module != NULL, RET_INVALID_PARAMS);
    
    Module* item = NULL;
    char* item_name = NULL;
    int count = modules_manager_get_count(thiz);
    int i = 0;

    for (i = 0; i < count; i++) {
        dlist_get_by_index(thiz->modules, i, (void**)&item);
        module_get_name(item, &item_name);
        if (!strcmp(module, item_name)) {
            break;
        }
        item = NULL;
        item_name = NULL;
    }

    if (item != NULL) {
        dlist_delete(thiz->modules, i);
        //module_destroy(item);
    }

    return RET_OK;
}

int modules_manager_get_count(ModulesManager* thiz)
{
    return_val_if_fail(thiz != NULL && thiz->modules != NULL, 0);

    return dlist_length(thiz->modules);
}

Ret modules_manager_get_by_name(ModulesManager* thiz, const char* name, Module** module)
{
    return_val_if_fail(thiz != NULL && name != NULL, RET_INVALID_PARAMS);

    char* item_name = NULL;
    int count = modules_manager_get_count(thiz);
    int i = 0;
    Ret ret = RET_FAIL;

    for (i = 0; i < count; i++) {
        dlist_get_by_index(thiz->modules, i, (void**)module);
        module_get_name(*module, &item_name);
        if (!strcmp(name, item_name)) {
            ret = RET_OK;
            break;
        }
        module = NULL;
        item_name = NULL;
    }

    return ret;
}

Ret modules_manager_get_by_index(ModulesManager* thiz, size_t index, Module** module)
{
    return_val_if_fail(thiz != NULL && index >= 0, RET_INVALID_PARAMS);

    return dlist_get_by_index(thiz->modules, index, (void**)module);
}

void modules_manager_destroy(ModulesManager* thiz)
{
    return_if_fail(thiz != NULL);

    dlist_destroy(thiz->modules);
    allocator_free(thiz->alloc, thiz);
    return;
}
