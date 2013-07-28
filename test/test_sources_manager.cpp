/*
 * File:    test_sources_manager.cpp
 * Author:  zxsu <suzp1984@gmail.com>
 * Brief:   test case for sources manager
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
 * 2013-07-28 09:56 zxsu <suzp1984@gmail.com> created.
 */

#include <gtest/gtest.h>
#include <stdio.h>

#include "sources_manager.h"
#include "source_timer.h"

static Ret source_timer_action(void* user_data);

static Ret source_timer_action(void* user_data)
{
    printf("%s\n", __func__);

    return RET_OK;
}

TEST(SourcesManagerTest, testcase1) {
    SourcesManager* sources_manager = sources_manager_create();
    Source* timer = source_timer_create(10, source_timer_action, NULL);
    
    ASSERT_EQ(1, sources_manager_get_count(sources_manager));
    ASSERT_EQ(RET_OK, sources_manager_add_source(sources_manager, timer));
    ASSERT_EQ(2, sources_manager_get_count(sources_manager));
    ASSERT_EQ(RET_OK, sources_manager_del_source(sources_manager, timer));
    ASSERT_EQ(1, sources_manager_get_count(sources_manager));
    
    sources_manager_destroy(sources_manager);
}
