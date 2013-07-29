/*
 * File:    event.h
 * Author:  zxsu <suzp1984@gmail.com>
 * Brief:   event
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
 * 2013-07-08 10:10 zxsu <suzp1984@gmail.com> created.
 */

#ifndef _EVENT_H
#define _EVENT_H

#include "typedef.h"
#include <string.h>

DECLES_BEGIN

typedef enum _EventType
{
    EVT_NOP = 0,
    EVT_ADD_SOURCE,
    EVT_REMOVE_SOURCE,
} EventType;

typedef struct _Event
{
    EventType type;
//    size_t time;
    union
    {
        void* extra;
    }u;

} Event;

typedef Ret (*OnEvent)(void* user_data, Event* event);

static inline Ret event_init(Event* event, EventType type)
{
    if (event != NULL) {
        memset(event, 0x00, sizeof(Event));
        event->type = type;
    }

    return RET_OK;
}

DECLES_END

#endif /* _EVENT_H */
