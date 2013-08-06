/*
 * File:    test_config_xml_expat.cpp
 * Author:  zxsu <suzp1984@gmail.com>
 * Brief:   test case for config_xml_expat
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
 * 2013-08-06 16:54 zxsu <suzp1984@gmail.com> created.
 */

#include <gtest/gtest.h>

#include "config_xml_expat.h"

TEST(CONFIG_XML_EXPAT_TEST, simple_test) {
    Config* config = config_xml_expat_create();
    char* path;
    char* module;

    ASSERT_EQ(0, config_get_modules_count(config));
    ASSERT_EQ(RET_OK, config_load(config, "../../src/core/genesis_conf.xml"));
    ASSERT_EQ(RET_OK, config_get_module_lib_path(config, &path));
    ASSERT_EQ(1, config_get_modules_count(config));
    ASSERT_EQ(RET_OK, config_get_module_name_by_id(config, 0, &module));
    ASSERT_EQ(0, strcmp(path, "/usr/local/genesis/"));
    ASSERT_EQ(0, strcmp(module, "hello"));

    config_destroy(config);
}
