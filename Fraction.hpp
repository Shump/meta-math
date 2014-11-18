#ifndef FRACTION_HPP

#include <utility>

namespace Fraction {

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

template<long long NN, long long DD>
struct Value {
  static const long long Nom = NN;
  static const long long Denom = DD;    
};

template<typename A> struct Absolute;

template<unsigned int i, long long N, long long D, long long d_limit, long long prec>
struct Round {

};

template<long long N, long long D, long long d_limit, long long prec>
struct Round<0, N, D, d_limit, prec> {
  using value = Value<N,D>;
};

template<long long N, long long D, long long DENOM_LIMIT = 3037000499, long long PRECISION = 1000>
struct Fraction {

  using value_type = long long;

  static const value_type denom_limit = DENOM_LIMIT;
  static const value_type precision = PRECISION;


  static const value_type GCD = gcd<value_type>(N, D);
  static const value_type short_n = N / GCD;
  static const value_type short_d = D / GCD;


  static const bool should_short = short_d > denom_limit;
  static const unsigned int start = should_short ? integer_length(short_d) - 1 : 0;
  using temp_value = typename std::conditional<should_short, 
        typename Round<start, short_n, short_d, denom_limit, precision>::value,
        Value<short_n, short_d>>::type;


  static const value_type Nom = temp_value::Nom;
  static const value_type Denom = temp_value::Denom;

  template<typename U = double>
  static U value() {
    return U(Nom) / U(Denom);
  };
};

template<char const* str>
struct FractionString {
  
};

template<typename A, typename B>
struct Add {
  //TODO: simplify! Might case less instatiations.
  using value = Fraction<A::Nom * B::Denom + B::Nom * A::Denom, A::Denom * B::Denom>;
};

template<typename A, typename B>
struct Sub {
  using value = Fraction<A::Nom * B::Denom - B::Nom * A::Denom, A::Denom * B::Denom>;
};

template<typename A, typename B>
struct Mul {
  using value_type = typename A::value_type;
  static const value_type Nom = A::Nom * B::Nom;
  static const value_type Denom = A::Denom * B::Denom;
  using f = Fraction<Nom, Denom>;
  using value = Fraction<f::Nom, f::Denom>;
};

template<typename A, typename B>
struct Div {
  using value_type = typename A::value_type;
  static const value_type Nom = A::Nom * B::Denom;
  static const value_type Denom = A::Denom * B::Nom;
  using value = Fraction<Nom, Denom>;
};

template<typename A>
struct Negate { 

};

template<typename A>
struct Absolute {
  using value_type = typename A::value_type;
  static const value_type Nom = A::Nom < 0 ? -A::Nom : A::Nom;
  static const value_type Denom = A::Denom < 0 ? -A::Denom : A::Denom;
  
  using value = Fraction<Nom, Denom>;
};

template<typename A, typename x, unsigned int iteration>
struct Sqrt_ {
  using div = typename Div<A, x>::value;
  using add = typename Add<x, div>::value;
  using x_ = typename Mul<Fraction<1,2>, add>::value;
  using value = typename Sqrt_<A, x_, iteration - 1>::value;
};

template<typename A, typename x>
struct Sqrt_<A, x, 0> {
  using value = x;
};

template<typename A, unsigned int iterations = 20>
struct Sqrt {
  using x = typename Div<A, Fraction<2,1>>::value;
  using value = typename Sqrt_<A, x, iterations>::value;
};

template<typename A, unsigned int power>
struct Pow {
  using value = typename Mul<A, typename Pow<A, power - 1>::value>::value;
};

template<typename A>
struct Pow<A, 0> {
  using value = Fraction<1,1>;
};


}

#define FRACTION_HPP 
#endif /* FRACTION_HPP */
