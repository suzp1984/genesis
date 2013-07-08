/*
 * File:    source_timer.h
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
 * 2013-07-08 10:26 zxsu <suzp1984@gmail.com> created.
 */

#ifndef _SOURCE_TIMER_H
#define _SOURCE_TIMER_H

#include "source.h"

DECLES_BEGIN

typedef Ret (*TimerAction)(void* user_data);

Source* source_timer_create(int interval, TimerAction action, void* user_data);

Ret source_timer_reset(Source* thiz);
Ret source_timer_modify(Source* thiz, int interval);

DECLES_END

#endif /* _SOURCE_TIMER_H */
