/*
 * File:    test_darray.cpp
 * Author:  zxsu <suzp1984@gmail.com>
 * Brief:   darray test case 
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
 * 2013-07-27 11:00 zxsu <suzp1984@gmail.com> created.
 */

#include <gtest/gtest.h>

#include "darray.h"

static int cmp_int(void* ctx, void* data)
{
    return (int)data - (int)ctx;
}

TEST(DarrayTest, inttest) {
    int i = 0;
    int n = 100;
    int data = 0;

    DArray* darray = darray_create(NULL, NULL);

    for (i = 0; i < n; i++) {
        ASSERT_EQ(RET_OK, darray_append(darray, (void*)i));
        ASSERT_EQ(1, (darray_length(darray) - i));
        ASSERT_EQ(RET_OK, darray_get_by_index(darray, i, (void**)&data));
        ASSERT_EQ(0, (data - i));
        ASSERT_EQ(RET_OK, darray_set_by_index(darray, i, (void*)(2*i)));
        ASSERT_EQ(RET_OK, darray_get_by_index(darray, i, (void**)&data));
        ASSERT_EQ(0, (data - 2*i));
        ASSERT_EQ(RET_OK, darray_set_by_index(darray, i, (void*)i));
        ASSERT_EQ(0, (darray_find(darray, cmp_int, (void*)i) - i));
    }

    for (i = 0; i < n; i++) {
        ASSERT_EQ(RET_OK, darray_get_by_index(darray, 0, (void**)&data));
        ASSERT_EQ(0, (data - i));
        ASSERT_EQ(0, (darray_length(darray) - n + i));
        ASSERT_EQ(RET_OK, darray_delete(darray, 0));
        ASSERT_EQ(0, (darray_length(darray) - n + i + 1));
    }

    ASSERT_EQ(0, darray_length(darray));

    darray_destroy(darray);
}
