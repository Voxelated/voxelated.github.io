---
title: Pixel Coding Conventions
keywords: Conventions
last_updated: November 7, 2016
tags: [Conventions, Style]
summary: "Guidlines and requirements for all Pixel code."
sidebar: mydoc_sidebar
permalink: CodingConventions.html
folder: Guides
---

# Introduction

This page describes the coding conventions for Pixel's software. The conventions
particularly important for a large projects, of which there are a few. The 
conventions are designed to increase the readability of the code base, as well 
as make it easier to maintain. We also want to produce high quality, bug free 
software, with exceptional performance. The only way to do so is to establish
conventions and follow them. They will likely be imperfect, so feel free to 
make suggestions.

In general, the preference is to produce clean, modern, and efficient C++ code. 
When the choice must be made between performance and clarity, the preference is 
**generally** clarity. However, if performance is critical, then sacrificing 
clarity is acceptable, so long as there is a **detailed** comment accompanying 
the specific section of code, which explains the code, and the reason for the 
performance being critically important.

# Code Structure

## Code Width

To allow code to remain well formatted in most editors and terminals without
resizing, lines should be at most 80 columns wide. It's suggested that the 81st
column is coloured to ensure the 80 column limit is followed.

## Spaces and Tabs

Spaces must always be used over tabs. This is so that there is consistency
across all development environments. If the preferred development environment
allows it, configure it to replace all tabs with spaces.

In general, all indentation is a **2 space** indent. This allows more to fit
into the 80 column limit, and also only requires a single additional keyboard
press compared to using a tab.

There are, however, occasions where the 2 space indent is **not** the correct 
indentation. These cases are documented throughout the remainder of these 
conventions. When these cases appear, then follow what is stated in those more
specific instances.

# Files

## File Naming and Including

All files should be named using CamelCase, and should be named with the class
they define, or if they're more general than that, then they should be named
with the functionality that they define.

For template files, if there is specific implementation details which are
hidden in a ```detail``` namespace, then move the implementation to a file
with the same name with a **Impl** suffix, in a **Detail** folder.

The following are examples of some file names:
@code{.cpp}
  FunctionTraits.hpp              // Name of a class file.
  Detail/FunctionTraitsImpl.hpp   // Name of a detail file.
@endcode

Files should have the following extensions:

| File Extension | Use                                     |
| :------------- | :-------------------------------------- |
| h              | For a header without any implementation |
| hpp            | For a header with implementation        |
| cpp            | For implementation files                |
| cl             | OpenCL kernels                          |
| cu             | Cuda related code and kernels           |
| .vert          | GLSL vertex shader                      |
| .frag          | GLSL fragment shader                    |

The ```#include``` keyword for including header files should directly follow 
the file comment. Include header files minimally, and where possible, prefer to 
forward declare. Header files should be included in the following order:

* Headers local to the library/application
* Headers for other Pixel libraries used in the library/application
* Headers from the C++ standard libraries
* Any other headers

## The Define Guard

All header files (```.h``` and ```.hpp```) should use ```#define``` guards.
The guard should have the name  **PIXEL** , followed by the library name,
followed by the module name, and finally the name of the file.

The names should be **upper case** and separated by **underscores**. Each 
terminating ```#endif``` should have a comment which matches the guard name. 
For example, for a library named Meta, a module within Meta named Traits, and a
file named FunctionTraits.hpp:

@code{.cpp}
  #ifndef PIXEL_META_TRAITS_FUNCTION_TRAITS_HPP
  #define PIXEL_META_TRAITS_FUNCTION_TRAITS_HPP

  // Some code here ...

  #endif  // PIXEL_META_TRAITS_FUNCTION_TRAITS_HPP
@endcode

# Comments

Comments are extremely important for making code simpler to understand, most
especially in sections which introduce complexity in exchange for increased
performance, and in templated code -- which will likely be extensive within 
Pixel since many of the libraries use expression templates and aim for optimal
performance (where possible, try to move general templated code to Pixel's Meta
library).

Comments should we written using correct English, which means that they should
make correct use of punctuation, capitalization, spelling, and should end with
fullstops etc. All comments should describe **what** the code aims to do, and 
**why** it aims to do so, rather than **how** it does so -- which should be 
described by the code itself, if it conforms to the Pixel conventions. In 
exceptional circumstances -- when the code may be complex in order to achieve 
orders of magnitude of additional performance -- it is okay to describe how the 
code achieves its goal.

Doxygen comments should be included as described in the following sections. In 
all instances, use the ```//``` comment (even for multi-line comments), and 
the ```///``` comment for the Doxygen version of the comments. This makes the
look of the code consistent. For inline Doxygen comments, use ```\\!<```.

When comments span more than two lines, then all lines but the last should use
as much of the full 80 available columns as possible.

## Header Files

Each source file should have a comment at the top of the file which includes
the path to the file, its name, and the language (C++). Files should also 
include the license reference, the name of the library the file is part of, 
Pixel Technology's name in the copyright section, and a location to where 
the full license can be found. Lastly, Doxygen comments for the file name 
(using the ```/file```command) and a more detailed description (using 
the ```/brief``` command) must be provided. Files without headers should not be 
accepted. The file comment for a FunctionTraits.hpp file in the root directory
of the Meta Library looks as follows:

```cpp
//==--- Meta/Traits/FunctionTraits.hpp -------------------- -*- C++ -*- ---==//
//            
//                                Pixel : Meta 
//
//                  Copyright (c) 2016 Pixel Technologies, Ltd.
//
//  This file is distributed under the MIT License. See LICENSE for details.
//
//==-----------------------------------------------------------------------==//
//
/// \file  FunctionTraits.hpp
/// \brief This file defines functionality to get properties of a function at
///        compile time.
//
//==-----------------------------------------------------------------------==//
```
