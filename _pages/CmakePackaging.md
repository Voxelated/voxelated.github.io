---
layout:     page
title:      Packaging Libraries with CMake
permalink:  CmakePackaging.html
author:     Rob Clucas
---

This post describes how to create a ```PojectConfig.cmake``` file which packages
a project ```Foo```.

It's important that the package configuration not use absolute paths, so that
the package is relocatable. When another project uses our library (Foo), we
would like that project to be able to simply do

~~~cmake
find_package(Foo COMPONENTS FooComponents)
~~~

and have our library Foo be found, with the following (minimal) variables
defined:

| Variable  | Description |
|:----------|:------------|
| **Foo_CMAKE_DIR** | Location of Foo's installed cmake files |
| **Foo_INCLUDE_DIRS** | The location of the header files for Foo |
| **Foo_LIBRARY_DIRS** | The location of Foo's libraries |
| **Foo_LIBRARIES**    | A list of all libraries defined by Foo |
| **Foo_LIBS**         | A list of libraries specified with the COMPONENTS
command when using find package |
| **Foo_DEFINITIONS**  | Compiler flags required by the source |
| **Foo_FOUND**        | If the library Foo was found |
| **Foo_DIR**          | The prefix of the directory where Foo was found |

Additionally, we would like the targets defined by Foo to be accessible
individually to the user of Foo. For example, if Foo defines libraries Bar and
Baz, then a project which defines a target UserTarget which wants to use only
Bar and Baz should be able to do:

```cmake
target_link_libraries(UserTarget Foo::Bar Foo::Baz)
```

Further, the reason that we want variables ``Foo_LIBRARIES`` (listing all Foo's
libraries) and ``Foo_LIBS`` is so that if UserTarget wants to link against
__all__ of Foo's libs, then they do:

```cmake
target_link_libraries(UserTarget ${Foo_LIBRARIES})
```

However, if they only want to use some of the libraries, then they can do:

```cmake
find_package(Foo COMPONENTS Bar Baz Other)

...


target_link_libraries(UserTarget ${Foo_LIBS})
```

## The FooConfig.cmake file


The component ``Foo_DIR`` is done automatically by Cmake if ``Foo_FOUND``
is not set to __False__ by the FooConfig.cmake file, so there is not much to
do for that.

The first thing to do is to get the installation prefix which defines where
Foo is installed, which can be done with:

```cmake
get_filename_component(Foo_INSTALL_PREFIX "${CMAKE_CURRENT_LIST_FILE}" PATH)
```

Next we want to include all the targets so that we get the above functionality,
to do so with:

```cmake
include("${CMAKE_CURRENT_LIST_DIR}/FooTargets.cmake")
```

where ``FooTargets.cmake`` is made be the root CMakeList.txt file, see below.
Additionally, include any other custom cmake files the project defines, which
will then allow them to be used by users of Foo.


Next we set most of the variables. This is straightforward, and is done as
follows:

```cmake
set(Foo_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/../../../include")
set(Foo_LIBRARY_DIRS "${CMAKE_CURRENT_LIST_DIR}../../../lib"     )
set(Foo_LIBRARYS      -lFooLib1 -lFooLib2                        )
set(Foo_DEFINITIONS  -std=c++1z                                  )
```

In the above ``CMAKE_CURRENT_LIST_DIR`` is the path where the FooConfig.cmake
file is installed, so if the Project installation structure is:

```
| INSTALL_PREFIX/
|--| include/
|--| lib/
   |-- lib.so/lib.a/lib.dylib files ...
   |--| cmake/
      |--| Foo/
         |-- FooConfig.cmake
```

then ``CMAKE_CURRENT_LIST_DIR`` is ``INSTALL_PREFIX/lib/cmake/Foo``. This is
project specific and is set in the root CMakeList.txt file, however, this is
convention and should be followed. If not followed, modify the variable setting
about to reflect the alternative locations.

Lastely, we need to check that the components specified by the user of Foo are
found, and then set ``Foo_LIBS`` to those libs, which can be done by defining
the supported components:

```cmake
// If FooLib1 and FooLib2 are the only supported components:
set(SupportedComponents FooLib1 FooLib2)
```

Then we just need to search through the supported components as follows:

