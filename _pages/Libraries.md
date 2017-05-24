---
layout:     page
title:      Libraries
permalink:  Libraries.html
---

This page provides a reference point for the available libraries, and consists of
the following parts:

  1. It defines the structure of the libraries.

  2. It defines how the libraries are documented a library, so that anyone
     contributing can easilt understand the process.

  3. It defines a list of all the libraries, with a brief overview of what each
     one does.

## Library Structure
-------------------------------------------------------------------------------

All libraries should have the following structure:

~~~
| Library/
|--| apps (optional)/
   |-- CMakeLists.cpp
   |-- applications
|--| benchmarks/
   |-- CMakeLists.txt
   |-- benchmark source files
|--| cmake (optional)/
   |-- LibraryNameConfig.cmake
   |-- Custom cmake files
|--| docs/
   |-- CMakeLists.txt
   |-- Doxyfile.in
   |-- FetchFiles.py
|--| include/
   |--| Voxel/
      |--| LibraryName/
         |-- header files
|--| src/
   |-- CMakeLists.txt
   |-- source files
|--| tests/
   |-- CMakeLists.txt
   |-- test source files
|-- CMakeLists.txt
|-- LICENSE
|-- README.md
~~~

For an example, see [Voxel](https://github.com/Voxelated/Voxel). The root
```CmakeLists.txt``` file must have functionality to package the library.
See [Cmake Packaging](CmakePackaging.html). The ```FetchFiles.py``` script
fetches the required files to correctly format the Doxygen documentation, and
can be found in the  [DoxyFormat](https://github.com/Voxelated/DoxyFormat)
repository. The ```docs/``` directory in
[Voxel] (https://github.com/Voxelated/Voxel) provides a good example of how to
build a library's documentation, and requiresonly minor changes for new
library's.


## Documenting a Library
-------------------------------------------------------------------------------

Good documentation for software is arguably as important as the software
itself, and **a lot** of effort has gone into making the documentation look
good, and into ensuring that the libraries are well documented.

### Formatting

A library's documentation should be generated using Doxygen, using the custom
formatting files. The [MaterialDoxygen](https://github.com/Voxelated/MaterialDoxygen)
repository has all the files which are required for ensuring that the
documentaton is correctly formatted.

The **FetchFiles.py** script will fetch the Doxygen formatting files, and put
them into a **DoxyFormat/** directory in the directory from which it was run.
In the **docs/** directory in the library, add the file path to the relevant
section in the Doxyfile:

| Filepath to add           | Doxyfile Section      |
|:------------------------- |:----------------------|
| DoxyFormat/header.html    | HTML_HEADER           |
| DoxyFormat/footer.html    | HTML_FOOTER           |
| DoxyFormat/stylesheet.css | HTML_EXTRA_STYLESHEET |
| DoxyFormat/DoxyFormat.js  | HTML_EXTRA_FILES      |

Running ```doxygen``` from the ```docs/``` directory will then allow you to
test the documentation generation for the library.

__Note:__ The ```docs``` directory in the [Voxel](https://github.com/Voxelated/Voxel)
          repository has the correct configuration, and requires only the following
          changes (to ```Doxyfile.in``` __only__) for a new library to build documentation:

1. Change ```PROJECT_NAME``` to the project name.
2. Change ```PROJECT_BRIEF``` appropriately.
3. Change ```@Voxel_SOURCE_DIR@``` for the ```INPUT``` variable
   to ```@CmakeLibraryName_SOURCE_DIR@```
4. Change ```@Voxel_SOURCE_DIR@/README.md``` for
   the ```USE_MDFILE_AS_MAIN_PAGE``` variable
   to ```@CmakeLibraryName_SOURCE_DIR@```.

This configuration creates a ```Docs``` target for cmake, so (from the root):

~~~bash
mkdir build && cd build
cmake -D{CMAKE_PARAMS} ..
make Docs
~~~~

will make a ```html/``` directory with ```index.html``` at  ```LibRoot/build/docs/```,
which can then be opened with a browser to view the generated documentation.

### Library Overview

Each library should have a well-written overview see [Overview Formatting](#overview-formatting), which is also the main page for the Doxygen generated
documentation (the **README.md** file in the library
root directory). It should contain the following sections:

1. An introduction and decription of the purpose of the librrary i.e why the
   library was written.
2. A getting started guide (installation etc.) for using the library.
3. Examples of intended usage for the main components.
4. Benchmarks for the library (optional but recommended). This is quite
   important for libraries which implement data structures and algorithms -- the
   benchmarks should compare the implementations against existing implementations.
   To do this, use the [Google Benchmarking Framework](https://github.com/google/benchmark).

### Overview Formatting

The documentation build scripts search through the html source looking for h2
headers (```##```), and subsequent h3 headers (```###```), and generate a
dynamic table of contents for the page from thiose headers. Thus h2 and h3
headers should be used for documentation pages, unless a dynamic table of
contents is not desired, in which case use h1, h3, h4 headers.

For example, to generate a dynamic contents list with only the main headers, use h4 headers after h1/h2 headers.

## List of Libraries

The libraries are structued such that [Voxel](libraries/voxel/index.html) is the base repository which essentially contains general purpose functionality.
The whole repository must be installed, but individual components can be linked
against if desired, rather than linking against all the components (although
that option is also possible).

For example (the base library):

~~~
|<prefix>
|--| include/
   |--| Voxel/
      |--| ComponentA/
      |--| ComponentB/
~~~

There are also other libraries which have their own repositories, generally
addressing a more specific use case. They do, however, often use the base
library and it's components, or the other individual libraries. The
'standalone' repositories install to as part of the base library on the system
and can be found as components of the base library when using CMake.

For example, when they are installed, the above tree looks like:

~~~
|<prefix>
|--| include/
   |--| Voxel/
      |--| ComponentA/
      |--| ComponentB/
      |--| StandaloneA/
      |--| StandaloneB/
~~~

The following is a list of Voxel's libraries:

| Library Name | Brief Description |
|:-------------|:------------------|
| [Voxel](libraries/voxel/index.html) | Main library for Voxel, containing common functionality used by other libraries. |
| [Conky](libraries/conky/index.html) | Concurrency and parallelism library |
| [Xpress](libraries/xpress/index.html) | Expression template array library allowing Numpy like arrys in C++ |
