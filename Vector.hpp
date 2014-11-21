#ifndef VECTOR_HPP
#define VECTOR_HPP 

#include "Rational.hpp"

namespace mmath {
namespace vec {

namespace priv{

template<typename X, typename Y, typename Z>
struct Vector {
  using x = X;
  using y = Y;
  using z = Z;
};

template<typename A, typename B, template<typename,typename> class Op>
struct __BinOp__ {
  using x_ = Op<typename A::x, typename B::x>;
  using y_ = Op<typename A::y, typename B::y>;
  using z_ = Op<typename A::z, typename B::z>;

  using value = Vector<x_, y_, z_>;
};

template<typename A, typename B>
struct Add {
  using value = typename __BinOp__<A, B, ratio::add>::value;
};

template<typename A, typename B>
struct Sub {
  using value = typename __BinOp__<A, B, ratio::sub>::value;
};

template<typename A, typename B>
struct Mul {
  using value = typename __BinOp__<A, B, ratio::mul>::value;
};

template<typename A, typename B>
struct Div {
  using value = typename __BinOp__<A, B, ratio::div>::value;
};

template<typename A, typename B>
struct Equal {
  static const bool value = ratio::eq<typename A::x, typename B::x>::value && 
                            ratio::eq<typename A::y, typename B::y>::value && 
                            ratio::eq<typename A::z, typename B::z>::value;
};

template<typename A, typename B>
struct NotEqual {
  static const bool value = !Equal<A,B>::value;
};

template<typename A, typename B>
struct Dot {
  using x_ = typename ratio::mul<typename A::x, typename B::x>;
  using y_ = typename ratio::mul<typename A::y, typename B::y>;
  using z_ = typename ratio::mul<typename A::z, typename B::z>;
  using value = typename ratio::add<typename ratio::add<x_, y_>, z_>;
};

template<typename A>
struct Length {
  using value = typename ratio::sqrt<typename Dot<A, A>::value>;
};

}

template<typename X, typename Y, typename Z>
using vector = priv::Vector<X, Y, Z>;

template<typename A, typename B>
using add = typename priv::Add<A, B>::value;
template<typename A, typename B>
using sub = typename priv::Sub<A, B>::value;
template<typename A, typename B>
using mul = typename priv::Mul<A, B>::value;
template<typename A, typename B>
using div = typename priv::Div<A, B>::value;

template<typename A, typename B>
using eq = priv::Equal<A, B>;
template<typename A, typename B>
using neq = priv::NotEqual<A, B>;

template<typename A, typename B>
using dot = typename priv::Dot<A, B>::value;

template<typename A>
using len = typename priv::Length<A>::value;

}
}

#endif /* VECTOR_HPP */
