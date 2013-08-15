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
import os

CONFIG_NAME = "config.prop"
config_dir = os.path.dirname(os.path.abspath(__file__))
config_file = os.path.join(config_dir,  CONFIG_NAME)
test_bin_dir = os.path.join(os.path.dirname(config_dir), 'build/test/')

config = ConfigParser.ConfigParser()
config.read(config_file)

test_dir = config.get("test_case", "test_dir")

def is_file_has_extension(path):
    if len(path.split('.')) > 1:
        return True
    else:
        return False

    
def is_test_case(path):
    filename = os.path.basename(path)
    if (filename.startswith("test_") and not is_file_has_extension(filename)):
       return True
    else:
       return False

    
def get_exe_file(exedir):
    for path, subdirs, files in os.walk(exedir):
        files.sort()
        for name in files:
            if is_test_case(name):
                yield os.path.join(path, name)


if __name__ == "__main__":
    import subprocess
    for file in get_exe_file(test_bin_dir):
        print "***************"
        print "Running test case: " + os.path.basename(file)
        popen = subprocess.Popen(file, stdout=subprocess.PIPE, cwd=os.path.dirname(file))
        popen.wait()
        output = popen.stdout.read()
        print output

    
#print test_dir
#print sys.argv

