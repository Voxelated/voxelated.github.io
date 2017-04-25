# /usr/bin/python
#
#==--- VoxelDocs/MakeLibraryDocs.py -----------------------------------------==#
#
# File        : MakeLibraryDocs.py
# Description : Makes the documentation for each of the libraries.
#
#==--------------------------------------------------------------------------==#


import subprocess, os, shutil

def git(*args):
  return subprocess.check_call(['git'] + list(args))

startDir = os.getcwd()
libDir   = startDir + '/../libraries/'

libraries = {
  'Voxel'  : 'https://github.com/Voxelated/Voxel.git',
}

# Build docs for each of the libraries:
os.chdir(startDir)
for libname, liburl in libraries.items():
  if (os.path.exists(libname)):
    shutil.rmtree(libname)

  print('\nCloning: ' + libname + ':\n')
  git('clone', liburl)

  os.chdir(libname)
  os.mkdir('build')
  os.chdir('build')
  subprocess.call(['ls','-l'])
  subprocess.call(['cmake',
                   '-DCMAKE_BUILD_TYPE=Release',
                   '..'])
  subprocess.call(['make', '-j2', 'Docs'])

  outputDir = libDir + libname.lower()
  if (os.path.exists(outputDir)):
    shutil.rmtree(outputDir)

  os.rename('docs/html', outputDir)
  os.chdir(startDir);
  shutil.rmtree(libname)