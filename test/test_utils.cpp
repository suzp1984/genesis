/*
 * File:    test_utils.cpp
 * Author:  zxsu <suzp1984@gmail.com>
 * Brief:   utils test case
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
 * 2013-08-02 10:05 zxsu <suzp1984@gmail.com> created.
 */

#include <gtest/gtest.h>

#include "gs_string.h"
#include "allocator_nginx.h"
#include "logger_default.h"

TEST(UTILSTEST, gs_string_test) {
    Allocator* alloc = allocator_nginx_create(128);
    GsString* str = gs_string_create(alloc, "abc", 3);
    GsString* ather = gs_string_dup(str, alloc);
    ASSERT_EQ(0, gs_string_cmp(str, ather));
    ASSERT_EQ(3, gs_string_len(str));
    gs_string_destroy(str);
    allocator_destroy(alloc);
}

TEST(UTILSTEST, logger_default_test) {
    Logger* logger = logger_default_create();
    logger_set_level(logger, LOGGER_WARNING);
    logger_verbose(logger, "hello world %s", __func__);
    logger_info(logger, "hello world %s", __func__);
    logger_debug(logger, "hello world %s", __func__);
    logger_warning(logger, "hello world %s", __func__);
    logger_error(logger, "hello world %s", __func__);

    logger_destroy(logger);
}

TEST(LoggerTest, simpletest) {
    Logger* logger = logger_default_create();
    
    logger_info(logger, "hello world!");
    logger_verbose(logger, "nice talk!");

    logger_destroy(logger);
}

