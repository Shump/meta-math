#ifndef RATIONAL_HPP

#include <utility>

namespace mmath {
namespace ratio {


namespace priv {

template<typename A, typename B>
struct _SameNominator {
  using value_type = typename A::value_type;
  static const value_type a_nom = A::Nom * B::Denom;
  static const value_type b_nom = B::Nom * A::Denom;
};

template<typename A, typename B>
struct Equal {
  using same_nom = _SameNominator<A, B>;
  static const bool value = same_nom::a_nom == same_nom::b_nom;
};

template<typename A, typename B>
struct NotEqual {
  using same_nom = _SameNominator<A, B>;
  static const bool value = same_nom::a_nom != same_nom::b_nom;
};

template<typename A, typename B>
struct Less {
  using same_nom = _SameNominator<A, B>;
  static const bool value = same_nom::a_nom < same_nom::b_nom;
};

template<typename A, typename B>
struct LessEq {
  using same_nom = _SameNominator<A, B>;
  static const bool value = same_nom::a_nom <= same_nom::b_nom;
};

template<typename A, typename B>
struct Greater {
  using same_nom = _SameNominator<A, B>;
  static const bool value = same_nom::a_nom > same_nom::b_nom;
};

template<typename A, typename B>
struct GreaterEq {
  using same_nom = _SameNominator<A, B>;
  static const bool value = same_nom::a_nom >= same_nom::b_nom;
};

constexpr unsigned int integer_length(long long i) {
  long long i_ = i / 10;
  return i_ == 0 ? 1 : 1 + integer_length(i_);
}

constexpr long long tenth_pow(unsigned int e) {
  return e == 0 ? 1 : 10 * tenth_pow(e-1);
}

template<typename T>
constexpr T gcd(T a, T b) {
  return (b == 0 ? a : gcd<T>(b, a % b));
} 

constexpr bool __neg__(long long n) {
  return n < 0;
}

constexpr long long __abs__(long long n) {
  return __neg__(n) ? -n : n;
}

template<long long NN, long long DD, typename T = long long>
struct Value {
  
  using value_type = T;

  static const long long Nom = NN;
  static const long long Denom = DD;    
};

template<typename A, bool simple> struct Absolute;
template<typename A, typename B, bool simple> struct Sub;
template<long long N, long long D, long long DENOM_LIMIT, long long PRECISION> struct Rational;

template<typename A>
struct Reduce {
  using value_type = typename A::value_type;

  static const value_type GCD = gcd<value_type>(A::Nom, A::Denom);

  using value = Value<A::Nom / GCD, A::Denom / GCD>;
};

template<unsigned int i, long long N, long long D, long long d_limit, long long prec>
struct Round {
  static const long long N_ = N / tenth_pow(i);
  static const long long D_ = (N_ == 0 ?  1 : D / tenth_pow(i));

  using rounded = Value<N_,D_>;
  using old = Value<N, D>;

  using diff = typename Sub<rounded, old, true>::value;
  using abs = typename Absolute<diff, true>::value;

  using sigma = Value<1,prec>;

  static const bool acceptable = Less<abs, sigma>::value;

  using value = typename std::conditional<acceptable, 
        typename Reduce<Value<N_, D_>>::value,
        typename Round<i - 1, N, D, d_limit, prec>::value>::type;
};

template<long long N, long long D, long long d_limit, long long prec>
struct Round<0, N, D, d_limit, prec> {
  static const long long comp = 1; // Compensation for integer div.
  static const long long factor = D / d_limit + comp;

  static const long long Nom = N / factor;
  static const long long Denom = D / factor;
  using value = typename std::conditional<Nom == 0,
        Value<0,1>,
        Value<N / factor,D / factor>>::type;
};

constexpr long long __fix_minus_nom__(long long n, long long d) {
  return __neg__(n) != __neg__(d) ? -__abs__(n) : __abs__(n);
}

// Max long long value = 9223372036854775807
template<long long N, long long D, long long PRECISION = 1000, long long DENOM_LIMIT = 20971>
struct Rational {

  using value_type = long long;

  static const value_type denom_limit = DENOM_LIMIT;
  static const value_type precision = PRECISION;

  using reduced = typename Reduce<Value<N,D>>::value;
  //static const value_type short_n = __fix_minus_nom__(reduced::Nom, reduced::Denom);
  //static const value_type short_d = __abs__(reduced::Denom);
  static const value_type short_n = reduced::Nom;
  static const value_type short_d = reduced::Denom;

