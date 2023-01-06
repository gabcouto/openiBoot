#
# The root build file for OpeniBoot.
#

import SCons

#
# Configuration, change this stuff
#
version="0.2"
# /Configuration

SConscript([
	'scons/ARMEnvironment.SConscript',
	'scons/Git.SConscript',
	])
Import('*')

henv = Environment()
Export('henv')

henv.Append(CPPFLAGS = ['-g'])

env = ARMEnvironment()
env.Append(CPPDEFINES=[
	'OPENIBOOT_VERSION='+version,
	'OPENIBOOT_VERSION_BUILD='+GetGitCommit(),
	])
env.Append(CPPFLAGS = ['-Wall', '-Werror', '-O3', '-Ttext=0x0'])
Export('env')

def localize(env, ls):
	return [File(f) for f in ls]
env.AddMethod(localize, "Localize")

def build_target(env, name, fname, flag, sources, img3template=None):
	env = env.Clone()
	env['OBJPREFIX'] = name + '_'	
	env.Append(CPPDEFINES=[flag])

	# Work out filenames
	elf_name = '#' + fname
	bin_name = elf_name + '.bin'
	img3_name = elf_name + '.img3'

	def listify(ls):
		ret = []
		for e in ls:
			if SCons.Util.is_List(e):
				ret += listify(e)
			else:
				ret.append(e)
		return ret
	sources = listify(sources)

	# Add init/sentinal, but make sure first file linked is still first
	# (this means that _start gets run first... kinda important) -- Ricky26
	sources = sources[:1] + ['#init.c'] + sources[1:] + ['#sentinel.c']

	# Add Targets
	elf = env.Program(elf_name, sources)
	bin = env.Make8900Image(bin_name, elf)
	if img3template is not None:
		img3 = env.Make8900Image(img3_name, elf+['#mk8900image/%s.img3' % img3template])
		Alias(name, img3)
	else:
		img3 = None
		Alias(name, bin)

	globals()[elf_name] = elf
	globals()[bin_name] = bin
	globals()[img3_name] = img3
	Export([elf_name, bin_name, img3_name])

	return elf, bin, img3
env.AddMethod(build_target, 'OpenIBootTarget')

# Sources for menu
menu_src = env.Localize([
	'menu.c',
	])
Export('menu_src')

# Sources for installer image
installer_src = env.Localize([
	'installer.c',
	])
Export('installer_src')

# Base Target Sources
base_src = env.Localize([
	'acm.c',
	'audiohw.c',
	'actions.c',
	'commands.c',
	'framebuffer.c',
	'images.c',
	'malloc.c',
	'nvram.c',
	'openiboot.c',
	'printf.c',
	'scripting.c',
	'sha1.c',
	'stb_image.c',
	'syscfg.c',
	'tasks.c',
	'usb.c',
	'util.c',
	])
Export('base_src')

# Build Host Modules
henv.SConscript([
	'images/SConscript',
	'mk8900image/SConscript',
	])

# Build Modules
env.SConscript([
	'hfs/SConscript',
	'radio-pmb8876/SConscript',
	'radio-pmb8878/SConscript',
	'arch-arm/SConscript',
	])
