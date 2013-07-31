/*
 * File:    reactor.h
 * Author:  zxsu <suzp1984@gmail.com>
 * Brief:   reactor header file
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
 * 2013-07-31 22:10 zxsu <suzp1984@gmail.com> created.
 */

#ifndef _REACTOR_H
#define _REACTOR_H

#include "typedef.h"

DECLES_BEGIN

typedef Ret (*TimerHandler)(void* ctx);

struct _Reactor;
typedef struct _Reactor Reactor;

Reactor* reactor_create(const char* conf_file);

Ret reactor_call_later(Reactor* thiz, int interval, TimerHandler handler, void* ctx);
Ret reactor_run(Reactor* thiz);
Ret reactor_stop(Reactor* thiz);

void reactor_destroy(Reactor* thiz);

DECLES_END

#endif /* _REACTOR_H */
