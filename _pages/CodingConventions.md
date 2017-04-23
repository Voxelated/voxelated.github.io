---
layout:     page
title:      Coding Conventions
permalink:  CodingConventions.html
author:     Rob Clucas
---

This page describes the coding conventions which are followed when implementing
the Voxel libraries. he conventions are designed to increase the readability of
the code base so that it's as realtively simple for anyone wanting to contribute
to get up to speed. This also makes the code easier to maintain. Most of the
conventions are a combination of those from other C++ code bases (LLVM,
Google, etc.) as well as general things which have been discovered as the
libraries were being developed. They will likely be imperfect, and should be
considered a work in progress, so feel free to make suggestions.

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

In general, all indentation is a **2 space** indent, as it allows more to fit
into the 80 column limit.

There are, however, occasions where the 2 space indent is **not** the correct 
indentation. These cases are documented throughout the remainder of these 
conventions. When these cases appear, then follow what is stated in those more
specific instances.

## Files
-------------------------------------------------------------------------------

### File Naming

All files should be named using CamelCase, and should be named with the class
they define, or if they're more general than that, then they should be named
with the functionality that they provide.

For template files, if there is specific implementation details which are
hidden in a ```Detail::``` namespace, then move the implementation to a file
with the same name with an **Impl.hpp** suffix, and preferably in a
**Detail/** subdirectory within the parent directory which defines the
interface.

The following are examples of some file names:
~~~cpp
FunctionTraits.hpp              // Name of a class file.
Detail/FunctionTraitsImpl.hpp   // Name of a detail file.
~~~

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

### Header Guards

Rather than using header guards, use ```#pragma once``` is this is far simpler,
and results in cleaner looking header files. All header files (```.h``` and
```.hpp```) should use ```#pragma once```, which should directly follow the file
comment (see [Header Files](#header-files)).

### Including

The ```#include``` keyword for including header files should directly follow 
the ```#pragma once``` directive, separated by a space. Include header files
minimally, and where possible, prefer to forward declare. Header files should be
included in the following order:

  1. Headers local to the library/application
  2. Headers for other Voxel libraries used in the library/application
  3. Headers from the C++ standard library
  4. Any other headers

### Comments

Comments are extremely important for making code simpler to understand, most
especially in sections which introduce complexity in exchange for increased
performance, and in complex template metaprogramming code.

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

Prefer to describe the return parameters in the description of the function as
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
Voxel's name in the copyright section, and a location to where 
the full license can be found. Lastly, Doxygen comments for the file name 
(using the ```\file``` command) and a more detailed description (using 
the ```\brief``` command) must be provided. The declatation comment
for a FunctionTraits.hpp file in the Functional directory of the Voxel main
Library would look as follows:

```cpp
//==--- Voxel/Functional/FunctionTraits.hpp ----------------- -*- C++ -* ---==//
//            
//                                  Voxel
//
//                      Copyright (c) 2017 Author Name.
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
/// Voxel libraries.
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

No code should have warnings (when using GCC, clang, or MSVC). If there
are warnings, then there are problems in the code which should be fixed. The
code causing the warnings should be fixed immediately. There are some
exceptions, however.

Sometimes one might want to used taged dispatch to select between
implementations at compile time. For example:

```cpp
struct Example {
 private:
  // Struct which can be used to select the appropriate implementation.
  template <std::size_t Dimensions> struct DimDispatch {};
 
 public:
  // Interface:
  auto someImplementation(const MultiDimObject& object) const {
    constexpr auto dims = ObjectTraits<MultiDimObject>::Dimensions;
    return multiDimImpl(object, DimDispatch<dims>{});
  }

 private:
  // 1D implementation:
  auto multiDimImpl(const MultiDimObject& object, DimDispatch<1> tag) const {
    // ...
  }
  // 2D implementation:
  auto multiDimImpl(const MultiDimObject& object, DimDispatch<2> tag) const {
    // ...
  }
};
```

will result in unused parameter warnings for the implementation functions. This
is acceptable. However, for this specific case, the unused parameter should be
acknowledged by naming it appropriately, such as ```tag``` or ```selector``` in
the above example.

This can be avoided in c++17 by using ```if constexpr()```, however, when there
are numerous dispatch options, the above pattern results in clearer code.
Another alternative is to write a separate dispatch class template, templated on
the paramter which selects the appropriate dispatch, and then to specialize the
class tempalte. This is a good choice if the implementation functions do not
require access to the internals of the class doing the dispatching, however, if
they do then the dispatch class must be a friend of the class implementing the
interface, and it is then preferable to have the warning.

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
which does not break. The Voxel library code uses exceptions where appropriate,
since they are essentially zero cost in the non-exception case.

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

Lambda functions are another option which are often a lot simpler, and result in
very good performance, especially if they are stateless.

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
behind an interface which provides the similar functionality for the unsupported
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
#if defined(VoxxGnuc) || defined(VoxxMsvc) 
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
checked at compile time use ```static_assert``` -- use this very liberally! This
can often lead to finding bugs that would otherwise not have been found, saving 
a lot of time when debugging.

The assert macro which should be used is the ```VoxxAssert(condition, message```
macro in the [Voxel](https://github.com/Voxelated/Voxel) library. The macro
requires an error message to be provided as the second parameter which will be
printed when the assertation fails. For example:

```cpp
#include <Voxel/Utility/Debug/Assert.h>

Element getElement(size_t i) {
  VoxxAssert(i < Elements.size(), "getElement() : Out of range access");
  return Elements[i];
}
```

Note that ```VoxxAssert``` will add the file and line number. All assertations
with ```VoxxAssert``` are removed when compiling in release mode,
i.e when the ```-DNDEBUG``` flag is passed.

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
Voxx::Compute::Math::sum(x, y);

// To this.
namespace Math = Voxx::Compute::Math;
Math::sum(x, y);
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

Most of the Voxel containers provide their own implementations of
```forEach()```, which can be used instead of iteration. Additionally, the main
[Voxel](ttps://github.com/Voxelated/Voxel) library provides an implementation of
```forEach()``` for ```std::tuple```, which is useful.

### Inlining

For small functions (approx < 10 lines), the ```inline``` keyword may be used 
to __hint__ to the compiler that it should inline the function. However, where
a function is inlined implicitly, then avoid the use of the ```inline```
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
and they don't need to ensure that objects are destructein the inverse order
in which they were created. This makes life easier for the optimizer.

Besides having potential optimization gains, ```noexcept``` can also make it
clear to anyone reading the code that the method does not throw an exception.

### Final and Override

Use the ```override``` keyword for any derived class implementations of the same
base class functions. Additionally, if it is known that the derived
implementation will not be overriden, mark it as ```final```.

```cpp
struct Base {
  virtual void someFunc() {
    // Default impl ...
  }
};

struct Derived : public Base {
  virtual void simFunc() final override {
    // Overriden final implementation ...
  }
};
```

### Forwarding (Universal) and Rvalue-References

Forwarding references (termed [Universal references]
(https://isocpp.org/blog/2012/11/universal-references-in-c11-scott-meyers)) are
(from [temp.deduct](http://eel.is/c++draft/temp.deduct#call-3)) :

> A forwarding reference is an rvalue reference to a cv-unqualified template parameter. If P is a forwarding reference and the argument is an lvalue, the type “lvalue reference to A” is used in place of A for type deduction.

i.e:

```cpp
// Here T&& is a forwarding reference, and can either be lvalue reference
// or rvalue reference
template <typename T>
void func(T&& param);
```
where:
```cpp
int x = 10;
func(x);    // x is lvalue
func(10);   // 10 is rvalue
```

for functions which take a forwarding reference, the parameter(s) should always
be forwarded with ```std::forward```, unless the parameter is used multiple
times, since ```std::forward``` may consume the parameter if it is deduced to be
an rvalue reference. For example:

```cpp
// Example for forwarding reference used once:
template <typename T>
void interface(T&& param) {
  implementation(std::forward<T>(param));
}

// Example of forwarding reference used multiple times:
template <typename T>
void interface(T&& param) {
  firstUse(param);
  finalUseWhichMayConsume(std::forward<T>(param));
}
```


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
VoxxMacro(A);
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
VoxxMacro ( A );
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

### Classes and Structs

For classes and structs, the **opening brace** should be on the **same line** 
as the class declaration, and the closing brace should be on its own line.

The ```public```, ```protected``` and ```private``` keywords should be 
indented **one space**. Everything else should be indented **two spaces**, and 
variables and aliases should be **aligned in** columns.

The order of declarations should be as follows:

- List of friend classes
- Public aliases
- Public variables
- Public methods
- Protected aliases 
- Protected variables
- Protected methods
- Private aliases
- Private variables
- Private methods

This allows the public interface to easily be found at the beginning of the
class. Each of the sections within the access specifier should be separated by 
a space (for example there should be a space between the end of the public 
aliases and the public variables, etc...).

The following is an example of a correctly formatted class (including correct 
commenting):

```cpp
/// Example class illustrating correct class formatting.
class ExampleFormatting {
 public:
  friend class Formatter;

  /// Alias for formatting type.
  using formattingType = SomeFormat;
  /// Alias for some other type.
  using someOtherType  = SomeType;

  int    numFormats;        //!< Number of formats.
  float  formatPrecision;   //!< Precision of a format.

  /// Default constructor: Does nothing.
  ExampleFormatting() {};

 protected:
  // ...

 private:
  /// Internal alias for format storage.
  using FormatVector = std::vector<Format>;

  FormatVector  Formats;    //!< Storage of the formats.
  bool          MustFormat; //!< If some formatting must be done.

  /// Checks if a format is valid.
  /// \param[in] index The index of the format to check the validity of.
  bool isValidFormat(size_t index) const;
};
```

For constructors, the initialization of member variables should be on the same
line as the constructor declaration, if they can fit, otherwise they should
start on the next line, without indentation. If they cannot all fit on the
following line, then they should each be on a separate line with a 4 space
indent, and all comma's should be in the same column. For example:

```cpp
class ExampleClass {
 public:
  // Initialization can fit on the same line:
  ExampleClass(int a, int b) : TotalCount(a), SubCount(b) {}

  // Initialization will fit on a single new line for this:
  ExampleClass(SomeComplexType s, SomeOtherComplexType sc, int a);

  // Initialization will not fit on a single new line for this:
  ExampleClass(SomeComplexType      s  ,
              SomeOtherComplextType sc , 
              AnotherType           at ,
              YetAnotherType        yat,
              int                   a  );

 private:
  SomeComplextType      ComplexTypeA;
  SomeOtherComplexType  ComplexTypeB;
  AnotherType           TypeC;
  YetAnotherType        TypeD;
  int                   TotalCount;
  int                   SubCount;
};

ExampleClass::ExampleClass(SomeComplexType      s ,
                           SomeOtherComplexType sc,
                           int                  a )
: ComplexTypeA(s), ComplexTypeB(sc), TotalCount(a), SubCount(0) {
  // Rest of implementation ...
}

ExampleClass::ExampleClass(SomeComplexType       s  ,
                           SomeOtherComplextType sc , 
                           AnotherType           at ,
                           YetAnotherType        yat,
                           int                   a  )
:   ComplexTypeA(s) ,
    ComplexTypeB(sc),
    TypeC(at)       , 
    TypeD(yat)      , 
    TotalCount(a)   ,
    SubCount(0)     {
}
```

### Lambda Expressions

For lambda expression, the opening brace should be on the same line as the
lambda, the closing bracket should be on its own line, followed by the
closing ```)``` bracket (if appropriate) and the semi-colon. The body of the 
lambda should be indented **2** spaces further than the line above which 
declares the lambda. For example:

```cpp
for_each(someVector.begin(), someVector.end(), [] (int& n) {
  n++;      // Two space indent, from line above.
});         // Closing brace and bracket on the same line.
```

This reduces vertical space and allows more code to fit into a single screen,
allowing whomever is reading the code to gain more context.

In the case where the captures and arguments for the lambda roll over to a new 
line (past the 80 character limit), place the captures and parameters on a new
line with a __2__ space indent, and then indent the body a further __2__ spaces.
Use discretion to make the code as readable as possible. For example, this is one option:

```cpp
std::for_each(someVector.begin(), someVector.end(),
  [&someVariable] (int& n) {
    n++;                       // Further two space indent.
  }                            // Closing brace lined up with capture start.
);                             // Closing brace lined up with function start.
```

When there are multiple successive lambda functions, start each one on a new 
line, with the ```[]``` indented two spaces further than the previous
indentation, and the body of the lambda indented two spaces from the ```[]```. 
Line up the ```[]``` brackets from each lambda. 

If the lambdas are surrounded by opening and closing round brackets (as in the 
case of a function which takes multiple lambdas), then place the 
closing ```)``` bracket and the semi-colon which follows on their own line. For 
example:

```cpp
void someFunctionWithMultpleLambdas(
  [] (int& n) {               // Indented 2 spaces from previous indentation.
    n++;                      // Further two space indent.
  }, 
  [captureVariable] () {      // Lines up with previous lambda's capture.
    // Do something ...
  }
);                            // Placed on own line.
```

### Namespaces

Each namespace should be declared on it's own line, with an opening brace on
the same line, and should use CamelCase, starting with an uppercase letter.
The opening braces of namespaces should line up, and the end of the namespace
should have a closing brace on its own line and a comment
```// namespace <namespace_name>``` to indicate the end of the namespace. This
makes it easy to search for the end of a namespace using its name, for files
which have multiple namespaces. The body of the namespace should not be
indented. For example:

This is a general namespace example:

```cpp
namespace Example {
class Foo {
  // Foo details ...
};
}  // namespace Example
```

#### Anonymous and Detail Namespaces

Anonymous namespaces are a great feature of C++ as they let the compiler know
that the contents of the anonymous namespace are only visible to the current
translational unit, which allows the compiler to perform more aggressive
optimization. These are essentially the same as ```static``` functions in C. 
In C++, however, anonymous namespaces are more general than ```static``` 
since they can make an entire class private to a translational unit, which
should be their primary use.

When using anonymous namespaces, make them as small as possible, and use them
for class declarations only (not functions). For example:

This is good:

```cpp
namespace {

struct Comparator {
  Comparator();
  bool operator()(int a, int b) const;
};

}  // namespace anon

static void otherFunction() {
  // ...
}

bool Comparator::operator()(int a, int b) const {
  return a < b;
}
```

While this is bad:

```cpp
namespace {

struct Comparator {
  Comparator();
  bool operator()(int a, int b) const;
}

void otherFunction() {
  // ...
}

bool Comparator::operator()(int a, int b) const {
  return a < b;
}

} // namespace anon
```

There is no need for ```operator()``` to be included in the anonymous 
namespace. For ```someFunction()``` it is difficult to tell that it is local 
to the file in the case that it is in the anonymous namespace.

Functions and variables should rather be part of a ```Detail``` namespace
and/or use the ```static``` keyword, if they are intended to be used only in 
the surrounding context. For example:

```cpp
namespace Detail {

static int  objectCount = 4;
static void someFunction() {
  // ...
}

void someOtherFunction() {
  // ...
}

}  // namespace Detail
```

### Pointers and References

For pointers are references, attach the ```*``` or ```&``` operators to the
type rather than to the name. Additionally, the use of ```const``` for 
pointers and ints is shown below:

The following is good convention for pointers:

```cpp
// Good for pointers:
int*              p;      // Non-const pointer to non-const int.
int* const        p;      // Const pointer to a non-const int.
const int*        p;      // Non-const pointer to const int.
const int* const  p;      // Const pointer to const int.
```

While the following is bad for pointers:

```cpp
int const*        p;
int              *p;
int * const       p;
const int        *p;
const int * const p;
```

The following is good for references:

```cpp
int&              r;      // Non-const int reference.
const int&        r;      // Const int reference.
```

While the following is bad for references:

```cpp
int              &r;
const int        &r;
int const&        r;
int const        &r;
```

## Naming
--------------------------------------------------------------------------------

Naming is important as poor naming can cause confusion when trying to
understand how code works, and can therefore lead to bugs. Names should be
descriptive, allowing the reader to understand the usage and intention of
a variable or type from it's name. Avoid abbreviations where possible, and
conform to the capitalization conventions, as they are designed to allow for 
immediate identification of types, variables, functions, access scope, etc..., without having to actually search for that information.

### Type Names

Type names, such as classes, structs, typedefs, alias's, and type template
parameters, should be nouns, use CamelCase, and start with a capital letter. 
Enums have additional rules -- see [Enums](#enums).

The following are examples:

```cpp
// Classes an structs:
class  ErrorHandler {};
struct FileProperties {}:

// Typedefs (for the odd case that they are used):
typedef std::array<float, 3> Vec3f;

// Aliases:
using FloatArray = std::array<float>;

// Template type parameter:
template <typename AllocatorType>
class SmallVector {
  // ...
};
```

### Enums

Enum declarations are types, so they should follow the formatting of type names
by using CamelCase. The contents of the enum should also use CamelCase,
starting with a capital letter. 

Preferably enums should be scoped, however, sometimes the intent is to use the
numeric value of the enum, in which case it is simpler, and clearer, to not have
to ```static_cast<>``` the scoped enum to the appropriate numeric type. In this
case, it's okay to use a non-scoped enum, but when using the enum values they
should be treated as if they are scoped, and should be accessed though the enum
name with the scope resolution operator ```::```. For example:

```cpp
// An enum for which the numeric value is required:
enum PropertyKind : uint8_t {
  SomeProp      = 0, 
  SomeOtherProp = 1
};

// PropertyKind:: is not required, but should be used,
// and has type uint8_t here:
PropertyKind::SomeProp;
```

A scoped enum is similar, but has the type of the enum (this should be used
wherever possible):

```cpp
// A scoped enum:
enum class PropertyKind : uint8_t {
  SomeProp      = 0, 
  SomeOtherProp = 1
};

// PropertyKind:: is required, and has type PropertyKind:
PropertyKind::SomeProp;
```

### Variables

Variables should be nouns, and the name should be written using CamelCase,
starting with a lowercase letter. Private member variables, however, should
begin with an uppercase letter. For example:

This is a local variable naming example:

```cpp
int someInt = 4;
```

This is a class naming example:

```cpp
class NamingExample {
 public:
  // Public member variable:
  int someInt;

  // Constant expression:
  static constexpr auto someVar = someValue;

  // Function arguments:
  NamingExample(int someOtherInt)
  : someInt(0), SomeOtherInt(someOtherInt) {}

 private:
  // Private member variable:
  int SomeOtherInt;
};
```

This is a struct naming example:

```cpp
struct Params {
  // Public variables as above for classes:
  bool    firstFlag;
  size_t  maxRecursiveCalls;

 private:
  // Private variables also as above:
  bool AnotherFlag;
};
```

### Functions 

Function names should be verbs, and use CamelCase, with the first word starting
with a lowercase letter -- just like public and local variables. The reason for
using the same convention for public and local variables, and functions, is 
that function calls are easily identifiable from the fact that they need 
arguments (or empty brackets). Using the same style makes the code look better
without making it less readable. 

The following is a function naming example:

```cpp
void        containsFoo();
FileHandle  openFile():
```

When the arguments of a function will exceed the 80 character limit, then begin
each new line of function arguments with:

1.  - A hanging indent if the longest parameter will fit in the 80 columns
    - A __2 (definition) or 4 (implementation)__ space indent if all parameters
      will fit into a single line
2.  - A __2__ space hanging indent on the next line if the function is a
      definition
    - A __4__ space hanging indent on the next line if the function has an
      implementation

If the return type of the function is long, for example has 
```constexpr inline someLongType``` then the entire return type can be placed on
its own line before the function name, which will allow function signatures
which fall into 2 above, to be formatted as 1 above. This is common when a
function signature is prefixed with a macro. Examples are shown below.

Additionally, add the ```constexpr``` specifier whenever a function can be
computed at compile-time. In the worst case, the compiler will warn you that
the constexpr function never produces a constant expression.

The following are examples:

__First Option : (Preferred):__

Here the longest parameter will fit into 80 columns, so a hanging indent should
be used:

```cpp
// Hanging indent - definition:
int aFunctionWithManyLongArguments(ArgumentTypeOne   argOne  ,
                                   ArgumentTypeTwo   argTwo  ,
                                   ArgumentTypeThree argThree);

// Hanging indent - implemetation:
int aFunctionWithManyLongArguments(ArgumentTypeOne   argOne  ,
                                   ArgumentTypeTwo   argTwo  ,
                                   ArgumentTypeThree argThree) {
 // Implementation ...
}
```

Alternatively, since all parameters can fit on a single line, this is also an
option:

```cpp
// All parameters fit on one line (defintion : 2 space indent):
constexpr inline auto aFunctionWithManyLongArguments(
  ArgumentTypeOne argOne, ArgumentTypeTwo argTwo, ArgumentTypeThree argThree);

// All parameters fit on one line (implementation : 4 space indent):
constexpr inline auto aFunctionWithManyLongArguments(
    ArgumentTypeOne argOne, ArgumentTypeTwo argTwo, ArgumentTypeThree argThree) {
  // Implementation ...
}
```

__Second Option: (Last Resort):__

All parameters will not fit on a single line, and a hanging indent is not
possible:

```cpp
// Definition (2 space indent):
constexpr inline auto aFunctionWithManyLongArguments(
  ArgumentTypeOne   argOne  ,
  ArgumentTypeTwo   argTwo  ,
  ArgumentTypeThree argThree,
  ArgumentTypeFour  argFour ) noexcept;

// Implementation (4 space indent):
constexpr inline auto aFunctionWithManyLongArguments(
    ArgumentTypeOne   argOne  ,
    ArgumentTypeTwo   argTwo  ,
    ArgumentTypeThree argThree,
    ArgumentTypeFour  argFour ) noexcept;  
```

The above example can specify the return type on its own line, allowing the
paramters to be formatted with a hanging indent:

```cpp
// Definition:
constexpr inline auto 
aFunctionWithManyLongArguments(ArgumentTypeOne   argOne  ,
                               ArgumentTypeTwo   argTwo  ,
                               ArgumentTypeThree argThree,
                               ArgumentTypeFour  argFour ) noexcept;

// Implementation:
constexpr inline auto 
aFunctionWithManyLongArguments(ArgumentTypeOne   argOne  ,
                               ArgumentTypeTwo   argTwo  ,
                               ArgumentTypeThree argThree,
                               ArgumentTypeFour  argFour ) noexcept {
  // Implementation ...
}
```














































































