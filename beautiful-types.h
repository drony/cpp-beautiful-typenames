#define BEAUTIFUL_IMPORT_ALL using namespace beautiful::all

#define BEAUTIFUL_IMPORT(name) using namespace beautiful::name

#define BEAUTIFUL_IMPORT_AS(name, alias) \
  template <typename... args> using alias = beautiful::name::name<args...>

#define BEAUTIFUL_IMPORT_ARRAY_AS(alias) \
  template <typename T, size_t... N> \
  using alias = beautiful::array::array<T, N...>

namespace beautiful {

  namespace impl {

    template <typename...args>
    struct list {
      template <typename x> using push_front = list<x, args...>;
      
      template <typename x> using push_back = list<args..., x>;
      
      template <template <typename...> class func>
      using pass_to = func<args...>;
    };

    template <typename xs, typename next, typename... last>
    struct last_as_first {
      typedef typename last_as_first<typename xs::template push_back<next>,
                                     last...>::value value;
    };

    template <typename xs, typename last>
    struct last_as_first<xs, last> {
      typedef typename xs::template push_front<last> value;
    };
    
    template<template <typename...> class func, typename... args>
    using pass_last_as_first = typename last_as_first<list<>, args...>::value::template pass_to<func>;

    template <typename T, size_t... N>
    struct get_array;
    
    template <typename T, size_t N>
    struct get_array<T, N> {
      typedef T value [N];
    };
    
    template <typename T>
    struct get_array<T> {
      typedef T value [];
    };
    
    template <template <typename...> class func, typename... args>
    using pass = typename list<args...>::template pass_to<func>;

    template <typename T, typename... args> using lfun = T(args...);

  }
  
  namespace all {
  
    template <typename T> using ref = T&;
    
    template <typename T> using ptr = T*;
    
    template <typename T, size_t...N>
    using array = typename impl::get_array<T, N...>::value;
    
    template <typename T> using cnst = const T;
    
    template <typename T> using vltl = volatile T;
    
    template <typename... args> using lfun = impl::pass<impl::lfun, args...>;
    
    template <typename... args> using plfun = ptr<lfun<args...>>;
    
    template <typename... args>
    using fun = impl::pass_last_as_first<lfun, args...>;
    
    template <typename... args> using pfun = ptr<fun<args...>>;
    
  }
  
  namespace ref {
    template <typename T> using ref = all::ref<T>;
  }
  
  namespace ptr {
    template <typename T> using ptr = all::ptr<T>;
  }
  
  namespace array {
    template <typename T, size_t...N>
    using array = typename all::array<T, N...>;
  }
  
  namespace cnst {
    template <typename T> using cnst = all::cnst<T>;
  }
  
  namespace vltl {
    template <typename T> using vltl = all::vltl<T>;
  }
  
  namespace lfun {
    template <typename... args> using lfun = all::lfun<args...>;
  }

  namespace fun {
    template <typename... args> using fun = all::fun<args...>;
  }

  namespace plfun {
    template <typename... args> using plfun = all::plfun<args...>;
  }
  
  namespace pfun {
    template <typename... args> using pfun = all::pfun<args...>;
  }
  
}