  static const bool should_short = short_d > denom_limit;
  static const unsigned int start = should_short ? integer_length(short_d) - 1 : 0;
  using temp_value = typename std::conditional<true, 
        typename Round<start, short_n, short_d, denom_limit, precision>::value,
        Value<short_n, short_d>>::type;

  static const value_type Nom = temp_value::Nom;
  static const value_type Denom = temp_value::Denom;

  template<typename U = double>
  static U value() {
    return U(Nom) / U(Denom);
  };
};

template<long long D, long long PRECISION, long long DENOM_LIMIT>
struct Rational<0, D, PRECISION, DENOM_LIMIT> {

  using value_type = long long;

  static const value_type Nom = 0;
  static const value_type Denom = 1;

  template<typename U = double>
  static U value() {
    return U(Nom) / U(Denom);
  };
};

template<typename A, typename B, bool simple = false>
struct Add {
  //TODO: simplify! Might case less instatiations.
  using value = Rational<A::Nom * B::Denom + B::Nom * A::Denom, A::Denom * B::Denom>;
};

template<typename A, typename B, bool simple = false>
struct Sub {
  using value_type = typename A::value_type;
  static const value_type Nom = A::Nom * B::Denom - B::Nom * A::Denom;
  static const value_type Denom = A::Denom * B::Denom;
  using value = typename std::conditional<simple,
        Value<Nom,Denom>,
        Rational<Nom, Denom>>::type;
};

template<typename A, typename B, bool simple = false>
struct Mul {
  using value_type = typename A::value_type;
  static const value_type Nom = A::Nom * B::Nom;
  static const value_type Denom = A::Denom * B::Denom;
  using f = Rational<Nom, Denom>;
  using value = Rational<f::Nom, f::Denom>;
};

template<typename A, typename B, bool simple = false>
struct Div {
  using value_type = typename A::value_type;
  static const value_type Nom = A::Nom * B::Denom;
  static const value_type Denom = A::Denom * B::Nom;
  using value = Rational<Nom, Denom>;
};

template<typename A>
struct Negate { 

};

template<typename A, bool simple = false>
struct Absolute {
  using value_type = typename A::value_type;
  static const value_type Nom = A::Nom < 0 ? -A::Nom : A::Nom;
  static const value_type Denom = A::Denom < 0 ? -A::Denom : A::Denom;
  
  using value = typename std::conditional<simple,
        Value<Nom, Denom>,
        Rational<Nom, Denom>>::type;
};

template<typename A, typename x, unsigned int iteration>
struct Sqrt_ {
  using div = typename Div<A, x>::value;
  using add = typename Add<x, div>::value;
  using x_ = typename Mul<Rational<1,2>, add>::value;
  using value = typename Sqrt_<A, x_, iteration - 1>::value;
};

template<typename A, typename x>
struct Sqrt_<A, x, 0> {
  using value = x;
};

template<typename A, unsigned int iterations = 20>
struct Sqrt {
  using x = typename Div<A, Rational<2,1>>::value;
  using value = typename Sqrt_<A, x, iterations>::value;
};

template<typename A, unsigned int power>
struct Pow {
  using value = typename Mul<A, typename Pow<A, power - 1>::value>::value;
};

template<typename A>
struct Pow<A, 0> {
  using value = Rational<1,1>;
};

}

template<long long N, long long D>
using rational = priv::Rational<N, D>;

template<typename A, typename B>
using add = typename priv::Add<A, B>::value;
template<typename A, typename B>
using sub = typename priv::Sub<A, B>::value;
template<typename A, typename B>
using mul = typename priv::Mul<A, B>::value;
template<typename A, typename B>
using div = typename priv::Div<A, B>::value;

template<typename A, typename B>
using eq = typename priv::Equal<A,B>;
template<typename A, typename B>
using neq = typename priv::NotEqual<A,B>;

template<typename A, typename B>
using lt = typename priv::Less<A,B>;
template<typename A, typename B>
using le = typename priv::LessEq<A,B>;
template<typename A, typename B>
using gt = typename priv::Greater<A,B>;
template<typename A, typename B>
using ge = typename priv::GreaterEq<A,B>;

template<typename A, unsigned int power>
using pow = typename priv::Pow<A, power>::value;

template<typename A>
using sqrt = typename priv::Sqrt<A>::value;

template<typename A>
using abs = typename priv::Absolute<A>::value;

}
}

#define RATIONAL_HPP 
#endif /* RATIONAL_HPP */
