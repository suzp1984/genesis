/*
 * File:    test_dlist.cpp
 * Author:  zxsu <suzp1984@gmail.com>
 * Brief:   unit test case for dlist
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
 * 2013-07-26 22:13 zxsu <suzp1984@gmail.com> created.
 */

#include <gtest/gtest.h>

#include "dlist.h"

namespace {

    class DlistTest : public ::testing::Test {
    protected:
        DlistTest() {
        }

        virtual ~DlistTest() {
        }

        virtual void SetUp() {
            dlist = dlist_create(NULL, NULL, NULL, NULL);
        }

        virtual void TearDown() {
            dlist_destroy(dlist);
        }

        DList* dlist;

    }; // DlistTest

    static int cmp_int(void* ctx, void* data)
    {
        return (int)data - (int)ctx;
    }

    TEST_F(DlistTest, inttest) {
        int i = 0;
        int n = 100;
        int data = 0;

        for (i = 0; i < n; i++) {
            ASSERT_EQ(RET_OK, dlist_append(dlist, (void*)i));
            ASSERT_EQ(1, (dlist_length(dlist) - i));
            ASSERT_EQ(RET_OK, dlist_get_by_index(dlist, i, (void**)&data));
            ASSERT_EQ(0, (data - i));
            ASSERT_EQ(RET_OK, dlist_set_by_index(dlist, i, (void*)(2*i)));
            ASSERT_EQ(RET_OK, dlist_get_by_index(dlist, i, (void**)&data));
            ASSERT_EQ(0, (data - (2*i)));
            ASSERT_EQ(RET_OK, dlist_set_by_index(dlist, i, (void*)i));
            ASSERT_EQ(0, (dlist_find(dlist, cmp_int, (void*)i) - i));
        }

        for (i = 0; i < n; i++) {
            ASSERT_EQ(RET_OK, dlist_get_by_index(dlist, i, (void**)&data));
            ASSERT_EQ(0, (i - data));
        }
    }

} // namespace
