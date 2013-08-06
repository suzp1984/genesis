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

#include "main_loop.h"
#include "modules_manager.h"

struct _Reactor {
    Allocator* alloc;
    Config* config;
    ModulesManager* modules_manager;
    MainLoop* main_loop;
};

Reactor* reactor_create(Config* config, Allocator* alloc)
{
    return_val_if_fail(config != NULL, NULL);

    Reactor* thiz = (Reactor*)allocator_alloc(alloc, sizeof(Reactor));
    if (thiz != NULL) {
        thiz->alloc = alloc;
        thiz->config = config;
        thiz->modules_manager = modules_manager_create(alloc);
        thiz->main_loop = NULL;
        // then load the default modules
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

    modules_manager_destroy(thiz->modules_manager);

    return;
}
