/*
 * File:    pipe.h
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
 * 2013-07-11 22:41 zxsu <suzp1984@gmail.com> created.
 */

#ifndef _PIPE_H
#define _PIPE_H

#include "typedef.h"

DECLES_BEGIN

struct _Pipe;
typedef struct _Pipe Pipe;

typedef int (*PipeRead)(Pipe* thiz, void* buf, size_t length);
typedef int (*PipeWrite)(Pipe* thiz, const void* buf, size_t length);
typedef int (*PipeGetReadFd)(Pipe* thiz);
typedef int (*PipeGetWriteFd)(Pipe* thiz);
typedef void (*PipeDestroy)(Pipe* thiz);

struct _Pipe {
    PipeRead read;
    PipeWrite write;
    PipeGetReadFd get_read_fd;
    PipeGetWriteFd get_write_fd;
    PipeDestroy destroy;
};

static inline int pipe_read(Pipe* thiz, void* buf, size_t length)
{
    return_val_if_fail(thiz != NULL && buf != NULL 
                       && thiz->read != NULL && length > 0, -1);
                       
    return thiz->read(thiz, buf, length);
}

static inline int pipe_write(Pipe* thiz, const void* buf, size_t length)
{
    return_val_if_fail(thiz != NULL && thiz->write != NULL 
                       && buf != NULL && length > 0, -1);

    return thiz->write(thiz, buf, length);
}

static inline int pipe_get_read_fd(Pipe* thiz)
{
    return_val_if_fail(thiz != NULL && thiz->get_read_fd != NULL, -1);

    return thiz->get_read_fd(thiz);
}

static inline int pipe_get_write_fd(Pipe* thiz)
{
    return_val_if_fail(thiz != NULL && thiz->get_write_fd != NULL, -1);

    return thiz->get_write_fd(thiz);
}

static inline void pipe_destroy(Pipe* thiz)
{
    return_if_fail(thiz != NULL && thiz->destroy != NULL);

    return thiz->destroy(thiz);
}

DECLES_END

#endif /* _PIPE_H */
