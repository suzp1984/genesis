/*
 * File:    test_modules_manager.cpp
 * Author:  zxsu <suzp1984@gmail.com>
 * Brief:   modules_manager test case
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
 * 2013-08-06 10:14 zxsu <suzp1984@gmail.com> created.
 */

#include <gtest/gtest.h>

#include "modules_manager.h"
#include "allocator_nginx.h"

TEST(ModulesManagerTest, simple_test) {
    Allocator* alloc = allocator_nginx_create(128);
    ModulesManager* manager = modules_manager_create(alloc, NULL);
    
    ASSERT_EQ(0, modules_manager_get_count(manager));

    modules_manager_destroy(manager);
    allocator_destroy(alloc);
}
