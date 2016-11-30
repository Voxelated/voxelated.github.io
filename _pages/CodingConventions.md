---
layout:     page
title:      Coding Conventions
permalink:  CodingConventions.html
---

This page describes the coding conventions for Pixel's software. The conventions
are particularly important for a large projects, which Pixel is. Some of the
internal libraries are themselves large projects. The conventions are designed
to increase the readability of the code base so that it's as simple as possible
for new developers to understand the code. This also makes the code easier
to maintain. We also want to produce high quality, bug free software, with 
exceptional performance, and the only way to do so is to establish conventions
and follow them. They will likely be imperfect, and should be considered a work
in progress, so feel free to make suggestions.

In general, the preference is to produce clean, modern, and efficient C++ code. 
When the choice must be made between performance and clarity, the preference is 
**generally** clarity. However, if performance is critical, then sacrificing 
clarity is acceptable, so long as there is a **detailed** comment accompanying 
the specific section of code, which explains the code, and the reason for the 
performance being critically important.

## Code Structure
-------------------------------------------------------------------------------

### Code Width

To allow code to remain well formatted in most editors and terminals, without
resizing, lines should be at most 80 columns wide. It's suggested that the 81st
column is coloured to ensure the 80 column limit is followed.

### Spaces and Tabs

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

**TODO:** Get clang format setup and specify how to use it.

## Files
-------------------------------------------------------------------------------

### File Naming

All files should be named using CamelCase, and should be named with the class
they define, or if they're more general than that, then they should be named
with the functionality that they provide.

