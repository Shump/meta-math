#ifndef FRACTION_HPP

#include <utility>

template<typename T>
constexpr T gcd(T a, T b) {
  return (b == 0 ? a : gcd<T>(b, a % b));
} 

template<long long N, long long D>
struct Fraction {

  using value_type = long long;

  static const value_type GCD = gcd<value_type>(N, D);

  static const value_type Nom = N / GCD;
  static const value_type Denom = D / GCD;

  template<typename U = double>
  static U value() {
    return U(Nom) / U(Denom);
  };
};

template<char const* str>
struct FractionString {
  
};

template<typename A, typename B>
struct FractionAdd {
  //TODO: simplify! Might case less instatiations.
  using value = Fraction<A::Nom * B::Denom + B::Nom * A::Denom, A::Denom * B::Denom>;
};

template<typename A, typename B>
struct FractionSub {
  using value = Fraction<A::Nom * B::Denom - B::Nom * A::Denom, A::Denom * B::Denom>;
};

template<typename A, typename B>
struct FractionMul {
  using value_type = typename A::value_type;
  static const value_type Nom = A::Nom * B::Nom;
  static const value_type Denom = A::Denom * B::Denom;
  using f = Fraction<Nom, Denom>;
  using value = Fraction<f::Nom, f::Denom>;
};

template<typename A, typename B>
struct FractionDiv {
  using value_type = typename A::value_type;
  static const value_type Nom = A::Nom * B::Denom;
  static const value_type Denom = A::Denom * B::Nom;
  using value = Fraction<Nom, Denom>;
};

template<typename A, typename x, unsigned int iteration>
struct Sqrt_ {
  using div = typename FractionDiv<A, x>::value;
  using add = typename FractionAdd<x, div>::value;
  using x_ = typename FractionMul<Fraction<1,2>, add>::value;
  using value = typename Sqrt_<A, x_, iteration - 1>::value;
};

template<typename A, typename x>
struct Sqrt_<A, x, 0> {
  using value = x;
};

template<typename A, unsigned int iterations = 20>
struct FractionSqrt {
  using x = typename FractionDiv<A, Fraction<2,1>>::value;
  using value = Sqrt_<A, x, iterations>;
};

template<typename A, unsigned int power>
struct FractionPow {
  using value = typename FractionMul<A, typename FractionPow<A, power - 1>::value>::value;
};

template<typename A>
struct FractionPow<A, 0> {
  using value = Fraction<1,1>;
};

template<typename A, typename B>
struct FractionEqual {
  using value_type = typename A::value_type;
  static const value_type a_nom = A::Nom * B::Denom;
  static const value_type b_nom = B::Nom * A::Denom;
  static const bool value = a_nom == b_nom;
};


#define FRACTION_HPP 
#endif /* FRACTION_HPP */
