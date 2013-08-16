/*
 * File:    test_main_loop.cpp
 * Author:  zxsu <suzp1984@gmail.com>
 * Brief:   main loop's test case
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
 * 2013-07-29 15:55 zxsu <suzp1984@gmail.com> created.
 */

#include <gtest/gtest.h>

#include <signal.h>

#include "main_loop_select.h"
#include "sources_manager.h"
#include "source_timer.h"
#include "logger_default.h"
#include "source_signal.h"

static Ret test_timer(void* user_data) {
    MainLoop* main_loop = (MainLoop*)user_data;
    printf("%s: timer....\n", __func__);

    main_loop_quit(main_loop);

    return RET_OK;
}

static void test_siganl(int signum, void* ctx) 
{
    MainLoop* main_loop = (MainLoop*)ctx;
    main_loop_quit(main_loop);
}

TEST(MainLoopTest, select_test) {
    Logger* logger = logger_default_create();

    SourcesManager* sources_manager = sources_manager_create(logger);
    MainLoop* select_loop = main_loop_select_create(sources_manager, logger);
    Source* timer_source = source_timer_create(2000, test_timer, (void*)select_loop);

    main_loop_add_source(select_loop, timer_source);
    main_loop_run(select_loop);

    main_loop_destroy(select_loop);
    sources_manager_destroy(sources_manager);

    logger_destroy(logger);
}

TEST(MainLoopTest, signal_test) {
    Logger* logger = logger_default_create();

    SourcesManager* sources_manager = sources_manager_create(logger);
    MainLoop* select_loop = main_loop_select_create(sources_manager, logger);

    Source* signal_source = source_signal_create(SIGALRM, test_siganl, select_loop);

//    main_loop_add_source(select_loop, signal_source);
    sources_manager_add_source(sources_manager, signal_source);
    main_loop_run(select_loop);

    main_loop_destroy(select_loop);
    sources_manager_destroy(sources_manager);

    logger_destroy(logger);
}
