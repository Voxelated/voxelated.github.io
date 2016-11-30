---
layout:     page
title:      Libraries
permalink:  Libraries.html
---

This page provides a reference point (other than Pixel's repository) for all
the internal libraries. This page consists of a few parts:

  1. It defines the structure of an internal software library. This is
     important so that **all** libraries have the same structure, which makes
     navigating them simple.

  2. It defines how to correctly document a library, so that anyone not working
     on the library can easily navigate it and understand it.

  3. It defines a list of all the libraries, with a brief overview of what each
     one does.

## Library Structure
-------------------------------------------------------------------------------

All libraries should have the following structure:

## Documenting a Library
-------------------------------------------------------------------------------

Good documentation for software is arguably as important as the software
itself, and **a lot** of effort has gone into making the documentation look
good, and into ensuring that the libraries are well documented.

### Formatting

A library's documentation should be generated using Doxygen, using the custom
formatting files. The [DoxyFormat](https://github.com/PixelTechnologies/DoxyFormat)
repository has all the files which are required for ensuring that the
documentaton is correctly formatted.

The **FetchFiles.py** script will fetch the Doxygen formatting files, and put
them into a **DoxyFormat/** directory in the directory from which it was run.
In the **Docs/** directory in the library, add the file path to the relevant
section in the Doxyfile:

| Filepath to add          | Doxyfile Section      |
|:-------------------------|:----------------------|
| DoxyFormat/header.html   | HTML_HEADER           |
| DoxyFormat/footer.html   | HTML_FOOTER           |
| DoxyFormat/pixel.css     | HTML_EXTRA_STYLESHEET |
| DoxyFormat/DoxyFormat.js | HTML_EXTRA_FILES      |

Running ```doxygen``` from the ```Docs/``` directory will then allow you to
test the documentation generation for the library.

### Library Overview

Each library should have a well-written overview, which is also the main page
for the Doxygen generated documentation (the **Docs/LibName.md** file. It
should contain the following sections:

1. An introduction and decription of the purpose of the librrary i.e why the
   library was written.
2. A getting started guide for using the library.
3. Examples of intended usage for the main components.
4. Benchmarks for the library (optional but recommended). This is quite
   important for libraries which define data structures and algorithms -- the
   benchmarks should show that the containers are better than the existing open
   source/std library alternatives.


## List of Libraries
-------------------------------------------------------------------------------

| Name                                   | Description                                       |
|:---------------------------------------|:--------------------------------------------------|
| [Meta](libraries/Meta/index.html)      | Meta is Pixel's template metaprogramming library. |
| [Pulley](libraries/Pulley/index.html)  | Pulley is Pixel's general purpose library.        |

