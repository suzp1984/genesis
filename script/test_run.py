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
from optparse import OptionParser
import sys
import os

CONFIG_NAME = "config.prop"
config_dir = os.path.dirname(os.path.abspath(__file__))
config_file = os.path.join(config_dir,  CONFIG_NAME)
test_bin_dir = os.path.join(os.path.dirname(config_dir), 'build/test/')

config = ConfigParser.ConfigParser()
config.read(config_file)

test_dir = config.get("test_case", "test_dir")

opt_parser = OptionParser()
opt_parser.add_option("-l", "--list", help="list all test case", action="store_true", dest="get_list")
opt_parser.add_option("-a", "--all", help="run all test cases", action="store_true", dest="run_all")
opt_parser.add_option("-t", "--test-run", help="choice a test list to run", action="store", dest="test_list")
opt_parser.set_defaults(get_list=False, run_all=False, test_list=None)

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

def foreach_test_case(cmd):
    for test in get_exe_file(test_bin_dir):
        if hasattr(cmd, '__call__'):
            cmd(test)

def print_cmd(test):
    filename = os.path.basename(test)
    if filename.startswith('test_'):
        filename = filename[5:]
    print "\t%s" % filename

def run_cmd(test):
    if not os.path.exists(test):
        print "\tTest Case [%s] did not exists", os.path.basename(test)
        return
    print "***************"
    print "Running test case: " + os.path.basename(test)
    popen = subprocess.Popen(test, stdout=subprocess.PIPE, cwd=os.path.dirname(test))
    popen.wait()
    output = popen.stdout.read()
    print output
     
if __name__ == "__main__":
    import subprocess
    (option_cmd, args) = opt_parser.parse_args()

    if option_cmd.get_list:
        foreach_test_case(print_cmd)
        sys.exit(0)

    if option_cmd.run_all:
        foreach_test_case(run_cmd)
        sys.exit(0)

    if option_cmd.test_list:
        testcases = option_cmd.test_list.split(',')
        for test in testcases:
            test = 'test_' + test
            test = os.path.join(test_bin_dir, test)
            run_cmd(test)
        sys.exit(0)

    for file in get_exe_file(test_bin_dir):
        print "***************"
        print "Running test case: " + os.path.basename(file)
        popen = subprocess.Popen(file, stdout=subprocess.PIPE, cwd=os.path.dirname(file))
        popen.wait()
        output = popen.stdout.read()
        print output

