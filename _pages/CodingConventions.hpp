/*!
 
@page pix-cc Coding Conventions

@tableofcontents

@section pix-cc-intro Introduction

===============================================================================
This page describes the coding conventions for Pixel's software. The conventions
particularly important for a large project. The conventions are designed to
increase the readability of the code base, as well as make it easier to
maintain. They will likely be imperfect, so feel free to make suggestions.

In general, the preference is to produce clean, modern, and efficient C++ code. 
When the choice must be made between performance and clarity, the preference is 
**generally** clarity. However, if performance is critical, then sacrificing 
clarity is acceptable, so long as there is a **detailed** comment accompanying 
the specific section of code, which explains the code, and the reason for the 
performance being critically important.
 
@section pix-cc-form Code Structure

===============================================================================

@subsection pix-cc-struct-width Code Width 

-------------------------------------------------------------------------------
To allow code to remain well formatted in most editors and terminals without
resizing, lines should be at most 80 columns wide. It's suggested that the 81st
column is coloured to ensure the 80 column limit is followed.

@subsection pix-cc-struc-tabs Use of Spaces and Tabs

-------------------------------------------------------------------------------
Spaces must always be used over tabs. This is so that there is consistency
across all development environments. If the preferred development environment
allows it, configure it to replace all tabs with spaces.

In general, all indentation is a **2 space** indent. This allows more to fit
into the 80 column limit, and also only requires a single additional keyboard
press compared to using a tab.

There are occasions where the 2 space indent is not the correct indentation.
These cases are documented throughout the remainder of these conventions. When
these cases appear, then follow what is stated in those more specific
instances.

@section pix-cc-files Files

===============================================================================

@subsection pix-cc-files-nameinc File Naming and Including

-------------------------------------------------------------------------------
All files should be named using CamelCase, and should be named with the class
they define, or if they're more general than that, then they should be named
with the functionality that they define.

For template files, if there is specific implementation details which are
hidden in a ```detail``` namespace, then move the implementation to a file
with the same name with a **Detail** suffix, in a **Detail** folder.

The following are examples of some file names:
@code{.cpp}
  FunctionTraits.hpp                // Name of a class file.
  Detail/FunctionTraitsDetail.hpp   // Name of a detail file.
@endcode

Files should have the following extensions:

| File Extension | Use                                     |
| :------------- | :-------------------------------------- |
| h              | For a header without any implementation |
| hpp            | For a header with implementation        |
| cpp            | For implementation files                |
| cl             | OpenCL kernels                          |
| cu             | Cuda related code and kernels           |

The ```#include``` keyword to include header files should directly follow the 
file comment. Include header files minimally, and where possible, prefer to 
forward declare. Header files should be included in the following order:

* Headers local to the Pixel library
* Headers local to Pixel
* Headers from the C++ standard libraries
* Any other headers


@subsection pix-cc-files-define The Define Guard

-------------------------------------------------------------------------------
All header files (```.h``` and ```.hpp```) should use ```#define``` guards.
The guard should have the name  **Pixel** , followed by the library name,
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

@section pix-cc-comm Comments

===============================================================================

@subsection pix-cc-form-comm-gen General

-------------------------------------------------------------------------------
Comments are extremely important for making code simpler to understand, most
especially in sections which introduce complexity in exchange for increased
performance, and in templated code -- which will likely be extensive within 
Pixel since many of the libraries use expression templates and aim for optimal
performance.

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

Comments which span two lines should be formatted such that each line of
the comment has approximately the same width. For example:

@code{.cpp}
  // This is an example of a badly formatted comment because the length of
  // the lines differ.
@endcode

is a bad comment, and should rather be written as:

@code{.cpp}
  // This is an example of a well formatted comment because the
  // lines have the same length, improving the look of the code.
@endcode

which is better, because it looks cleaner.

When comments span more than two lines, then all lines but the last should use
the full 80 columns available.

@subsection pix-cc-comm-headers Header Files

-------------------------------------------------------------------------------
Each source file should have a comment at the top of the file which includes
the path to the file, its name, and the language (C++). Files should also 
include the license reference, the name of the library the file is part of, 
Pixel Software's name in the copyright section, and a location to where 
the full license can be found. Lastly, Doxygen comments for the file name 
(using the ```file```command) and a more detailed description (using 
the ```brief``` command) must be provided. Files without headers should not be 
accepted. The file comment for a FunctionTraits.hpp file in the root directory
of the Meta Library looks as follows:

@code{.cpp}
  // ---- Pixel/Meta/FunctionTraits.hpp ------------------- -*- C++ -*- ---- //
  //            
  //  Pixel : Meta Library
  //
  //  Copyright 2016 Pixel Software
  //
  //  Licensed under the Apache License, Version 2.0 (the "License");
  //  you may not use this file except in compliance with the License.
  //  You may obtain a copy of the License at
  //
  //    http://www.apache.org/licenses/LICENSE-2.0
  //
  //  Unless required by applicable law or agreed to in writing, software
  //  distributed under the License is distributed on an "AS IS" BASIS,
  //  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  //  See the License for the specific language governing permissions and
  //  limitations under the License.     
  //
  // ======================================================================= //
  //
  /// \file  FunctionTraits.hpp
  /// \brief Defines utility functions for detecting traits of functions.
  //
  // ----------------------------------------------------------------------- //
@endcode

@note The text for the license should be indented such that it lines up with 
the start of the path in the first line. 

@subsection pix-cc-comm-class Classes and Structs

-------------------------------------------------------------------------------
Classes and structs promote good object oriented design. It is important that
their purpose is clearly stated. As such, include a comment block which
explains the purpose and usage of the class/struct. An class/struct comment
looks as follows:

@code{.cpp}
  /// The example class is a general base class for all examples within the 
  /// Pixel libraries. It is used to define the interface which all examples 
  /// must follow, making all examples consistent and easy to understand.
  ///
  /// A more detailed description may follow, if appropriate.
@endcode

@subsection pix-cc-comm-method Methods

-------------------------------------------------------------------------------
All class methods (both public and private) and global functions should be 
thoroughly documented using Doxygen comments. 

The pre and post conditions should be tested within the method, and should be
self documenting, thus do nor require comments.

If there are any cases which may prove tricky for the function, then document 
these in the function description. Examples might be error checking, a specific
input causing undefined behaviour, or if no error handling is performed, 
specify why the decision was made.


@section pix-cc-lcomp Language and Compiler

===============================================================================

@subsection pix-cc-lcomp-warn Warnings

-------------------------------------------------------------------------------
No Pixel code should have warnings (when using GCC, clang, or MSVC). If there
are warnings, then there are problems in the code which should be fixed. The
code causing the warnings should be fixed immediately.

To enable compiler warnings, code should be compiled with the following flags:

@code{.cpp}
-Wall (clang/gcc)
/Wall (MSVC)
@endcode

@subsection pix-cc-lcomp-excep Exceptions and Errors

-------------------------------------------------------------------------------
Exceptions and error handling can slow down code when such features are not a
necessity, however, can be extremely useful for debugging and producing code 
which does not break. Pixel code does not use any exception handling, but
rather uses policies (see [Design Patterns: Policies](@ref pix-dp-policies)) to
add compile-time configurable error handling to classes at varying levels. This
allows non-critical error handling to easily switched off for production code,
critical error handling to remain in all versions, and various levels of error
handling functionality to be enabled while debugging.

Let's consider some examples. First, consider a socket which will has an open
method:

@code{.cpp}
class Socket {
 public:
  Socket(Endpoint endpoint) : Descriptor(-1) {}

  void open() {
    Descriptor = // Call which creates descriptor, or returns error.
    if (!Descriptor) {
      // Error is critical, user should know that a connection cannot be
      // established.
      printErrorMessage();
    }
    // Socket is open.
  }
 private:
  int Descriptor;
};
@endcode

Next, consider a custom array class and it's access method, which we want to
range check. We don't want to create range checkable at() methods, because that
would result in production code range checking each access, which we don't
want:

@code{.cpp}
template <typename Type, size_t Size>
class BetterArray {
 public:
  Type operator[](size_t index) const {
    if (index >= Size) {
      // Handle error appropriately
    }
    // Could also be assert(index < Size);
    return Data[index];
  }
 private:
  Type[Size] Data;
};
@endcode

In the two examples above, the errors have different significance to us. Let's
say that the socket's error is "critical" because our application relies on an
internet connection. However, the performance degradation of range checking on
each array access is just too great, and we want to disable it in production
code. We use an error handling policy for each of the classes:

@code{.cpp}
template <typename ErrorPolicy = CriticalErrorPolicy>
class Socket {
 public:
  Socket(Endpoint endpoint) : Descriptor(-1) {}

  void open() {
    Descriptor = // Call which creates descriptor, or returns error.
    ErrorPolicy::handle([] {
      if (!Descriptor) {
        // Error is critical, user should know that a connection cannot be
        // established.
        printErrorMessage();
      }
      // Socket is open.
   });
  }
 private:
  int Descriptor;
};
@endcode

Where the ``CriticalErrorPolicy`` always invokes it's lambda function.

@code{.cpp}
template <typename Type, size_t Size, typename ErrorPolicy = NonCriticalPolicy>
class BetterArray {
 public:
  Type operator[](size_t index) const {
    ErrorPolicy::handle([]
      if (index >= Size) {
        // Handle error appropriately
      }
    });
    // Could also be assert(index < Size);
    return Data[index];
  }
 private:
  Type[Size] Data;
};
@endcode

The critical policy may be defined as:

@code{.cpp}
struct NonCriticalPolicy {
  template <typename Functor>
  static inline void handle(Functor f) {};
};
@endcode

Which will allow the error handling code to be removed at compile time.
However, when we are doing debugging, we can change the policy which will
enable the bounds checking. The mechanism has the added advantage that the
lambda function is modern C++, which looks the same as the surrounding code.

@subsection pix-cc-lcomp-cast Casting

-------------------------------------------------------------------------------
In C++ code, you should never using C-style casting, and 
only  ```static_cast<>``` should really be used, except for in certain 
circumstances. As much as possible, and unless there is a **very** good reason 
to do so, avoid ```dynamic_cast<>``` and ```const_cast<>```. Obviously, in 
C code, C-style casting is the only option and may be used, but the same 
principles apply.

@subsection pix-cc-lcomp-fcall Function Pointers 

-------------------------------------------------------------------------------
C-style function pointers should not be used:

@code{.cpp}
  void funcWithCallback(int paramOne, void (*callback)(int x));
@endcode

They provide less opportunity for the compiler to perform optimisation, and are 
less readable. Rather use a functor, and put the implementation of the functor 
in the header file of the module which uses it, or in its own file. For example:

@code{.cpp}
  // FileUsingFunctionWithCallback.hpp
    
  template <typename Callable>
  void funcWithCallback(int paramOne, Callable callback) {
    callback(paramOne);
  }
@endcode

@subsection pix-cc-lcomp-cstruct Class and Struct Keywords

-------------------------------------------------------------------------------
The ```class``` and ```struct``` keywords should be used for the following
conditions: 

Use ```struct``` when all variables are public, or for for a class which 
provides metaprogramming functionality, otherwise use ```class```.

@subsection pix-cc-lcomp-auto Auto Keyword

-------------------------------------------------------------------------------
The ```auto``` keyword can make code much simpler and hence more readable in
certain situation. Use the ```auto``` keyword where ever you deem it to make 
the code more readable, and nowhere else. This is especially true for the case
that the type of the object is immediately obvious from the surrounding 
context. You may also use it *within* library implementations to simplify 
template code. 

@note Do not use auto to simplify template code if the code is part of a 
library's interface. It is okay to assume that other library developers 
understand C++ sufficiently to infer the type of heavily templated code from 
the surrounding context, and hence justifies the simplification ```auto``` 
provides. However, if the interface is available for anyone to use, the code 
should be explicit so that even beginner C++ developers can understand it.

When using the ```auto``` keyword, be aware of the efficiency in specific
cases.

Make sure that when you do not need to copy, you specify ```const auto&``` 
or ```const auto*```. For example: 

@code{.cpp}
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
@endcode

@section pix-cc-style Code Style 

===============================================================================

@subsection pix-cc-style-earlyx Early Exits and Minimal Nesting

-------------------------------------------------------------------------------
Use early exits to terminate functions if preconditions are not met, as well as
to make long code executed by passing such conditions more clear. Often
multiple conditional checks in the same place require the reader to store a lot
of information, and when the code inside the conditions is long and includes
further conditions, storing this information is difficult. For example, the 
following code:

@code{.cpp}
  int functionWithMultipleConditions(Conditional& condition) {
    if (!isCondition1(condition) && condition.doesSomethingElse()) {
      // Long code based on conditions
    }
    return 0;
  }
@endcode

Might be re-factored into the following:

@code{.cpp}
  int functionWithMultipleConditions(conditional& condition) {
    if (isCondition1(condition)) {
      return 0;
    }

    if (!condition.doesSomethingElse()) {
      return 0;
    }

    // Long code ...
  }
@endcode

This is often the case with loops, and again code can be restructured to 
reduce nesting and remove the requirement of the reader to have to remember 
which conditions have passed or failed. This makes it easier to 
understand *why* the current state is what it is. An example might be:

@code{.cpp}
  for (const auto& element : elements) {
    if (auto subElement = element.getSubElement()) {
      auto left  = subElement.getLeftCondition();
      auto right = subElement.getRightCondition();

      if (left != right) {
        // ...
      }
    }
  }
@endcode

Which could be re-factored to become more clear:

@code{.cpp}
  for (const auto& element : elements) {
    auto subElement = element.getSubElement();
    if (!subElement) continue;   // Go to next iteration

    auto left  = subElement.getLeftCondition();
    auto right = subElement.getRightCondition();
    if (left == right) continue;  // Go to next iteration

    // Reader doesn't need to remember what conditions have passed ...
  }
@endcode

Which reduces the nesting, and makes each of the checks significantly more
clear. Additionally, there are no ```else``` statements for which the reader
must remember what the corresponding ```if``` statement was.

@subsection pix-cc-style-predicate-loops Predicate Loops

-------------------------------------------------------------------------------
It is common to write a loop which does some computation to return a boolean
value. It is preferred that such loops are refactored into a function, which
can be ```static```, ```inline``` if small, or reside in a ```detail``` 
or ```anonymous``` namespace near it's use -- if the function is not reusable.

For example, this is not ideal:

@code{.cpp}
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
@endcode

Which can rather be rewritten as a function to compute the predicate, something
like:

@code{.cpp}
  /// Returns true if a foo element is found in
  /// a some array, otherwise returns false.
  static bool containsFoo(const std::array<SomeType>& someArray) {
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
@endcode

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

@subsection pix-cc-style-tdef Typedef vs Alias

-------------------------------------------------------------------------------
C++11 provides the alias feature as an alternative to typedefs. It is preferred
that alias's are used rather than typedefs since it encourages modern C++ and
the syntax is (arguably) more clear. Additionally, where an alias is 
created for a specific template type which may have other similar alias's, then 
add a suffix to the name which indicates the type (for example ```i``` for 
an ```int```, ```f```  for a ```float```, ```16f``` for a 16 element array 
of ```float's``` etc). 

Here is an example of the preferred use of alias's and typedefs:

This is preferred:

@code{.cpp}
  using Vec3f = std::array<float, 3>;
  using Vec3i = std::array<int, 3>;
@endcode

To this:

@code{.cpp}
  typedef std::array<float, 3> Vec3f;
  typedef std::array<int, 3>   Vec3i;
@endcode

@subsection pix-cc-style-assert Assertations

-------------------------------------------------------------------------------
@todo Add the custom Pixel assert when implemented.

Make use of ```assert``` to check preconditions and assumptions. When the
conditions can be checked at compile time use ```static_assert```. This can 
often lead to finding bugs that would otherwise not have been found, saving a 
lot of time when debugging.

To use the assert functionality to its fullest, add an error message to the
assert which will be printed when the assertation fails. For example:

@code{.cpp}
  Element getElement(size_t i) {
    assert(i < Elements.size() && "getElement() out of range access!");
    return Elements[i];
  }
@endcode

@subsection pix-cc-style-usingstd Using namespace std

-------------------------------------------------------------------------------
Avoid ```using namespace std```, and prefer to use the prefix ```std::```.

Also, in header files, avoid the use of ```using namespace X```, and rather
use the prefix ```X::```, since the ```using``` directive pollutes the
namespace of any source file which includes the header.

In source files this is less of a concern, but should still be applied whenever
it is not inconvenient to do so, as it makes functions easy to find. If
multiple namespaces are chained, then define a shorter namespace to represent
it. For example:

@code{.cpp}
  // This is a case which can be simplified.
  pixel::snap::math::sum(x, y);

  // To this.
  namespace math = pixel::snap::math;
  math::sum(x, y);
@endcode

@subsection pix-cc-style-iteration Container Iteration

-------------------------------------------------------------------------------
When iterating over containers and performing some action with the iterator, 
it is preferred that ```std::for_each``` is used, and that the action to
perform on the iterator is provided as either a lambda function or as a
functor. For example:

@code{.cpp}
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
@endcode

However, if the iteration over the container must be written explicitly, then
pre-compute the end iterator so that a call to ```end()``` or ```size()``` 
is not computed for each iteration.

@note This doesn't apply to the case where the container is modified by the
      loop, in which case the pre-computation of ```end()``` or ```size()``` 
      will produce an incorrect result.

In the case that the container is modified, add a comment which says so, and
states why the container is modified. Here is an example:

@code{.cpp}
  IterableArray* array = ...

  // This is the case when the container is not modified:
  for (auto it = array->begin(), end = array->end(); it != end; ++it) {
    // Do something with it
  }

  // This is the case when the container is modified (note comment):
  // Modifies the array each time a bar element is found
  for (auto it = array->begin(); it != array->end(); ++it) {
    if (!it->isBar()) continue;

    // Modify array ...
  }
@endcode

This is done for the following reasons:

1. For complex types the call to ```end()``` can potentially be costly. While 
   this is not the case for a call to ```size()```, the same structure should 
   still be used so that the code has a consistent style. 
2. This makes it immediately clear whether or not the container is modified, 
   without even having to look at the implementation of the loop. This is 
   enforced by the requirement of writing a comment for loops which modify the
   container. 


@subsection pix-cc-style-endl Using std::endl

-------------------------------------------------------------------------------
The use of ```std::endl``` should be avoided, since it flushes the buffer,
which is often not required. Rather use ```\n```, and in the case that the
output stream must be flushed, then append ```std::flush```. For example:

@code{.cpp}
  std::cout << std::endl;             // Avoid this.
  std::cout << "\n";                  // In favour of this.
  std::cout << "\n" << std::flush;    // Or this to flush the output stream.
@endcode

@subsection pix-cc-style-inline Inlining 

-------------------------------------------------------------------------------
For small functions (approx < 10 lines), the ```inline``` keyword may be used 
to hint to the compiler that it should inline the function. However, where a 
function is inlined implicitly, then avoid the use of the :code:`inline` 
keyword. For example:

The inline keyword here is not implicit, so it may be used:

@code{.cpp}
  inline bool isGreater(int a, int b) {
    return a > b;
  }
@endcode

However, the inline keyword here is implicit (method implementation is defined
inside the struct definition), so don't add it:

@code{.cpp}
  struct Foo {
    // Implicit inline, so don't use the inline keyword
    void bar() {
      // Some short implementation ...
    }
  };
@endcode

@subsection pix-cc-style-const Use of const 

-------------------------------------------------------------------------------
Make use of ```const``` as often as possible, since this allows the compiler 
to more aggressively optimise, and makes code easier to reason about. Mark 
class methods ```const``` whenever they do not modify class variables.

@section pix-cc-formatting Formatting 

===============================================================================

@subsection pix-cc-formatting-spaces Spaces for Parentheses

-------------------------------------------------------------------------------
A space before an open parentheses is preferred for control-flow statements,
but not in function calls or macros. No space is preferred after open
parentheses and before closing parentheses, for all cases. For example:

The following examples are good:

@code{.cpp}
  // Control flow statements:
  if (A)                  // ...
  for (i = 0; i < e; ++i) // ...
  while (true)            //...

  // Functions:
  function(argument);
  PIXEL_MACRO(A);
  auto x = sum(4, 5) + divide(4, 2);
@endcode

While the following examples are bad:


@code{.cpp}
  // Control flow statements:
  if(A)                   // ...
  for(i = 0; i < e; ++i ) // ...
  while( true )           // ...

  // Functions:
  function( argument );
  function (argument);
  PIXEL_MACRO ( A );
  auto x = sum (4, 5) + divide( 4, 2 );
@endcode

@subsection pix-cc-formatting-align Alignment of Variables

-------------------------------------------------------------------------------
When declaring variables, always align them in columns, for example:

@code{.cpp}
  int       intOne   , intTwo;
  float     floatOne ;
  OtherType otherType;
@endcode

@subsection pix-cc-formatting-classes Classes and Structs

-------------------------------------------------------------------------------
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

@code{.cpp}
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
@endcode

For constructors, the initialization of member variables should be on the same
line as the constructor declaration, if they can fit, otherwise they should
start on the next line, without indentation. If they cannot all fit on the
following line, then they should each be on a separate line with a 4 space
indent, and all comma's should be in the same column. For example:

@code{.cpp}
  class ExampleClass {
   public:
    // Initialization can fit on the same line:
    ExampleClass(int a, int b) : TotalCount(a), SubCount(b) {}

    // Initialization will fit on a single new line for this:
    ExampleClass(SomeComplexType s, SomeOtherComplexType sc, int a);

    // Initialization will not fit on a single new line for this:
    ExampleClass(SomeComplexType s, SomeOtherComplextType sc, 
      AnotherType at, YetAnotherType yat, int a);

   private:
    SomeComplextType      ComplexTypeA;
    SomeOtherComplexType  ComplexTypeB;
    AnotherType           TypeC;
    YetAnotherType        TypeD;
    int                   TotalCount;
    int                   SubCount;
  };

  ExampleClass::ExampleClass(SomeComplexType s, SomeOtherComplexType sc, 
    int a)
  : ComplexTypeA(s), ComplexTypeB(sc), TotalCount(a), SubCount(0) {
    // Rest of implementation ...
  }

  ExampleClass::ExampleClass(SomeComplexType s, SomeOtherComplextType sc, 
    AnotherType at, YetAnotherType yat, int a)
  :   ComplexTypeA(s) , 
      ComplexTypeB(sc),
      TypeC(at)       , 
      TypeD(yat)      , 
      TotalCount(a)   ,
      SubCount(0)     {
  }
@endcode

@subsection pix-cc-formatting-lambda Lambda Expressions

-------------------------------------------------------------------------------
For lambda expression, the opening brace should be on the same line as the
lambda, the closing bracket should be on its own line, followed by the
closing ```)``` bracket (if appropriate) and the semi-colon. The body of the 
lambda should be indented **2** spaces further than the line above which 
declares the lambda. For example:

@code{.cpp}
  for_each(someVector.begin(), someVector.end(), [] (int& n) {
    n++;        // Two space indent, from line above.
  });           // Closing brace and bracket on the same line.
@endcode

This reduces vertical space and allows more code to fit into a single screen,
allowing whomever is reading the code to gain more context.

In the case where the captures and arguments for the lambda roll over to a new 
line (past the 80 character limit), the next line must have a four space 
indent, as is the case for functions. Use discretion to make the code as 
readable as possible. For example, this is one option:

@code{.cpp}
  std::for_each(someVector.begin(), someVector.end(), [&someVariable](
      int& n) {
    n++;                            // Normal two space indent.
    // Some more ...
  });                               // Closing brace and bracket on same line.
@endcode

This is another option:

@code{.cpp}
  std::for_each(someVector.begin(), someVector.end(), 
      [&someVariable, someOtherVariable] (int& n) {
    n++;                            // Normal two space indent.
    // Some more...
  });                               // Closing brace and bracket on same line.
@endcode

When there are multiple successive lambda functions, start each one on a new 
line, with the ```[]``` indented two spaces further than the previous
indentation, and the body of the lambda indented two spaces from the ```[]```. 
Line up the ```[]``` brackets from each lambda. 

If the lambdas are surrounded by opening and closing round brackets (as in the 
case of a function which takes multiple lambdas), then place the 
closing ```)``` bracket and the semi-colon which follows on their own line. For 
example:

@code{.cpp}
  void someFunctionWithMultpleLambdas(
    [] (int& n) {               // Indented 2 spaces from previous indentation.
      n++;                      // Further two space indent.
    }, 
    [captureVariable] () {      // Lines up with previous lambda.
      // Do something ...       
    }
  );                            // Placed on their own line.
@endcode

@subsection pix-cc-formatting-namespaces Namespaces

-------------------------------------------------------------------------------
Each namespace should be declared on it's own line, with an opening brace on
the same line, and should use lowercase letters. Namespace names should not be
multiple words. The end of the namespace should have a closing brace on its own
line and a comment ```// namespace <namespace_name>``` to indicate the end of 
the namespace. This makes it easy to search for the end of a namespace using 
its name, for files which have multiple namespaces. The body of the namespace 
should not be indented, except for forward declarations which should be 
indented one space. For example:

This is a general namespace example:

@code{.cpp}
  namespace example {
    
  class Foo {
    // Foo details ...
  };

  }  // namespace example
@endcode

This is an example of a forward declaration in a namespace:

@code{.cpp}
  namespace fwdec {
    class Foo;
  }  // namespace fwdec
@endcode

@subsubsection pix-cc-formatting-namespaces-ad Anonymous and Detail Namespaces

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

@code{.cpp}
  namespace {

  struct Comparator {
    Comparator();
    bool operator()(int a, int b) const;
  };

  }  // end anonymous namespace

  static void otherFunction() {
    // ...
  }

  bool Comparator::operator()(int a, int b) const {
    return a < b;
  }
@endcode

While this is bad:

@code{.cpp}
  namespace {

  struct Comparator {
    Comparator();
    bool operator()(int a, int b) const;
  }

  void otherFunction() {
    // ...
  }

  bool Comparator::operatpr()(int a, int b) const {
    return a < b;
  }

  } // end anonymous namespace
@endcode

There is no need for ```operator()``` to be included in the anonymous 
namespace. For ```someFunction()``` it is difficult to tell that it is local 
to the file in the case that it is in the anonymous namespace.

Functions and variables should rather be part of a ```detail``` namespace
and/or use the ```static``` keyword, if they are intended to be used only in 
the surrounding context. For example:

@code{.cpp}
  namespace detail {

  static int  objectCount = 4;
  static void someFunction() {
    // ...
  }

  void someOtherFunction() {
    // ...
  }

  }  // namespace detail
@endcode

@subsection pix-cc-formatting-pandr Pointer and References

-------------------------------------------------------------------------------
For pointers are references, attach the ```*``` or ```&``` operators to the
type rather than to the name. Additionally, the use of ```const``` for 
pointers and ints is shown below:

The following is good convention for pointers:

@code{.cpp}
  // Good for pointers:
  int*              p;      // Non-const pointer to non-const int.
  int* const        p;      // Const pointer to a non-const int.
  const int*        p;      // Non-const pointer to const int.
  const int* const  p;      // Const pointer to const int.
@endcode

While the following is bad for pointers:

@code{.cpp}
  int const*        p;
  int              *p;
  int * const       p;
  const int        *p;
  const int * const p;
@endcode

The following is good for references:

@code{.cpp}
  int&              r;      // Non-const int reference.
  const int&        r;      // Const int reference.
@endcode

While the following is bad for references:

@code{.cpp}
  int              &r;
  const int        &r;
  int const&        r;
  int const        &r;
@endcode

@subsection pix-cc-naming Naming 

-------------------------------------------------------------------------------
Naming is important as poor naming can cause confusion when trying to
understand how code works, and can lead to bugs. Names should be descriptive,
allowing the reader to understand the usage and intention of a variable or type
from it's name. Avoid abbreviations where possible, and conform to the 
capitalization conventions, as they are designed to allow for immediate 
identification of types, variables, functions, access scope, etc..., without 
having to actually search for that information.

Most importantly, be consistent.

@subsection pix-cc-naming-type-names Type Names

-------------------------------------------------------------------------------

Type names, such as classes, structs, typedefs, alias's, and type template
parameters, should be nouns, use CamelCase, and start with a capital letter. 
Enums have additional rules -- see [Enums](@ref pix-cc-naming-enums).

The following are examples:

@code{.cpp}
  // Classes an structs:
  class  ErrorHandler {};
  struct FileProperties {}:

  // Typedefs (for the odd case that they are used):
  typedef std::array<float, 3> Vec3f;

  // Aliases when not part of a class or struct:
  using FloatArray = std::array<float>;

  // Template type parameter:
  template <typename AllocatorType>
  class SmallVector {
    // ...
  };
@endcode

Exceptions to this rule are when the ```using``` keyword is used to create an
alias for a class/struct which is part of the public interface, in which case
the name should be CamelCase but start with a lowercase letter. For example:

@code{.cpp}
  template <typename SomeType, typename SomeOtherType>
  struct Example {
    /// Defines the type of the example.
    using type          = typename SomeType::type;
    /// Defines something else.
    using somethingElse = SomeOtherType;
  };
@endcode

When an alias is private, then it should use CamelCase but begin with an
uppercase letter. For example:

@code{.cpp}
  template <typename SomeType, typename SomeOtherType>
  class Example {
    /// Defines the type of the example.
    using Type          = typename SomeType::type;
    /// Defines something else.
    using SomethingElse = SomeOtherType;
  };
@endcode

Additionally, if a using directive mirrors a template parameter, then it should
have the same name but start with a lowercase letter. For example:

@code{.cpp}
  template <typename Allocator>
  struct TinyVector {
    /// Defined the allocator type.
    using allocator = Allocator;
  };

  template <typename Type>
  struct SomeMetaprogrammingStruct {
    /// Defines the type of the metaprogramming struct.
    using type = Type;
  };
@endcode

@subsection pix-cc-naming-enums Enums

-------------------------------------------------------------------------------
Enum declarations are types, so they should follow the formatting of type names
by using CamelCase. The contents of the enum should use uppercase letters. The
enum should also have a prefix which uses a 2 letter abbreviation of the
project name if not in the project namespace, followed by an abbreviation of 
the enum name if the enum is not scoped. For example:

For an enum in the global namespace (project pixel):

@code{.cpp}
  enum ErrorType {
    PX_ET_SUCCESS = 0, 
    PX_ET_FAILURE = 1
  };

  // Access as:
  PX_ET_SUCCESS;
@endcode
    
For an enum in the project namespace (pixel):

@code{.cpp}
  namespace pixel {

  enum ErrorType {
    ET_SUCCESS = 0, 
    ET_FAILURE = 1
  };

  } // namespace pixel

  // Access as:
  pixel:ET_SUCCESS;
@endcode

For an enum in a more specialized namespace:

@code{.cpp}
  namespace pixel  {
  namespace ecodes {

  enum ErrorType {
    ET_SUCCESS = 0, 
    ET_FAILURE = 1
  };

  } // namespace ecodes
  } // namespace pixel

  // Access as: 
  pixel::ecodes::ET_SUCCESS;
@endcode

When enums are scoped, then the contents do not need a 2 letter abbreviation:

 @code{.cpp} 
  namespace pixel {
    
  enum class ErrrorType : uint8_t {
    SUCCESS = 0,
    FAILURE = 1
  };

  } // namespace pixel

  // Access as:
  pixel::ErrorType::SUCCESS;
@endcode

Scoped enums are preferred over the other options as they are the most
explicit, at the cost of some extra verbosity.

Enums which are used to define constants don't need to have a name:

@code{.cpp}
  enum {
    CONST_TWENTY_ONE = 21, 
    CONST_TWENTY_TWO = 22
  };
@endcode

@subsection pix-cc-naming-variables Variables

-------------------------------------------------------------------------------
Variables should be nouns, and the name should be written using CamelCase,
starting with a lowercase letter. Private member variables, however, should
begin with an uppercase letter. For example:

This is a local variable naming example:

@code{.cpp}
  int someInt = 4;
@endcode

This is a class naming example:

@code{.cpp}
  class NamingExample {
   public:
    // Public member variable:
    int someInt; 

    // Function arguments:
    NamingExample(int someOtherInt)
    : someInt(someOtherInt) {}
 
   private:
    // Private member variable:
    int SomeOtherInt;
  };
@endcode

This is a struct naming example:

@code{.cpp}
  struct Params {
    bool    firstInstance;
    size_t  maxRecursiveCalls;
  };
@endcode

@subsection pix-cc-naming-function Functions

-------------------------------------------------------------------------------
Function names should be verbs, and use CamelCase, with the first word starting
with a lowercase letter -- just like public and local variables. The reason for
using the same convention for public and local variables, and functions, is 
that function calls are easily identifiable from the fact that they need 
arguments (or empty brackets). Using the same style makes the code look better
without making it less readable. 

The following is a function naming example:

@code{.cpp}
  void        containsFoo();
  FileHandle  openFile():
@endcode

When the arguments of a function will exceed the 80 character limit, then begin
each new line of function arguments with:

- A **2** space indent when the function is **a definition**
- A **4** space indent when the function has **an implementation**, then use 
  the standard **2** space indent for the body of the function.
- A hanging indent if this is preferred.

The following are examples:

This is an example for a function definition (**note** the alignment when using
the hanging indent options):

@code{.cpp}
  // 2 space indent:
  int aFunctionWithManyLongArguments(ArgumentTypeOne argOne, 
    ArgumentTypeTwo argTwo, ArgumentTypeThree argThree);

  // Hanging indent option 1 (preferred over option 2):
  int aFunctionWithManyLongArguments(
    ArgumentTypeOne   argOne  ,
    ArgumentTypeTwo   argTwo  ,
    ArgumentTypeThree argThree);

  // Hanging indent option 2:
  int aFunctionWithManyLongArguments(ArgumentTypeOne   argOne  ,
                                     ArgumentTypeTwo   argTwo  ,
                                     ArgumentTypeThree argThree);
@endcode

For the above, if using option 2 for the hanging indent and any of the
arguments will not fit on the remainder of the line, then option 1 must be
used. Option 1 is also preferred to option 2, in general.

This is an example for a function with an implementation:

@code{.cpp}
  // 4 space indent:
  int aFunctionWithManyLongArguments(ArgumentTypeOne argOne, 
      ArgumentTypeTwo argTwo, ArgumentTypeThree argThree) { 
    // Function body ...
  };

  // Hanging indent option 1:
  int aFunctionWithManyLongArguments(
      ArgumentTypeOne   argOne  ,
      ArgumentTypeTwo   argTwo  ,
      ArgumentTypeThree argThree) {
    // Function body ...
  }

  // Hanging indent option 2:
  int aFunctionWithManyLongArguments(ArgumentTypeOne   argOne  ,
                                     ArgumentTypeTwo   argTwo  ,
                                     ArgumentTypeThree argThree) {
    // Function body ...
  }
@endcode

For the above case, option 1 for the hanging indent is not necessarily
preferred over option 2 as option 2 can often make the implementation more
readable as it is easy to distinguish the start of the implementation from the
function arguments.

*/
