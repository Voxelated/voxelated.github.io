---
layout: post
title: Template Metaprogramming Basics
excerpt: "Towards a metaprogramming understanding!"
tags: [C++, metaprogramming]
comments: true
modified: 2016-11-23
---

[Template metaprogramming](https://en.wikipedia.org/wiki/Template_metaprogramming) 
(TMP) in C++ is a method of generic programming which essentially uses the 
compiler to interpret the code and generate temporary source code which is then 
used with the rest of the code. 

The above statement is a bit of a complicated way to put it, so more simply, it 
is a way of programming the type system in C++ to do something useful in our 
programs, at compile time. This can have some pretty drastic benefits in
runtime performance when used correctly (and some negative impact on the time 
required to compile the program).

This post is by no means an extensive overview on template metaprogramming, or
an attempt to demonstrate some of its most powerful features, but rather an
introduction which will hopefully allow you to see the general thought pattern
required for template metaprogramming. In some later posts I will get into some
of the more advanced features which one might use.

### Basics

To implement something with template metaprogramming, we need to change our
mindset slightly. In C++, we are used to using templates to make classes
generic, for example, the standard library's vector class:

```cpp
template <typename T, typename Allocator = std::allocator<T>>
class vector {
  ...
};
```

The standard library allows a vector of any type, and allows the user to 
specify the allocation object which will perform the memory allocation for the
data types the vector holds. Templates allow the vector to be generic, but the 
vector is the object which holds the data, which can be operated on at 
*runtime* -- for example to sum the elements.

Lets take that example -- summing the elements of a container -- and see if we
can get the compiler to do something similar but at compile time. We will also
try and make sure that the interface for doing so it clear, and understandable. 
What we need is some struct which can hold something which can be evaluated at
compile time. Well types are evaluated at compile time, so can we have a struct
which can hold types? Yes, the template parameters of a struct are types! We
just need to store any number of different types. Fortunately, C++ does provide
this functionality!

### Variadic Templates

In C++11, parameter packs were introduced to allow that a struct has an
undefined number of types (template parameters), which will be specified when 
the struct is instantiated. This is exactly what we need, so let's go ahead and 
define a struct with a parameter pack:

```cpp
template <typename... Types>
struct TypeList {
};
```

In the above code, the ```...``` (elipses) indicate the the pack (named
```Types```) may consist of any number of unknown types. We can now declare
objects such as the following:

```cpp
TypeList<int  , int>            intTypes;
TypeList<float, float>          floatTypes;
TypeList<int  , float, double>  mixedTypes;
```

Great, we can now create objects which store an unlimited number of types (well
not really because the compiler evaluates variadic templates recursively so it
would crash with too long a ```TypeList```). This isn't particularly useful at
the moment, because we can't do anything with the types stored in the
```TypeList```, and we don't know how to operate on the ```TypeList```. Lets
fix the first problem.

### A Compile Time Number

To start with, we will define a struct which stores a number which can be used
at compile time. The requirements are that the compile time number be a type 
(so that it can be part of the TypeList), but also have an assosciated value 
which can be used which can be accessed. To achieve this, we store the value of
the number as a template parameter of a ```Number``` class:

```cpp
template <size_t Value>
struct Number {
  //  More to follow ...
};
```

We can then define *alises* for different ```Number```s, and store them in the
TypeList, as follows:

```cpp
using N1 = Number<1>;
using N2 = Number<2>;

TypeList<I1, I2> Numbers;
```

### Comparison to Traditional Programming

Following the above declaration of a compile time number, it may be useful to
compare declarations and operations in metaprogramming compared to what we are
used to in more traditional programming:

```cpp
// Traditional variable declaration:
size_t tradNum = 4;

// Metaprogramming variable declaration, so to speak:
using metaNum = Number<4>;
```

We see that a metaprogramming declaration is similar to some declarations in
other languages. The ```using``` keyword (C++11 onwards) is kind of similar to 
```var``` in Swift, and allows us to "declare" a metaprogramming variable. 

In object oriented programming if we defined our own class we could perform
operations on it, for example:

```cpp
struct Number {
  size_t val;

  Number(size_t value) : val(value) {}

  // Operation on number:
  size_t square() const { return value * value; }
};
```

which can be used as follows:

```cpp
Number num(4);

auto squaredNum = num.square();
```

So how do we perform something similar on the metaprogramming ```Number```? We
just need to return (make accessible) a type with a doubled value:

```cpp
template <size_t Value>
struct Number {
  static constexpr size_t value = Value;

  using SquaredType = Number<Value * Value>;
};
```

We can then make an alias for the doubled type as follows:

```cpp
using N = Number<10>;

using NSquared = typename N::SquaredType;
```

While this is just a toy example, the point was to illustrate how we access
components of meta types -- through the scope resolution operator. To summarize
the different syntax between object oriented and metaprogramming:

```cpp
// Declaration:
Number n(4);          // OO
using N = Number<4>;  // MP

// Operate on:
auto nsquared  = n.square();              // OO -- evaluated at runtime
using NSquared = typename N::SquaredType; // MP -- this is still a type.

// Get NSquared's value:
auto nSquaredVal = NSquared::value;       // MP -- evaluated at compile time
```

### Metafunctions

We now have containers of types, and a ```Number``` struct which can hold
compile time number, which we know how to access the values of. Lets create an
example list which we will create a metafunction to sum:

```cpp
using ExampleList = TypeList<Number<1>, Number<2>, Number<3>>;
```

We need to create a metafunction which sums the list's elements. We will create
a recursive version, which adds the first two elements at each step, and stops
when there are no more elements to add. A metafunction is just a struct which
takes as a template parameter, a type which we want to operate on. We then
(partially) specialize the struct for the different cases.

Side Note: Partial specialization is where one defines some of the template
parameters for a struct generically, and others explicitly. We will see an
example now.

First, the definition of out metafunction, ```Sum```:

```cpp
template<typename ResultantSum, typename UnevaluatedList>
struct Sum;
```

In the above definition, the first template parameter is essentially the output
of the function, and the second is the input, which is out list. We only
declared the struct above, we will now partially specialize it for the two
cases.

The first case is when there are still elements in ```UnevaluatedList``` which
have not been added to ```ResultantSum```, this looks like:

```cpp
template <size_t Value, typename FirsType, typename OtherTypes...>
struct Sum<Number<Value>, TypeList<FirstType, OtherTypes...>> {
  static constexpr size_t result = 
    Sum<Number<Value + FirstType::value>, TypeList<OtherTypes...>>::result;
};
```

This may seen a little confusing, but what is happening is that when sum is
called, it creates a new ```Sum``` object, with a new ```Number``` using the 
sum of the number's current value ```Value``` and the value of the first type 
in the list, as the number's value. It then uses the rest of the elements in
the TypeList as the elements in the ```UnevaluatedList``` for that sum. This
will continue until a specialization of ```Sum``` is reached which does not
create a new ```Sum``` recursively. This will become a little more clear just
now, but let's first define the terminating case, which is when the
specialization for the TypeList element is a list with no elements:

```cpp
template <size_t Value>
struct Sum<Number<Value>, TypeList<>> {
  static constexpr size_t result = Value;
};
```

the result when this case is the ```Value```, which is the sum of all the
values of the elements in the ```TypeList```. We can now calculate the sum of
our example list:

```cpp
using ExampleList = TypeList<Number<1>, Number<2>, Number<3>>;

auto result = Sum<Number<0>, ExampleList>::result;
```

```result``` will have a value of 6, which will have been calculated at compile
time! We had to specify ```Number<0>``` as the first type for ```Sum``` to use
as the starting value of the sum. 

The declaration of the ```TypeList``` is a little verbose. We would rather not
have to type out Number for each of the numbers. So let's create an alias which
does that for us:

```cpp
template <size_t... Values>
using NumberList = TypeList<Number<Values>...>;
```

The above creates a ```Number<>``` type for each of the Values and expands it
into the TypeList.

Also, we don't want to have to tell the Sum that we are starting at 0, but
rather let the user optionally specify the starting value, so let's also add
that functionality;

```cpp
template <typename List, size_t StartValue = 0>
using BetterSum = Sum<Number<StartValue>, List>;
```

Note that we put the starting value last, which is required because we have it
a default value. The usage is now much more clear and concise:

```cpp
using Numbers = NumberList<1, 2, 3>;

// Sum starts at 0:
auto result = BetterSum<Numbers>::result;       // result = 6

// Sum starts at 10:
auto result2 = BetterSum<Numbers, 10>::result; // result2 = 16;
```

We have achieved what we set out to -- we can sum numbers at compile time with
a clear interface! We have even added some functionality for specifying the
starting value of the sum. It may still be a little difficult to understand
exactly what is going on, so I will add an example evaluation of the sum.

### Example Evaluation

When the Sum is evaluated, what happens is the following:

```
  auto result = Sum<Number<0>, TypeList<Number<1>, Number<2>, Number<3>>::result
                                                                            |
  ---------------------------------------------------------------------------
  |
  --> Sum<Number<0 + 1>, TypeList<Number<1>, Number<2>, Number<3>>::result
                                                                      |
    -------------------------------------------------------------------
    |
    --> Sum<Number<1 + 2>, TypeList<Number<2>, Number<3>>::result
                                                             |
      --------------------------------------------------------
      |
      --> Sum<Number<3 + 3, TypeList<Number<3>>::result
                                                   |
        --------------------------------------------
        |
        --> Sum<Number<6>, TypeList<>::result 
                                         |
          --------------------------------
          |
          --> Base case, return the value (6)
```

So on each iteration, the value of the number at the front of the list is added
to the current sum (just as we would do in a recursive implementation), and
that first Number element is peeled off the front of the list, which keeps
happening until there are no elements lest, at which point the result is the
value of the sum!

### Wrapping Up

I hope that this has been a fairly useful introduction to metaprogramming. The
example may not be the most useful, but it has illustrated how to perform
metaprogramming calculations recursively. There are other ways, which the
compiler evaluates more quickly, but we will leave that for another time.
