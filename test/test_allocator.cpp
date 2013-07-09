/*
 * File:    test_allocator.cpp
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
 * 2013-07-09 11:21 zxsu <suzp1984@gmail.com> created.
 */

#include <gtest/gtest.h>

#include "allocator_nginx.h"

namespace {

    class AllocatorNgnixTest : public ::testing::Test {
    protected:
        AllocatorNgnixTest() {
            p1 = NULL;
        }

        virtual ~AllocatorNgnixTest() {
        }

        virtual void SetUp() {
            allocator_nginx_512 = allocator_nginx_create(512);
        }

        virtual void TearDown() {
            allocator_destroy(allocator_nginx_512);
        }

        Allocator* allocator_nginx_512;
        void* p1;
    }; // AllocatorNgnixTest

    TEST_F(AllocatorNgnixTest, alloc) {
        p1 = allocator_alloc(allocator_nginx_512, 416);
        EXPECT_NE(p1, NULL);
    }

    TEST_F(AllocatorNgnixTest, free) {
        allocator_free(allocator_nginx_512, p1);
    }

} // namespace 
