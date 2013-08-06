/*
 * File:    module_sym.h
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
 * 2013-07-29 22:09 zxsu <suzp1984@gmail.com> created.
 */

#ifndef _MODULE_SYM_H
#define _MODULE_SYM_H

#include "typedef.h"
#include "module.h"

DECLES_BEGIN

#define MODULE_SYM_INFO FMI
#define MODULE_SYM_INFO_AS_STR "FMI"

typedef Ret (*ModuleInitFunc)(Module* thiz, void* ctx);
typedef Ret (*ModuleStartFunc)(Module* thiz, void* ctx);
typedef Ret (*ModuleDoneFunc)(Module* thiz, void* ctx);

struct ModuleInfo
{
    const char* author;
    const char* version;
    const char* description;
    const char* usage;

    ModuleInitFunc init;
    ModuleStartFunc start;
    ModuleDoneFunc done;
};

DECLES_END

#endif /* _MODULE_SYM_H */
