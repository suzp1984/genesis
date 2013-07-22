env = Environment()
env.Append(CPPPATH='utils:src')
Export('env')

print env['CPPPATH']
## the targets should include utils-test test
print "Build Targets is ", map(str, BUILD_TARGETS)

if 'test' in COMMAND_LINE_TARGETS:
    print 'test cmd line'
    SConscript('test/SConscript', variant_dir='build/test', duplicate=0)
    exit

# SConscript('src/SConscript', variant_dir='build/src', duplicate=0)
utils_lib = SConscript('utils/SConscript', variant_dir='build/utils', duplicate=0)

print utils_lib
