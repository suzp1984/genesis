#! /usr/bin/python
# File:    test_run.py
# Author:  zxsu <suzp1984@gmail.com>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Library General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
# Copyright 2005 Duke University

# History:
## =====================
# 2013-08-15 08:58 zxsu <suzp1984@gmail.com> created.
## =====================

import ConfigParser
import sys

config = ConfigParser.ConfigParser()
config.read("config.prop")

test_dir = config.get("test_case", "test_dir")

print test_dir
print sys.argv
