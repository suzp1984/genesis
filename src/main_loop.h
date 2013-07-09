/*
 * File:    main_loop.h
 * Author:  zxsu <suzp1984@gmail.com>
 * Brief:   reactor's main loop interface
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
 * 2013-07-08 15:19 zxsu <suzp1984@gmail.com> created.
 */

#ifndef _MAIN_LOOP_H
#define _MAIN_LOOP_H

#include "typedef.h"
#include "source.h"
//#include "sources_manager.h"

DECLES_BEGIN

struct _MainLoop;
typedef struct _MainLoop MainLoop;

typedef Ret (*MainLoopRun)(MainLoop* thiz);
typedef Ret (*MainLoopQuit)(MainLoop* thiz);
typedef Ret (*MainLoopAddSource)(MainLoop* thiz, Source* source);
typedef Ret (*MainLoopRemoveSource)(MainLoop* thiz, Source* source);

typedef void (*MainLoopDestroy)(MainLoop* thiz);

struct _MainLoop {
    MainLoopRun run;
    MainLoopQuit quit;
    MainLoopAddSource add_source;
    MainLoopRemoveSource remove_source;
    MainLoopDestroy destroy;

    char priv[1];
};

static inline Ret main_loop_run(MainLoop* thiz)
{
    return_val_if_fail(thiz != NULL && thiz->run != NULL, RET_INVALID_PARAMS);

    return thiz->run(thiz);
}

static inline Ret main_loop_quit(MainLoop* thiz)
{
    return_val_if_fail(thiz != NULL && thiz->quit != NULL, RET_INVALID_PARAMS);

    return thiz->quit(thiz);
}

static inline Ret main_loop_add_source(MainLoop* thiz, Source* source)
{
    return_val_if_fail(thiz != NULL && thiz->add_source != NULL
                       && source != NULL, RET_INVALID_PARAMS);

    return thiz->add_source(thiz, source);
}

static inline Ret main_loop_remove_source(MainLoop* thiz, Source* source)
{
    return_val_if_fail(thiz != NULL && thiz->remove_source != NULL
                       && source != NULL, RET_INVALID_PARAMS);

    return thiz->remove_source(thiz, source);
}

static inline void main_loop_destroy(MainLoop* thiz)
{
    return_if_fail(thiz != NULL && thiz->destroy != NULL);

    return thiz->destroy(thiz);
}

DECLES_END

#endif /* _MAIN_LOOP_H */
