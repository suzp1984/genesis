/*
 * File:    test_source.cpp
 * Author:  zxsu <suzp1984@gmail.com>
 * Brief:   source test case
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
 * 2013-07-27 17:37 zxsu <suzp1984@gmail.com> created.
 */

#include <gtest/gtest.h>

#include "source_primary.h"

static Ret test_on_event(void* user_data, Event* event)
{
    printf("test_on_event: [%d]\n", event->type);

    return RET_OK;
}

TEST(SourceTest, primarytest) {
    Event event;
    event_init(&event, EVT_ADD_SOURCE);

    Source* primary = source_primary_create(test_on_event, NULL);
    source_queue_event(primary, &event);
    source_dispatch(primary);

    source_destroy(primary);
}

