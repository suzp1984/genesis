/*
 * File:    pipe_socketpair.c
 * Author:  zxsu <suzp1984@gmail.com>
 * Brief:   socketpair implementation of pipe.h
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
 * 2013-08-19 11:19 zxsu <suzp1984@gmail.com> created.
 * 2013-09-25 22:06 zxsu <suzp1984@gmail.com> edit
 */

#include "pipe_socketpair.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

typedef struct {
    int read_fd;
    int write_fd;
} PrivInfo;

static int pipe_socketpair_read(Pipe* thiz, void* buf, size_t length)
{
    DECLES_PRIV(priv, thiz);

    return read(priv->read_fd, buf, length);
}

static int pipe_socketpair_write(Pipe* thiz, const void* buf, size_t length)
{
    DECLES_PRIV(priv, thiz);

    return write(priv->write_fd, buf, length);
}

static int pipe_socketpair_get_read_handler(Pipe* thiz)
{
    DECLES_PRIV(priv, thiz);

    return priv->read_fd;
}

static int pipe_socketpair_get_write_handler(Pipe* thiz)
{
    DECLES_PRIV(priv, thiz);

    return priv->write_fd;
}

static int pipe_socketpair_check(Pipe* thiz)
{
    return -1;
}

static void pipe_socketpair_destroy(Pipe* thiz)
{
    DECLES_PRIV(priv, thiz);

    if (priv->read_fd >=0) {
        close(priv->read_fd);
        priv->read_fd = -1;
    }

    if (priv->write_fd >=0) {
        close(priv->write_fd);
        priv->write_fd = -1;
    }

    SAFE_FREE(thiz);
}

Pipe* pipe_socketpair_create()
{
    Pipe* thiz = (Pipe*)malloc(sizeof(Pipe) + sizeof(PrivInfo));
    int socket_pair[2] = {0};

    if (thiz != NULL) {
        DECLES_PRIV(priv, thiz);
        thiz->read = pipe_socketpair_read;
        thiz->write = pipe_socketpair_write;
        thiz->get_read_fd = pipe_socketpair_get_read_handler;
        thiz->get_write_fd = pipe_socketpair_get_write_handler;
        thiz->destroy = pipe_socketpair_destroy;

        socketpair(AF_UNIX, SOCK_STREAM, 0, socket_pair);
        priv->read_fd = socket_pair[0];
        priv->write_fd = socket_pair[1];
    }

    return thiz;
}
