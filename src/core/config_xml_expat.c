/*
 * File:    config_xml_expat.c
 * Author:  zxsu <suzp1984@gmail.com>
 * Brief:   use expat to parser xml config file
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
 * 2013-08-06 11:12 zxsu <suzp1984@gmail.com> created.
 */

#include "config_xml_expat.h"
#include "dlist.h"

#include <expat.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define TOP_ELEMENT "genesis"
#define MODULE_LIB_PATH_ELEMENT "module_path"
#define MODULE_ELEMENT "modules"
#define MODULE_ITEM_ELEMENT "item"

typedef enum _XML_State {
    NULL_STATE = 0,
    IN_GENESIS,
    IN_MODULE_PATH,
    IN_MODULES
} XML_State;

typedef struct {
    XML_Parser parser;
    XML_State state;
    char* module_path;
    DList* modules_name;
} PrivInfo;

static void _modules_name_node_destroy(void* ctx, void* data)
{
    char* name = (char*)data;
    SAFE_FREE(name);
}

static void _xml_expat_start_element(void* userdata, const char* el, const char** attr)
{
    Config* config = (Config*)userdata;
    DECLES_PRIV(priv, config);
    char* name = NULL;

    if (!strcmp(el, TOP_ELEMENT)) {
        priv->state = IN_GENESIS;
    } else if (!strcmp(el, MODULE_LIB_PATH_ELEMENT)) {
        priv->state = IN_MODULE_PATH;
        if (!strcmp("value", attr[0])) {
            priv->module_path = strdup(attr[1]);
        }
    } else if (!strcmp(el, MODULE_ELEMENT)) {
        priv->state = IN_MODULES;
    } else if (priv->state == IN_MODULES && !strcmp(el, MODULE_ITEM_ELEMENT)) {
        if (!strcmp("name", attr[0])) {
            name = strdup(attr[1]);
            dlist_append(priv->modules_name, (void*)name);
        }
    }
}

static void _xml_expat_end_element(void* userdata, const char* el)
{
    Config* config = (Config*)userdata;
    DECLES_PRIV(priv, config);

    if (!strcmp(el, TOP_ELEMENT)) {
        priv->state = NULL_STATE;
    } else if (!strcmp(el, MODULE_ELEMENT)) {
        priv->state = IN_GENESIS;
    } else if (!strcmp(el, MODULE_ITEM_ELEMENT)) {
        priv->state = IN_MODULES;
    } else if (!strcmp(el, MODULE_LIB_PATH_ELEMENT)) {
        priv->state = IN_GENESIS;
    }
}

static Ret config_xml_expat_load(Config* thiz, const char* config_file)
{
    DECLES_PRIV(priv, thiz);

    struct stat fstat;
    char* buf;
    int fd;
    int ret = RET_OK;

    if (stat(config_file, &fstat)) {
        return RET_FAIL;
    }

    buf = (char*)malloc(fstat.st_size);

    if ((fd = open(config_file, O_RDONLY)) < 0) {
        ret = RET_FAIL;
        goto fail;
    }

    read(fd, buf, fstat.st_size);
    close(fd);
    XML_SetElementHandler(priv->parser, _xml_expat_start_element, _xml_expat_end_element);

    if (!XML_Parse(priv->parser, buf, fstat.st_size, 1)) {
        ret = RET_FAIL;
        goto fail;
    }

fail:
    SAFE_FREE(buf);
    return ret;
}

static size_t config_xml_expat_get_modules_count(Config* thiz)
{
    DECLES_PRIV(priv, thiz);
    
    return dlist_length(priv->modules_name);
}

static Ret config_xml_expat_get_module_name_by_id(Config* thiz, size_t index, char** module)
{
    DECLES_PRIV(priv, thiz);
    
    return dlist_get_by_index(priv->modules_name, index, (void**)module);
}

static Ret config_xml_expat_get_module_lib_path(Config* thiz, char** path)
{
    DECLES_PRIV(priv, thiz);
    
    *path = priv->module_path;
    return RET_OK;
}

static void config_xml_expat_destroy(Config* thiz)
{
    DECLES_PRIV(priv, thiz);

    XML_ParserFree(priv->parser);
    SAFE_FREE(priv->module_path);
    dlist_destroy(priv->modules_name);
    SAFE_FREE(thiz);
}

Config* config_xml_expat_create()
{
    Config* thiz = (Config*)malloc(sizeof(Config) + sizeof(PrivInfo));

    if (thiz != NULL) {
        DECLES_PRIV(priv, thiz);
        thiz->load = config_xml_expat_load;
        thiz->get_modules_count = config_xml_expat_get_modules_count;
        thiz->get_module_name_by_id = config_xml_expat_get_module_name_by_id;
        thiz->get_module_lib_path = config_xml_expat_get_module_lib_path;
        thiz->destroy = config_xml_expat_destroy;

        priv->parser = XML_ParserCreate(NULL);
        XML_SetUserData(priv->parser, (void*)thiz);
        priv->state = NULL_STATE;
        priv->module_path = NULL;
        priv->modules_name = dlist_create(_modules_name_node_destroy, NULL, NULL, NULL);
    }

    return thiz;
}
