/*
 * File:    gs_string.h
 * Author:  zxsu <suzp1984@gmail.com>
 * Brief:   a string object implementation
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
 * 2013-07-31 23:05 zxsu <suzp1984@gmail.com> created.
 */

/* 
C's string defination is really silly in this ways.
a string must be ended by 0, .....
*/

#ifndef _GS_STRING_H
#define _GS_STRING_H

#include "typedef.h"
#include "allocator.h"

DECLES_BEGIN

struct _GsString;
typedef struct _GsString GsString;

GsString* gs_string_create(Allocator* alloc, const void* str, size_t n);

GsString* gs_string_dup(GsString* thiz, Allocator* alloc);
int gs_string_cmp(GsString* thiz, GsString* target);
int gs_string_len(GsString* thiz);

void gs_string_destroy(GsString* thiz);

DECLES_END

#endif /* _GS_STRING_H */