```cmake
# Foo_FIND_COMPONENTS defined by cmake
foreach(comp ${Foo_FIND_COMPONENTS})
  if (NOT ";${SupportedComponents};" MATCHES comp)
    set(Foo_FOUND False)
    set(Foo_NOT_FOUND_MESSAGE "Unsupported component: ${comp}")
  endif()
  set(Foo_LIBS "${Foo_LIBS} -l{comp}")
  if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/${comp}Targets.cmake")
    include("${CMAKE_CURRENT_LIST_DIR}/${comp}Targets.cmake")
  endif()
endforeach()
```

And that's all, for a minimal FooConfig.cmake. The full file is:

```cmake
get_filename_component(Foo_INSTALL_PREFIX "${CMAKE_CURRENT_LIST_FILE}" PATH)

# Define the cmake installation directory:
set(Foo_CMAKE_DIR "${CMAKE_CURRENT_LIST_DIR}")

# Provide all the library targets:
include("${CMAKE_CURRENT_LIST_DIR}/FooTargets.cmake")

# Include all the custom cmake scripts ...

# Define the include directories:
set(Foo_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/../../../include")
set(Foo_LIBRARY_DIRS "${CMAKE_CURRENT_LIST_DIR}/../../../lib"     )
set(Foo_LIBRARYS      -lFooLib1 FooLib2)
set(Foo_DEFINITIONS  -std=c++1z)

set(SupportedComponents FooLib1 FooLib2)

set(Foo_FOUND True)

# Check that all the components are found:
# And add the components to the Foo_LIBS parameter:
foreach(comp ${Foo_FIND_COMPONENTS})
  if (NOT ";${SupportedComponents};" MATCHES comp)
    set(Foo_FOUND False)
    set(Foo_NOT_FOUND_MESSAGE "Unsupported component: ${comp}")
  endif()
  set(Foo_LIBS "${Foo_LIBS} -l{comp}")
  if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/Foo${comp}Targets.cmake")
    include("${CMAKE_CURRENT_LIST_DIR}/Foo${comp}Targets.cmake")
  endif()
endforeach()

```

## The CMakeList.txt file

For the root CMakeLists.txt file, we need to provide instructions for the
project. This is pretty simple, and we just need to create a package version 
file (which CMake can do for us), export the porject targets, and provide the
command to tell cmake where to install the package configuration (Cmake will
install the files relative to ``CMAKE_INSTALL_PREFIX``). Add the following to
the root CMakeLists.txt file (assuming that the FooConfig.cmake file as
described above is at ``PROJECT_ROOT/cmake/FooConfig.cmake``):

```cmake
cmake_minimum_required(VERSION 3.4)
project(Foo)
set(Foo_VERSION 0.0.1)

# Create the libraires:
add_library(FooLib1 FooLib1.cpp)
install(TARGETS  FooLib1
        EXPORT   FooTargets
        ARCHIVE  DESTINATION lib
        LIBRARY  DESTINATION lib
        RUNTIME  DESTINATION bin)
# This will automatically include the location of the header files used by
# foo if a target is linked against Foo::FooLib1
target_include_directories(FooLib1 PUBLIC ${CMAKE_INSTALL_PREFIX}/include)

# Same for FooLib2 ...

# Provided by Cmake:
include(CMakePackageConfigHelpers)

# Creates FooConfigVersion.cmake in the build/Foo directory:
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/Foo/FooConfigVersion.cmake"
  VERSION       ${Foo_VERSION}
  COMPATIBILITY AnyNewerVersion)

# Export the targets (change namespace appropriately):
export(EXPORT    FooTargets
       FILE      "${CMAKE_CURRENT_BINARY_DIR}/Foo/FooTargets.cmake"
       NAMESPACE Foo::)

# Copy the FooConfig.cmake to the build/Foo directory:
configure_file(cmake/FooConfig.cmake
               "${CMAKE_CURRENT_BINARY_DIR}/Foo/FooConfig.cmake"
               COPYONLY)

# This is relative to CMAKE_INSTALL_PREFIX:
# Change the location appropriately:
set(ConfigPackageLocation lib/cmake/Foo)
install(EXPORT      FooTargets
        FILE        FooTargets.cmake
        NAMESPACE   Foo::
        DESTINATION ${ConfigPackageLocation})

# This also installs relative to CMAKE_INSTALL_PREFIX:
install(
  FILES       cmake/FooConfig.cmake
              "${CMAKE_CURRENT_BINARY_DIR}/Foo/FooConfigVersion.cmake"
  DESTINATION ${ConfigPackageLocation})

# This is for the source files, change location appropriately:
install(${Foo_SOURCE_DIR}/inclue DESTINATION ${CMAKE_INSTALL_PREFIX}/include})

```