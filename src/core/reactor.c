/*
 * File:    reactor.c
 * Author:  zxsu <suzp1984@gmail.com>
 * Brief:   Reactor implementation
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
 * 2013-07-31 22:15 zxsu <suzp1984@gmail.com> created.
 */

#include "reactor.h"
#include "reactor-internal.h"

/* 
struct _Reactor {
    Allocator* alloc;
    Config* config;
    ModulesManager* modules_manager;
    MainLoop* main_loop;
    }; 
*/

Reactor* reactor_create(Config* config, Allocator* alloc)
{
    return_val_if_fail(config != NULL, NULL);

    char* lib_path = NULL;
    char* module_name = NULL;
    size_t count = 0;
    size_t i = 0;

    Reactor* thiz = (Reactor*)allocator_alloc(alloc, sizeof(Reactor));
    if (thiz != NULL) {
        Module* module = NULL;
        thiz->alloc = alloc;
        thiz->config = config;
        thiz->modules_manager = modules_manager_create(alloc);
        thiz->main_loop = NULL;
        // then load the default modules
        config_get_module_lib_path(config, &lib_path);
        count = config_get_modules_count(config);
        for (i = 0; i < count; i++) {
            config_get_module_name_by_id(config, i, &module_name);
            modules_manager_load(thiz->modules_manager, module_name, lib_path, thiz);
        }
        
        // init all modules.
        count = modules_manager_get_count(thiz->modules_manager);
        for (i = 0; i < count; i++) {
            modules_manager_get_by_index(thiz->modules_manager, i, &module);
            module_init(module, thiz);
        }
    }

    return thiz;
}

Ret reactor_run(Reactor* thiz)
{
    return main_loop_run(thiz->main_loop);
}

Ret reactor_stop(Reactor* thiz)
{
    return main_loop_quit(thiz->main_loop);
}

void reactor_destroy(Reactor* thiz)
{
    return_if_fail(thiz != NULL);

    sources_manager_destroy(thiz->sources_manager);
    modules_manager_destroy(thiz->modules_manager);
    allocator_free(thiz->alloc, thiz);

    return;
}

Ret reactor_get_main_loop(Reactor* thiz, MainLoop** main_loop)
{
    return_val_if_fail(thiz != NULL && main_loop != NULL, RET_INVALID_PARAMS);

    main_loop = &(thiz->main_loop);

    return RET_OK;
}

Ret reactor_set_main_loop(Reactor* thiz, MainLoop* main_loop)
{
    return_val_if_fail(thiz != NULL && main_loop != NULL, RET_INVALID_PARAMS);
    
    if (thiz->main_loop != NULL) {
        return RET_FAIL;
    }

    thiz->main_loop = main_loop;
    return RET_OK;
}

Ret reactor_get_modules_manager(Reactor* thiz, ModulesManager** modules_manager)
{
    return RET_OK;
}

Ret reactor_set_modules_manager(Reactor* thiz, ModulesManager* modules_manager)
{
    return RET_OK;
}
