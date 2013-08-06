/*
 * File:    module.h<2>
 * Author:  zxsu <suzp1984@gmail.com>
 * Brief:   module header
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
 * 2013-07-29 16:52 zxsu <suzp1984@gmail.com> created.
 */

#ifndef _MODULE_H
#define _MODULE_H

#include "typedef.h"
#include "allocator.h"

DECLES_BEGIN

struct _Module;
typedef struct _Module Module;

Module* module_create(const char* name, const char* arguments, const char* lib_path, Allocator* alloc, void* ctx);

Ret module_init(Module* thiz, void* ctx);
Ret module_start(Module* thiz, void* ctx);
Ret module_done(Module* thiz, void* ctx);

Ret module_set_name(Module* thiz, const char* name);
Ret module_get_name(Module* thiz, char** name);

void module_destroy(Module* thiz);

DECLES_END

#endif /* _MODULE_H */
