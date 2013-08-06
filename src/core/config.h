/*
 * File:    config.h
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
 * 2013-08-06 10:57 zxsu <suzp1984@gmail.com> created.
 */

#ifndef _CONFIG_H
#define _CONFIG_H

#include "typedef.h"

DECLES_BEGIN

struct _Config;
typedef struct _Config Config;

typedef Ret (*ConfigLoad)(Config* thiz, const char* config_file);
typedef size_t (*ConfigGetModulesCount)(Config* thiz);
typedef Ret (*ConfigGetModuleNameById)(Config* thiz, size_t index, char** module);
typedef Ret (*ConfigGetModuleLibPath)(Config* thiz, char** path);

typedef void (*ConfigDestroy)(Config* thiz);

struct _Config {
    ConfigLoad load;
    ConfigGetModulesCount get_modules_count;
    ConfigGetModuleNameById get_module_name_by_id;
    ConfigGetModuleLibPath get_module_lib_path;

    ConfigDestroy destroy;
    char* priv[1];
};

static inline Ret config_load(Config* thiz, const char* config_file) 
{
    return_val_if_fail(thiz != NULL && 
                       thiz->load != NULL &&
                       config_file != NULL, RET_INVALID_PARAMS);

    return thiz->load(thiz, config_file);
}

static inline size_t config_get_modules_count(Config* thiz)
{
    return_val_if_fail(thiz != NULL && thiz->get_modules_count != NULL, 0);

    return thiz->get_modules_count(thiz);
}

static inline Ret config_get_module_name_by_id(Config* thiz, size_t index, char** module)
{
    return_val_if_fail(thiz != NULL && 
                       thiz->get_module_name_by_id != NULL &&
                       index >= 0 &&  module != NULL, RET_INVALID_PARAMS);

    return thiz->get_module_name_by_id(thiz, index, module);
}

static inline Ret config_get_module_lib_path(Config* thiz, char** path)
{
    return_val_if_fail(thiz != NULL && thiz->get_module_lib_path != NULL &&
                       path != NULL, RET_INVALID_PARAMS);

    return thiz->get_module_lib_path(thiz, path);
}

static inline void config_destroy(Config* thiz)
{
    return_if_fail(thiz != NULL &&  thiz->destroy != NULL);

    return thiz->destroy(thiz);
}

DECLES_END

#endif /* _CONFIG_H */
