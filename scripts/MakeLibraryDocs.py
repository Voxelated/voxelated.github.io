import subprocess, os
from shutil import copytree
from distutils.dir_util import copy_tree as copytree_ow

def git(*args):
  return subprocess.check_call(['git'] + list(args))

startDir = os.getcwd()

libraries = {
  'Meta'   : 'https://github.com/PixelTechnologies/Meta.git',
  'Pulley' : 'https://github.com/PixelTechnologies/Pulley.git'
}

# Fetch all the formatting files:
import FetchFiles

# Build docs for each of the libraries:
os.chdir(startDir)
for libname, liburl in libraries.items():
  print('\nCloning: ' + libname + ':\n')
  git('clone', liburl)

  os.chdir(libname + '/Docs')
  copytree(startDir + '/DoxyFormat', 'DoxyFormat');
  subprocess.call('doxygen')
  copytree_ow('html', '../../../libraries/' + libname)

  print('\nBuilt documentation for: ' + libname + '\n')

  os.chdir(startDir)
  subprocess.call(['rm', '-rf', libname])

os.chdir(startDir)
subprocess.call(['rm', '-rf', 'DoxyFormat'])
