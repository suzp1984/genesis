/*
 * File:    genesis.c
 * Author:  zxsu <suzp1984@gmail.com>
 * Brief:   the main function of genesis
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
 * 2013-08-06 17:16 zxsu <suzp1984@gmail.com> created.
 */

#include "reactor.h"
#include "allocator_nginx.h"
#include "config_xml_expat.h"

#include <stdio.h>

int main(int argc, char* argv[])
{
    Allocator* alloc = allocator_nginx_create(1024);
    Config* config = config_xml_expat_create();
    
    config_load(config, "../../../src/app/genesis-config.xml");
    Reactor* reactor = reactor_create(config, alloc);
    reactor_run(reactor);
    
    reactor_destroy(reactor);

    config_destroy(config);

    allocator_destroy(alloc);

    return 0;
}
