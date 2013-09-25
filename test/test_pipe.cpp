/*
 * File:    test_pipe.cpp
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
 * 2013-07-27 16:56 zxsu <suzp1984@gmail.com> created.
 * 2013-09-25 22:09 zxsu <suzp1984@gmail.com> add socketpair test
 */

#include <gtest/gtest.h>
#include <string.h>

#include "pipe_default.h"
#include "pipe_socketpair.h"

TEST(PipeDefaultTest, test1) {
    char buf[4] = {0};
    Pipe* pipe = pipe_default_create();

    ASSERT_EQ(4, pipe_write(pipe, "abc", 4));
    ASSERT_EQ(4, pipe_read(pipe, buf, 4));
    ASSERT_EQ(0, strncmp("abc", buf, 4));

    pipe_destroy(pipe);
}

TEST(PipeSocketPairTest, test1) {
    char buf[4] = {0};
    Pipe* socketpair = pipe_socketpair_create();
    ASSERT_EQ(4, pipe_write(socketpair, "abc", 4));
    ASSERT_EQ(4, pipe_read(socketpair, buf, 4));
    ASSERT_EQ(0, strncmp("abc", buf, 4));

    pipe_destroy(socketpair);
}
