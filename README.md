# Beautiful types names for C++
The header library provides a template-like type notation for the existent C++ types.
## Overview

C/C++ types names are always interesting to read:

    const int * x = 5;

What is it? A pointer to constant or a constant pointer? The library proposes a solution:

    ptr<cnst<int>> x = 5;

You may say "It is too hard to read! Star is cool!" But consider these examples:

    typedef double number; // OK, from "double" to "number"
    typedef int ints[10]; // OK, I see "ints" somewhere
    typedef int* (*func) (int ints[10], int[]); // OMG, where is my type name?

The library provides a better way:

    typedef double number; // OK, from double to number
    typedef array<int, 10> ints; // OK, from array to "ints"
    typedef pfun<array<int, 10>, array<int>, ptr<int>> func; // OK, from function to "func"

The types are not something new. It is not like `std::function` or `std::array` that are not function and array respectively. `array<int>` is `int[]`, ptr<int> is `int*` and `fun<int, char, double>` is `double(int, char)`.

You can make type aliases, define variables and functions using this type notation. You can use it partially:

    typedef int (*pfunc) (array<int>, cnst<ref<std::list<const int>>>);
    typedef fun<array<int>, cnst<ref<std::list<const int>>>, int>* pfunc2;
    typedef pfun<array<int>, cnst<ref<std::list<cnst<int>>>>, int> pfunc3;

The only limitation is defining function. You can't define a variable of type `fun<...>` and specify its body. But it is possible to use the library while specifying the arguments and the result type:

    int func (array<int>, cnst<ref<std::list<cnst<int>>>>) {
        ...
    }

And you do able to declare a function using the type notation:

    fun<array<int>, cnst<ref<std::list<cnst<int>>>>, int> func;

    int func (array<int>, cnst<ref<std::list<cnst<int>>>>) {
        ...
    }

## Usage

Just include one file:

    #include "beautiful-types.h"

Then you can import something using

* `BEAUTIFUL_IMPORT_ALL` to import everything,
* `BEAUTIFUL_IMPORT(name)` to import type function `name`,
* `BEAUTIFUL_IMPORT_AS(name, newname)` to import type function `name` with the `newname` specified,
* `BEAUTIFUL_IMPORT_ARRAY_AS(newname)` to import type function `array` with the `newname` specified.

The macros above is just something like `use namespace beautiful::fun` or `template ... using newname as name`. You can use this directly by typing

* `using namespace beautiful::all` to import everything,
* `using namespace beautiful::name` to import type function `name`.

Then the types choosen become available.

## Reference

### Namespaces and hierarchy

* `namespace beautiful`
  * `namespace all` having
     * `type function ref`
     * `type function ptr`
     * `type function array`
     * `type function cnst`
     * `type function vltl`
     * `type function lfun`
     * `type function fun`
     * `type function plfun`
     * `type function pfun`
  * `namespace ref` having `type function ref`
  * `namespace ptr` having `type function ptr`
  * `namespace array` having `type function array`
  * `namespace cnst` having `type function cnst`
  * `namespace vltl` having `type function vltl`
  * `namespace lfun` having `type function lfun`
  * `namespace fun` having `type function fun`
  * `namespace plfun` having `type function plfun`
  * `namespace pfun` having `type function pfun`

### Type functions
#### `ref<typename T>`: reference
 `ref<T>` is `T&`
#### `ptr<typename T>`: pointer
 `ptr<T>` is `T*`
#### `array<typename T, size_t...N>`: array/sized array
  `array<T>` is `T[]`
  `array<T, N>` is `T[N]`
#### `cnst<typename T>`: constant
 `cnst<T>` is `const T`
#### `vltl<typename T>`: volatile
 `vltl<T>` is `volatile T`
#### `lfun<typename... TS>`: function (the first argument is the result type)
  `lfun<T>` is `T()`
  
  `lfun<T, T1>` is `T(T1)`
  
  `lfun<T, T1, T2>` is `T(T1, T2)`
  
  `lfun<T, T1, T2, T3>` is `T(T1, T2, T3)`
  ...
#### `fun<typename... TS>`: function (the last argument is the result type)
  `fun<T>` is `T()`
  
  `fun<T1, T>` is `T(T1)`
  
  `fun<T1, T2, T>` is `T(T1, T2)`
  
  `fun<T1, T2, T3, T>` is `T(T1, T2, T3)`
  
  ...
#### `plfun<typename... TS>`: pointer to a function (the first argument is the result type)
  `plfun<T>` is `T(*)()`
  
  `plfun<T, T1>` is `T(*)(T1)`
  
  `plfun<T, T1, T2>` is `T(*)(T1, T2)`
  
  `plfun<T, T1, T2, T3>` is `T(*)(T1, T2, T3)`
  
  ...
#### `pfun<typename... TS>`: pointer to a function (the last argument is the result type)
  `pfun<T>` is `T(*)()`
  
  `pfun<T1, T>` is `T(*)(T1)`
  
  `pfun<T1, T2, T>` is `T(*)(T1, T2)`
  
  `pfun<T1, T2, T3, T>` is `T(*)(T1, T2, T3)`
  
  ...

## Example

    #include <iostream>
    #include "beautiful-types.h"

    BEAUTIFUL_IMPORT_AS(ptr, pointer);
    BEAUTIFUL_IMPORT(fun);
    BEAUTIFUL_IMPORT(array);

    template<typename item_t>
    pointer<item_t> map(fun<item_t, item_t> f, pointer<item_t> in, size_t len) {
      pointer<item_t> out = new item_t[len];
      
      for(size_t i = 0; i < len; ++ i)
        out[i] = f(in[i]);
      
      return out;
    }

    fun<int, int> twice;

    int main() {
      
      array<int, 5> xs = {1, 2, 3};
      int* xs1 = map(twice, xs, 5);

      for(int i=0; i<5; ++i) std::cout << xs1[i] << std::endl;

      delete xs1;

      return 0;
    }

    int twice(int x) {
      return 2*x;
    }

    // OUTPUT:
    // 2
    // 4
    // 6
    // 0
    // 0