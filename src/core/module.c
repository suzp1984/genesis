/*
 * File:    module.c
 * Author:  zxsu <suzp1984@gmail.com>
 * Brief:   module
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
 * 2013-07-29 16:57 zxsu <suzp1984@gmail.com> created.
 */

#include "module.h"
#include "module_sym.h"

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <dlfcn.h>

#define MODULE_PATH "./"
#define MODULE_PATH2 "~/.genesis/modules/"

struct _Module
{
    char* name;
    char* argument;
    struct ModuleInfo* info;
    void* ctx;
    void* handler;
    char* lib_path;
    Allocator* alloc;
    Logger* logger;
};

static Ret module__load(Module* thiz, const char* name)
{
    return_val_if_fail(thiz != NULL && name != NULL, RET_INVALID_PARAMS);

    char path[PATH_MAX];
    void* handler;
    struct ModuleInfo* info;

    // first try lib_path, then ./, then ~/.genesis/modules/
    snprintf(path, sizeof(path), "%s/lib%s.so", thiz->lib_path, name);
    if (access(path, R_OK) != 0) {
        snprintf(path, sizeof(path), "%s/lib%s.so", MODULE_PATH, name);    
    }
    
    if (access(path, R_OK) != 0) {
        snprintf(path, sizeof(path), "%s/lib%s.so", MODULE_PATH2, name);
    }

    if (access(path, R_OK) != 0) {
        logger_error(thiz->logger, "%s: access path %s fail", __func__, path);
        return RET_FAIL;
    }

    handler = dlopen(path, RTLD_LAZY);
    if (handler == NULL) {
        logger_error(thiz->logger, "%s: dlopen %s return NULL", __func__, path);
        return RET_FAIL;
    }

    thiz->handler = handler;

    const char* sym = MODULE_SYM_INFO_AS_STR;
    info = (struct ModuleInfo*)dlsym(handler, sym);
    if (info == NULL) {
        logger_error("%s: can not find symble = %s", __func__, sym);
        return RET_FAIL;
    }

    thiz->info = info;
    return RET_OK;
}

Module* module_create(const char* name, const char* arguments, const char* lib_path, Allocator* alloc, Logger* logger, void* ctx)
{
    return_val_if_fail(name != NULL, NULL);

    Module* thiz = (Module*)allocator_alloc(alloc, sizeof(Module));

    if (thiz != NULL) {
        thiz->logger = logger;
        thiz->ctx = ctx;
        thiz->name = strdup(name);
        thiz->alloc = alloc;
        if (lib_path == NULL) {
            lib_path = MODULE_PATH;
        }
        thiz->lib_path = strdup(lib_path);
        if (arguments) {
            thiz->argument = strdup(arguments);
        }

        if (module__load(thiz, name) != RET_OK) {
            logger_error(thiz->logger, "%s: module__load fail", __func__);
            module_destroy(thiz);
            return NULL;
        }
    }

    return thiz;
}

Ret module_init(Module* thiz, void* ctx)
{
    return_val_if_fail(thiz != NULL, RET_INVALID_PARAMS);

    if (thiz->info && thiz->info->init) {
        return thiz->info->init(thiz, ctx);
    }

    return RET_OK;
}

Ret module_start(Module* thiz, void* ctx)
{
    return_val_if_fail(thiz != NULL, RET_INVALID_PARAMS);

    if (thiz->info && thiz->info->start) {
        return thiz->info->start(thiz, ctx);
    }

    return RET_OK;
}

Ret module_done(Module* thiz, void* ctx)
{
    return_val_if_fail(thiz != NULL, RET_INVALID_PARAMS);

    if (thiz->info && thiz->info->done) {
        return thiz->info->done(thiz, ctx);
    }

    return RET_OK;
}

Ret module_set_name(Module* thiz, const char* name)
{
    return_val_if_fail(thiz != NULL && name != NULL, RET_INVALID_PARAMS);

    SAFE_FREE(thiz->name);
    thiz->name = strdup(name);

    return RET_OK;
}

Ret module_get_name(Module* thiz, char** name)
{
    return_val_if_fail(thiz != NULL && name != NULL, RET_INVALID_PARAMS);

    *name = thiz->name;

    return RET_OK;
}

void module_destroy(Module* thiz)
{
    return_if_fail(thiz != NULL);

    if (thiz->handler != NULL) {
        dlclose(thiz->handler);
        thiz->handler = NULL;
    }

    SAFE_FREE(thiz->name);
    SAFE_FREE(thiz->lib_path);    
    SAFE_FREE(thiz->argument);

    allocator_free(thiz->alloc, thiz);
}
