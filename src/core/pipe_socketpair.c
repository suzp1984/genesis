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
 */

#include "pipe_socketpair.h"

#include <sys/types.h>
#include <sys/socket.h>

typedef struct {
    int read_fd;
    int write_fd;
} PrivInfo;

Pipe* pipe_socketpair_create()
{
    Pipe* thiz = (Pipe*)malloc(sizeof(Pipe) + sizeof(PrivInfo));
    int socket_pair[2] = {0};

    if (thiz != NULL) {
        DECLES_PRIV(priv, thiz);
        socketpair(AF_UNIX, SOCK_STREAM, 0, socket_pair);
    }

    return thiz;
}
