/*
 * File:    main_loop_select.c
 * Author:  zxsu <suzp1984@gmail.com>
 * Brief:   main_loop implementation by select api
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
 * 2013-07-08 15:47 zxsu <suzp1984@gmail.com> created.
 */

#include <sys/select.h>
#include <stdlib.h>

#include "main_loop_select.h"
//#include "source_primay

typedef struct _PrivInfo {
    int running;
    fd_set fdset;
    fd_set err_fdset;
    SourcesManager* sources_manager;
} PrivInfo;

static Ret main_loop_select_run(MainLoop* thiz)
{
}

static Ret main_loop_select_quit(MainLoop* thiz)
{
}

static Ret main_loop_select_add_source(MainLoop* thiz, Source* source)
{
}

static Ret main_loop_select_remove_source(MainLoop* thiz, Source* source)
{
}

static void main_loop_select_destroy(MainLoop* thiz)
{
}

MainLoop* main_loop_select_create(SourcesManager* sources_manager)
{
    return_val_if_fail(sources_manager != NULL, NULL);

    MainLoop* thiz = (MainLoop*)malloc(sizeof(MainLoop) + sizeof(PrivInfo));

    if (thiz != NULL) {
        DECLES_PRIV(priv, thiz);

        thiz->run = main_loop_select_run;
        thiz->quit = main_loop_select_quit;
        thiz->add_source = main_loop_select_add_source;
        thiz->remove_source = main_loop_select_remove_source;
        thiz->destroy = main_loop_select_destroy;

        priv->sources_manager = sources_manager;
    }

    return thiz;
}
