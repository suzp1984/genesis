/*
 * File:    reactor-internal.h
 * Author:  zxsu <suzp1984@gmail.com>
 * Brief:   internal implementation of reactor
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
 * 2013-08-13 10:22 zxsu <suzp1984@gmail.com> created.
 */

#ifndef _REACTOR_INTERNAL_H
#define _REACTOR_INTERNAL_H

#include "typedef.h"
#include "reactor.h"
#include "main_loop.h"
#include "modules_manager.h"
#include "sources_manager.h"
#include "logger.h"

DECLES_BEGIN

struct _Reactor {
    Logger* logger;
    Allocator* alloc;
    Config* config;
    SourcesManager* sources_manager;
    ModulesManager* modules_manager;
    MainLoop* main_loop;
};

Ret reactor_get_main_loop(Reactor* thiz, MainLoop** main_loop);
Ret reactor_set_main_loop(Reactor* thiz, MainLoop* main_loop);

Ret reactor_get_modules_manager(Reactor* thiz, ModulesManager** modules_manager);
Ret reactor_set_modules_manager(Reactor* thiz, ModulesManager* modules_manager);

DECLES_END

#endif /* _REACTOR_NTERNAL_H */

