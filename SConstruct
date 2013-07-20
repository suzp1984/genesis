env = Environment()
Export('env')

## the targets should include utils-test test
print "Build Targets is ", map(str, BUILD_TARGETS)

if 'test' in COMMAND_LINE_TARGETS:
    print 'test cmd line'
    exit

SConscript('src/SConscript', variant_dir='build/src', duplicate=0)
SConscript('utils/SConscript', variant_dir='build/utils', duplicate=0)
