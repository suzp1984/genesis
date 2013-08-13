/*
 * File:    sources_manager.h
 * Author:  zxsu <suzp1984@gmail.com>
 * Brief:   sources management
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
 * 2013-07-07 21:41 zxsu <suzp1984@gmail.com> created.
 */

#ifndef _SOURCES_MANAGER_H
#define _SOURCES_MANAGER_H

#include "source.h"
#include "typedef.h"
#include "logger.h"

DECLES_BEGIN

struct _SourcesManager;
typedef struct _SourcesManager SourcesManager;

SourcesManager* sources_manager_create(Logger* logger);

Ret sources_manager_add_source(SourcesManager* thiz, Source* source);
Ret sources_manager_del_source(SourcesManager* thiz, Source* source);

int sources_manager_get_count(SourcesManager* thiz);
Source* sources_manager_get(SourcesManager* thiz, int i);

/* Tell the main-loop break current loop and reselect */
int sources_manager_need_refresh(SourcesManager* thiz);
Ret sources_manager_set_need_refresh(SourcesManager* thiz);
Source* sources_manager_get_primary_source(SourcesManager* thiz);

void sources_manager_destroy(SourcesManager* thiz);

DECLES_END

#endif /* _SOURCES_MANAGER_H */