For template files, if there is specific implementation details which are
hidden in a ```Detail::``` namespace, then move the implementation to a file
with the same name with an **Impl.hpp** suffix, in a **Detail/** folder within
the directory.

The following are examples of some file names:
```cpp
FunctionTraits.hpp              // Name of a class file.
Detail/FunctionTraitsImpl.hpp   // Name of a detail file.
```

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

### The Define Guard

All header files (```.h``` and ```.hpp```) should use ```#define``` 
guards. The guards should directly follow the file comment (see 
[Header Files](#header-files). The guard should have the name  **PIXEL** , 
followed by the library name, followed by the module name, and finally the 
name of the file.

The names should be **upper case** and separated by **underscores**. Each 
terminating ```#endif``` should have a comment which matches the guard name. 
For example, for a library named Meta, a module within Meta named Traits, and a
file named FunctionTraits.hpp:

```cpp
#ifndef PIXEL_META_TRAITS_FUNCTION_TRAITS_HPP
#define PIXEL_META_TRAITS_FUNCTION_TRAITS_HPP

// Some code here ...

#endif  // PIXEL_META_TRAITS_FUNCTION_TRAITS_HPP
```

### Including

The ```#include``` keyword for including header files should directly follow 
the define guards. Include header files minimally, and where possible, prefer
to forward declare, unless the class is a class template, which should never be
forward declared. Header files should be included in the following order:

  1. Headers local to the library/application
  2. Headers for other Pixel libraries used in the library/application
  3. Headers from the C++ standard library
  4. Any other headers

### Comments

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

### Doxygen Comments

The following must be applied when document code:

The ```\file``` and ```\brief``` comments should be used in all files. See 
[Declaration Commment](#declaration-comment) below. 

It's important to document classes thoroughly, and where the class is
sufficiently complex, example usage should be provided.

When referring to parameter names, use ```\p```.

If code it not inline, then use the ```\code{.cpp}``` and ```\endcode```
commands.

Use the ```\param[in]``` and ```\param[out]``` commands for parameter names,
followed by the name of the parameters, and a description of it's purpose. Do
the same for template parameters with the ```\tparam``` command. Align all
comments in columns. For example:

```cpp
/// Does something with \p foo.
/// \param[in] foo     Foo object to operate on.
/// \tparam    FooType The type of \p foo.
template <typename FooType>
void doFooSomething(FooType foo);
```

Prefer to descripe the return parameters in the description of the function as
this generally makes more sense. For example:

```cpp
/// Returns true if \p obj is hit.
bool isHit(Obj obj);
```

Do not repeat any documentation across header and implementation files, in
other words, documentation in implementation files is generally not required,
except for the [Declaration Comment](#declaration-comment) and for anything
which is defined locally. 

### Declaration Comment

Each source file should have a comment at the top of the file which includes
the path to the file, its name, and the language (C++). Files should also 
include the license reference, the name of the library the file is part of, 
Pixel Technology's name in the copyright section, and a location to where 
the full license can be found. Lastly, Doxygen comments for the file name 
(using the ```\file```command) and a more detailed description (using 
the ```\brief``` command) must be provided. Files without declaration comments
should not be accepted when submitted for code review. The declatation comment
for a FunctionTraits.hpp file in the root directory of the Meta Library looks 
as follows:

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

### Classes and Structs

Classes and structs promote good object oriented design. It is important that
their purpose is stated clearly. As such, include a comment block which
explains the purpose and usage of the class/struct. The first sentance
(interpreted as ```\brief```) should be brief, and give an introduction. Add 
any further description after a blank line. A class/struct comment looks as 
follows:

```cpp
/// The example class is a general base class for all examples within the 
/// Pixel libraries. 
///
/// It is used to define the interface which all examples must follow, making
/// the examples clear, consistent and easy to understand.
///
/// A more detailed description may follow, if appropriate.
class ExampleClass {};
```

### Methods

All class methods (both public and private) and global functions should also be
thoroughly documented using Doxygen comments. 

The pre and post conditions should be tested within the method, and should be
self documenting, thus do not require comments.

If there are any cases which may prove tricky for the function, then document 
these in the function description. Examples might be error checking, a specific
input causing undefined behaviour, or if no error handling is performed, 
specify why such a decision was made.

## Language and Compiler
-------------------------------------------------------------------------------

### Warnings

No Pixel code should have warnings (when using GCC, clang, or MSVC). If there
are warnings, then there are problems in the code which should be fixed. The
code causing the warnings should be fixed immediately.

To enable compiler warnings, code should be compiled with the following flags:

```cpp
// Clang/gcc:
-Wall -Wextra -Wglobal-constructors (clang/gcc)

// MSVC:
/Wall
```

### Exceptions and Errors

Exceptions and error handling can slow down code when such features are not a
necessity, however, can be extremely useful for debugging and producing code 
which does not break. Pixel code does not use any exception handling, but
rather defines its own error handling class, ```TypedError```.The class
ensures that all errors are checked and handled (in debug code, in release code
the overheads are removed).

On top of ```TypedError```, there is  the ```ErrorOr<T>``` class, which stores
either  a ```T``` or a ```TypedError```. The ```ErrorOr<T>``` class should be
used whenever a function can return an error which should be handled. The class
ensures that all errors are checked and handled (in debug code, in release code
the overheads are removed).

The following provides some example code of where ```ErrorOr<T>``` and
```TypedError``` might be used:

```cpp
class Socket {
 public:
  Socket(Endpoint endpoint) : Descriptor(-1) {}

  TypedError open() {
    Descriptor = getDescriptor(); // Returns ErrorOr<int>

    // If there is an error, we leave that to the caller to handle:
    if (!Descriptor)
      return Descriptor.takeError();
    // Socket is open.
  }
 private:
  ErrorOr<int> Descriptor;
};
```

### Casting

In C++ code, you should never use C-style casting, and only ```static_cast<>```
should really be used, except for in certain, rare, circumstances. As much as
possible, and unless there is a **very** good reason to do so, avoid
```dynamic_cast<>``` and ```const_cast<>``` in all cases. Obviously, in C code,
C-style casting is the only option and may be used, but the same principles 
apply.

### Function Pointers

C-style function pointers should not be used:

```cpp
void funcWithCallback(int paramOne, void (*callback)(int x));
```

They provide less opportunity for the compiler to perform optimization, and are 
less readable. Rather use a functor, and put the implementation of the functor 
in the header file of the module which uses it, or in its own file. For
example:

```cpp
// FileUsingFunctionWithCallback.hpp
    
template <typename Callable>
void funcWithCallback(int paramOne, Callable callback) {
  callback(paramOne);
}
```

Where the ```Callable``` type looks something like:

```cpp
struct ExampleFunctor {
  void operator()(int param) const {
    // Implementation ...
  }
};
```

### Classes vs Structs

The ```class``` and ```struct``` keywords should be used under the following
conditions: 

Use ```struct``` when all variables are public, or for a class which 
provides metaprogramming functionality, otherwise use ```class```.

### Auto Keyword

The ```auto``` keyword can make code much simpler and hence more readable in
certain situation. Use the ```auto``` keyword where ever you deem it to make 
the code more readable, and nowhere else. This is especially true for the case
that the type of the object is immediately obvious from the surrounding 
context. You may also use it **within** library implementations to simplify 
template code. 

**Note:** *Do not use auto to simplify template code if the code is part of a 
library's interface. It is okay to assume that other library developers 
understand C++ sufficiently to infer the type of heavily templated code from 
the surrounding context, and hence justifies the simplification ```auto``` 
provides. However, if the interface is available for anyone to use, the code 
should be explicit so that even beginner C++ developers can understand it.*

When using the ```auto``` keyword, be aware of the efficiency in specific
cases.

Make sure that when you do not need to copy, you specify ```const auto&``` 
or ```const auto*```. For example: 

```cpp
// When a copy is needed, use the simple form:
for (auto val : container) { 
  val.modify();
  doSomethingWithCopiedVal(val);
}

// When a copy is not required:
for (const auto& val : container) { dontWantToModify(val); }
for (auto& val : container      ) { wantToModify(val);     }

// When using pointers, make copying explicit:
for (const auto* val : container) { dontWantToModify(*val); }
for (auto* val : container      ) { val->wantToModify();    }
```

### Portability

It should be possible to write portable code in almost all cases. In some
special circumstances (for example where wrapping a system call which may not
have a similar operation on another platform), then the code should be hidden
behind an iterface which provides the similar functionality for the unsupported
platform.

If a compiler does not support some functionality, then there are two options:

  1. Write the code in the way in which the worst case compiler can support it.
  2. Provide a wrapper of some sort to mimic the functionality so that the
     supported compiler compiles with the most supported feature, while the
     unsupported compiler compiles with the mimiced functionality.

An example is when clang had support for some features of c++17, while other
compilers did not. We can then do something like:

```cpp
namespace std {
#if defined(PIXEL_GNUC) || defined(PIXEL_MSVC) 
  template <typename T, typename U>
  static constexpr bool is_same_v = is_same<T, U>::value;
#endif
} // namespace std
```

which can then be removed once it is supported by the other compilers.

### Do Not use Static Constructors

Static constructors and destructors should not be added to the code base
(except in very rare circumstances, like a singlton class for example). They
are global variables, and should be removed if they are seen without **very**
good reason. They also have the problem that the order of initialization
between global variables in different source files is undefined, which has the
potential for many headaches. They also have the following problems: [Static
Con/destructor problems](http://yosefk.com/c++fqa/ctors.html#fqa-10.12).

Also, since all the static constructors must be executed when the program is
started, they can cause long startup times, which is really undesirable.

## Code Style 
-------------------------------------------------------------------------------

### Early Exits and Minimal Nesting

Use early exits to terminate functions if preconditions are not met, as well as
to make long code executed by passing such conditions more clear. Often
multiple conditional checks in the same place require the reader to store a lot
of information in their head, and when the code inside the conditions is long 
and includes further conditions, storing this information is difficult. For
example, the following code:

```cpp
int functionWithMultipleConditions(Conditional& condition) {
  if (!isCondition1(condition) && condition.doesSomethingElse())
    // Long code based on conditions
  return 0;
}
```

Might be re-factored into the following:

```cpp
int functionWithMultipleConditions(conditional& condition) {
  if (isCondition1(condition))
    return 0;

  if (!condition.doesSomethingElse())
    return 0;

  // Long code ...
}
```

This is often the case with loops, and again code can be restructured to 
reduce nesting and remove the requirement for the reader to have to remember 
which conditions have passed or failed. This makes it easier to understand
**why** the current state is what it is. An example might be:

```cpp
for (const auto& element : elements) {
  if (auto subElement = element.getSubElement()) {
    auto left  = subElement.getLeftCondition();
    auto right = subElement.getRightCondition();

    if (left != right) {
      // ...
    }
  }
}
```

Which could be re-factored to become more clear:

```cpp
for (const auto& element : elements) {
  auto subElement = element.getSubElement();
  if (!subElement) continue;   // Go to next iteration

  auto left  = subElement.getLeftCondition();
  auto right = subElement.getRightCondition();
  if (left == right) continue;  // Go to next iteration

  // Reader doesn't need to remember what conditions have passed ...
}
```

Which reduces the nesting, and makes each of the checks significantly more
clear. Additionally, there are no ```else``` statements for which the reader
must remember what the corresponding ```if``` statement was.

### Predicate Loops

It is common to write a loop which does some computation to return a boolean
value. It is preferred that such loops are refactored into a function, which
can be ```static```, ```inline``` if small, or reside in a ```Detail::``` 
or ```anonymous``` namespace near it's use -- if the function is not reusable.

For example, this is not ideal:

```cpp
bool foundFoo = false;
for (size_t i = 0; i < someArray.size(); ++i) {
  if (someArray[i].isFoo()) {
    foundFoo = true;
    break;
  } 

  if (foundFoo) {
    // ...
  }
  // ...
} 
```

Which can rather be rewritten as a function to compute the predicate, something
like:

```cpp
/// Returns true if a foo element is found in
/// a some array, otherwise returns false.
static bool containsFoo(const std::array<SomeType, SomeSize>& someArray) {
  for (size_t i = 0; i < someArray.size(); ++i) {
    if (someArray[i].isFoo()) {
      return true;
      break;
    }
  }
}

if (containsFoo(someArray)) {
  // ... 
}
```

There are numerous benefits for doing things this way:

1. Indentation is reduced (in the resulting code which calls the predicate
   function), which is always ideal as it requires less context to be 
   remembered. 
2. It requires the function to be named, making its purpose clearer, and the 
   resulting code simpler to understand. Additionally, a comment must be 
   written for the function. While this may not be beneficial in this simple 
   example, if the computation is complex or unusual there is a huge benefit.
3. The purpose of the code can be understood from just the name of the 
   function, rather than having to discern the functionality from the inline
   implementation.

### Typedef vs Aliases

C++11 provided the alias feature as an alternative to typedefs. It is preferred
that alias's are used rather than typedefs as this encourages modern C++ and
the syntax is more clear. Additionally, where an alias is created for a 
specific template type which may have other similar alias's, then add a suffix
to the name which indicates the type (for example ```i``` for an ```int```,
```f```  for a ```float```, ```16f``` for a 16 element array of ```float's```
etc). 

Here is an example of the preferred use of alias's and typedefs:

This is preferred:

```cpp
using Vec3f = std::array<float, 3>;
using Vec3i = std::array<int, 3>;
```

Over this:

```cpp
typedef std::array<float, 3> Vec3f;
typedef std::array<int, 3>   Vec3i;
```

Do not be afraid to abuse the use of aliases within classes, especially in the
```private``` section. This is especially the case where implementation details
may change. For example, some class may use an array as the container of
elements, but later it may be reqired that the size be dynamic. Creating an
alias for the container allows this change to be made easily. For example:

```cpp
class SomeClass {
 private:
  //==--- Aliases ---------------------------------------------------------==//

  /// Defines the type of the contiguous container used to store elements.
  using ContiguousContainer = std::vector<SomeType>;


 public:
  // Public interface ...
  
 private:
  ContiguousContainer Elements; //!< Elements for x ...
};
```
### Assertations

Assert to check preconditions and assumptions. When the conditions can be
checked at compile time use ```static_assert```. This can often lead to finding
bugs that would otherwise not have been found, saving a lot of time when 
debugging.

The assert macro which should be used is the ```PixAssert``` macro in the
**TODO: Add link** Pulley library. The macro requires an error message to be
provided as the second parameter which will be printed when the assertation
fails. For example:

```cpp
#include <Pixel/Pulley/Error/Assert.h>

Element getElement(size_t i) {
  PixAssert(i < Elements.size(), "getElement() : Out of range access");
  return Elements[i];
}
```

Note that ```PixAssert``` will add the file and line number. All assertations
with ```PixAssert``` are removed when compiling in release mode ```-DNDEBUG```.

### Using namespace::std

Avoid ```using namespace std```, and prefer to use the prefix ```std::```.

Also, in header files, avoid the use of ```using namespace X```, and rather
use the prefix ```X::```, since the ```using``` directive pollutes the
namespace of any source file which includes the header.

In source files this is less of a concern, but should still be applied whenever
it is not inconvenient to do so, as it makes functions easy to find, and easily
identifiable. If multiple namespaces are chained, then define a shorter 
namespace to represent it. For example:

```cpp
// This is a case which can be simplified.
pixel::snap::math::sum(x, y);

// To this.
namespace math = pixel::snap::math;
math::sum(x, y);
```

### Using std::endl

The use of ```std::endl``` should be avoided, since it flushes the buffer,
which is often not required. Rather use ```\n```, and in the case that the
output stream must be flushed, then append ```std::flush```. For example:

```cpp
std::cout << std::endl;             // Avoid this.
std::cout << "\n";                  // In favour of this.
std::cout << "\n" << std::flush;    // Or this to flush the output stream.
```

### Container Iteration

When iterating over containers and performing some action with the iterator, 
it is preferred that ```std::for_each``` is used, and that the action to
perform on the iterator is provided as either a lambda function or as a
functor. For example:

```cpp
std::vector<int> elements{1, 2, 3, 4, 5};

// for_each example with lambda.
std::for_each(elements.begin(), elements.end(), [] (int& n) {
  n++;
});

// for_each example with a functor
struct Sum {
  Sum() : sum_(0) {}
  void operator()(int n) {
    sum += n;
  }
  int sum;
};

Sum s = std::for_each(elements.begin(), elements.end(), Sum());
```

However, if the iteration over the container must be written explicitly, then
pre-compute the end iterator so that a call to ```end()``` or ```size()``` is 
not computed for each iteration.

**NOTE:** This doesn't apply to the case where the container is modified by the
loop, in which case the pre-computation of ```end()``` or ```size()``` will
produce an incorrect result.

In the case that the container is modified, add a comment which says so, and
states why the container is modified. Here is an example:

```cpp
IterableArray* array = makeIterableArray();

// This is the case when the container is not modified:
for (auto it = array->begin(), end = array->end(); it != end; ++it) {
  // Do something with it
}

// This is the case when the container is modified (note comment):
// Modifies the array each time a bar element is found:
for (auto it = array->begin(); it != array->end(); ++it) {
  if (!it->isBar()) continue;

  // Modify array ...
}
```

This is done for the following reasons:

1. For complex types the call to ```end()``` can potentially be costly. While 
   this is not the case for a call to ```size()```, the same structure should 
   still be used so that the code has a consistent style. 
2. This makes it immediately clear whether or not the container is modified, 
   without even having to look at the implementation of the loop. This is 
   enforced by the requirement of writing a comment for loops which modify the
   container. 

### Inlining

For small functions (approx < 10 lines), the ```inline``` keyword may be used 
to hint to the compiler that it should inline the function. However, where a 
function is inlined implicitly, then avoid the use of the ```inline```
keyword. For example:

The inline keyword here is not implicit, so it may be used:

```cpp
inline bool isGreater(int a, int b) {
  return a > b;
}
```

However, the inline keyword here is implicit (method implementation is defined
inside the struct definition), so don't add it:

```cpp
struct Foo {
  // Implicit inline, so don't use the inline keyword
  void bar() {
    // Some short implementation ...
  }
};
```

### Use of Const

Make use of ```const``` **as often as possible**, since this allows the
compiler to more aggressively optimise, and makes code easier to reason about.
Mark  class methods ```const``` whenever they do not modify class variables.

### Use of Noexcept

Make use of ```noexcept``` wherever a function **will not** throw an exception. 
As with ```const```, this allows for some optimisation. Specifically, the
optimizer doesn't need to keep track of the runtime stack in an unwindable way,
and they don't need to ensure that objects are destructe in the inverse order
in which they were created. This makes life easier for the optimizer. 
Additionally, since Pixel has its own error handling suite, and use of 
exceptions are not allowed, many methods will be ```noexcept```.

Besides having potential optimization gains, ```noexcept``` can also make it
clear to anyone reading the code that the method does not throw an exception.

## Formatting
-------------------------------------------------------------------------------

### Spaces for Parenthesis

A space before an open parentheses is preferred for control-flow statements,
but not in function calls or macros. No space is preferred after open
parentheses and before closing parentheses, for all cases. For example:

The following examples are good:

```cpp
// Control flow statements:
if (A)                  // ...
for (i = 0; i < e; ++i) // ...
while (true)            //...

// Functions:
function(argument);
PIXEL_MACRO(A);
auto x = sum(4, 5) + divide(4, 2);
```

While the following examples are bad:

```cpp
// Control flow statements:
if(A)                   // ...
for(i = 0; i < e; ++i ) // ...
while( true )           // ...

// Functions:
function( argument );
function (argument);
PIXEL_MACRO ( A );
auto x = sum (4, 5) + divide( 4, 2 );
```

### Alignment of Variables

When declaring variables, always align them in columns, for example:

```cpp
int       intOne   , intTwo;
float     floatOne ;
OtherType otherType;
```
Some may say that this is irrelevant and a waste of time, but it makes the code
easier to read, and look nice, so follow the convention.