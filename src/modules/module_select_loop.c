/*
 * File:    module_select_loop.c
 * Author:  zxsu <suzp1984@gmail.com>
 * Brief:   select mail_loop implementation
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
 * 2013-08-06 23:02 zxsu <suzp1984@gmail.com> created.
 */

#include "module_sym.h"
#include "reactor-internal.h"
#include "main_loop_select.h"

#define SELECT_LOOP_MODULE_NAME "select_loop"
#define SELECT_LOOP_MODULE_AUTHOR "zxsu <suzp1984@gmail.com>"
#define SELECT_LOOP_MODULE_VERSION "0.1"
#define SELECT_LOOP_MODULE_DESCRIPTION "main_loop implementation using select api"
#define SELECT_LOOP_MODULE_USAGE "what the hell?"

static Ret select_loop_module_init(Module* thiz, void* ctx)
{
    Reactor* reactor = (Reactor*)ctx;
    if (reactor->sources_manager == NULL) {
        logger_error(reactor->logger, "%s: sources_manager is NULL", __func__);
        return RET_FAIL;
    }

    MainLoop* select = main_loop_select_create(reactor->sources_manager, reactor->logger);
    //reactor_set_main_loop(reactor, select);
    reactor->main_loop = select;

    return RET_OK;
}

static Ret select_loop_module_start(Module* thiz, void* ctx)
{
    return RET_OK;
}

static Ret select_loop_module_done(Module* thiz, void* ctx)
{
    return RET_OK;
}

const struct ModuleInfo MODULE_SYM_INFO = {
    .module_name = SELECT_LOOP_MODULE_NAME,
    .author = SELECT_LOOP_MODULE_AUTHOR,
    .version = SELECT_LOOP_MODULE_VERSION,
    .description = SELECT_LOOP_MODULE_DESCRIPTION,
    .usage = SELECT_LOOP_MODULE_USAGE,
    .type = MODULE_CORE_TYPE,
    .init = select_loop_module_init,
    .start = select_loop_module_start,
    .done = select_loop_module_done
};
