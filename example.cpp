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