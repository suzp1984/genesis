/*
 * File:    source_primary.h
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
 * 2013-07-08 16:05 zxsu <suzp1984@gmail.com> created.
 */

#ifndef _SOURCE_PRIMARY_H
#define _SOURCE_PRIMARY_H

#include "source.h"
#include "event.h"

DECLES_BEGIN

Source* source_primary_create(OnEvent on_event, void* userdata);

Ret source_queue_event(Source* thiz, Event* event);

DECLES_END

#endif /* _SOURCE_PRIMARY_H */
