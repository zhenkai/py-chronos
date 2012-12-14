from distutils.core import setup
from distutils.extension import Extension

extension_name = 'chronos'
extension_version = '1.0'

include_dirs = [ '/opt/local/include', '/usr/local/include', '/usr/include' ]

library_dirs = [ '/opt/local/lib', '/usr/local/lib', '/usr/lib' ]

libraries = [ 'boost_python-mt', 'sync' ]

source_files = [ 'chronos.cpp', 'simple-chronos-socket.cpp' ]

setup( name = extension_name, version = extension_version, ext_modules = [Extension (extension_name, source_files, include_dirs = include_dirs, library_dirs = library_dirs, libraries = libraries)] )
