env = Environment()
#env.Append(CPPPATH='utils:src')
Export('env')

#print env['CPPPATH']
## the targets should include utils-test test
print "Build Targets is ", map(str, BUILD_TARGETS)

# SConscript('src/SConscript', variant_dir='build/src', duplicate=0)
utils_lib = SConscript('utils/SConscript', variant_dir='build/utils', duplicate=0)
SConscript('test/SConscript', exports='utils_lib', variant_dir='build/test', duplicate=0)

