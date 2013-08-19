/*
 * File:    pipe_socketpair.h
 * Author:  zxsu <suzp1984@gmail.com>
 * Brief:   socket pair implementation of pipe
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
 * 2013-08-19 11:17 zxsu <suzp1984@gmail.com> created.
 */

#ifndef _PIPE_SOCKETPAIR_H
#define _PIPE_SOCKETPAIR_H

#include "pipe.h"

DECLES_BEGIN

Pipe* pipe_socketpair_create();

DECLES_END

#endif /* _PIPE_SOCKETPAIR_H */