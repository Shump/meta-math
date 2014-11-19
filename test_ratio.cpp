
#include "Rational.hpp"

#include <iostream>
#include <string>
#include <sstream>

#include <type_traits>

#include <cmath>

using namespace mmath;

template<typename Frac>
std::string frac2str() {
  std::stringstream ss;
  ss << Frac::Nom << " / " << Frac::Denom << " [" << Frac::value() << "]";
  return ss.str();
};

template<typename frac1,
         typename frac2,
         template<typename, typename, bool b = false> class Op,
         typename expected>
struct BinaryTester {
  using result = typename Op<frac1, frac2>::value;

  static_assert(ratio::priv::Equal<result, expected>::value, "Result is not equal expected value.");

  static void run(std::string op_name) {
    std::cout << frac2str<frac1>() << " " << op_name << " " << frac2str<frac2>() << " = " << frac2str<result>() << std::endl;
  };
};

template<typename frac1,
         typename frac2,
         template<typename, typename> class Op,
         bool expected>
struct CompareTester {

  static const bool value = Op<frac1, frac2>::value;

  static_assert(value == expected, "Truth value wrong.");

  static void run(std::string op_name) {
    std::cout << frac2str<frac1>() << " " << op_name << " " << frac2str<frac2>() << " = " << value << std::endl;
  };
};

void test_add() {
  std::cout << "Addition tests:" << std::endl;

  BinaryTester<ratio::priv::Rational<1,3>, ratio::priv::Rational<1,3>, ratio::priv::Add, ratio::priv::Rational<2,3>>::run("+");
  BinaryTester<ratio::priv::Rational<4,1>, ratio::priv::Rational<15,1>, ratio::priv::Add, ratio::priv::Rational<19,1>>::run("+");
  BinaryTester<ratio::priv::Rational<195,642>, ratio::priv::Rational<76,34>, ratio::priv::Add, ratio::priv::Rational<195*34+76*642,642*34>>::run("+");

  std::cout << std::endl;
};

void test_sub() {
  std::cout << "Subtraction tests:" << std::endl;

  BinaryTester<ratio::priv::Rational<2,3>, ratio::priv::Rational<1,3>, ratio::priv::Sub, ratio::priv::Rational<1,3>>::run("-");

  std::cout << std::endl;
};

void test_div() {
  std::cout << "Division tests:" << std::endl;

  BinaryTester<ratio::priv::Rational<1,3>, ratio::priv::Rational<3,1>, ratio::priv::Div, ratio::priv::Rational<1,9>>::run("/");

  std::cout << std::endl;
}

void test_mul() {
  std::cout << "Division tests:" << std::endl;

  BinaryTester<ratio::priv::Rational<1,3>, ratio::priv::Rational<1,3>, ratio::priv::Mul, ratio::priv::Rational<1,9>>::run("*");

  std::cout << std::endl;
};

void test_equal() {
  std::cout << "Equal tests:" << std::endl;

  CompareTester<ratio::priv::Rational<1,3>, ratio::priv::Rational<2,6>, ratio::priv::Equal, true>::run("==");
  CompareTester<ratio::priv::Rational<2,5>, ratio::priv::Rational<3,7>, ratio::priv::Equal, false>::run("==");

  std::cout << std::endl;
}

void test_not_equal() {
  std::cout << "Not equal tests:" << std::endl;

  CompareTester<ratio::priv::Rational<1,3>, ratio::priv::Rational<2,6>, ratio::priv::NotEqual, false>::run("==");
  CompareTester<ratio::priv::Rational<2,5>, ratio::priv::Rational<3,7>, ratio::priv::NotEqual, true>::run("==");

  std::cout << std::endl;
}

template<template<typename, typename> class Op, bool expected>
using less = CompareTester<ratio::priv::Rational<1,7>, ratio::priv::Rational<1,6>, Op, expected>;

template<template<typename, typename> class Op, bool expected>
using equal = CompareTester<ratio::priv::Rational<3,5>, ratio::priv::Rational<15,25>, Op, expected>;

template<template<typename, typename> class Op, bool expected>
using greater = CompareTester<ratio::priv::Rational<2,3>, ratio::priv::Rational<6,10>, Op, expected>;

void test_less() {
  std::cout << "Less than tests:" << std::endl;

  less<ratio::priv::Less, true>::run("<");
  equal<ratio::priv::Less, false>::run("<");
  greater<ratio::priv::Less, false>::run("<");

  std::cout << std::endl;
}

void test_less_equal() {
  std::cout << "Less or equal than tests:" << std::endl;

  less<ratio::priv::LessEq, true>::run("<=");
  equal<ratio::priv::LessEq, true>::run("<=");
  greater<ratio::priv::LessEq, false>::run("<=");

  std::cout << std::endl;
}

void test_greater() {
  std::cout << "Greater than tests:" << std::endl;

  less<ratio::priv::Greater, false>::run(">");
  equal<ratio::priv::Greater, false>::run(">");
  greater<ratio::priv::Greater, true>::run(">");

  std::cout << std::endl;
}

void test_greater_equal() {
  std::cout << "Grater or equal than tests:" << std::endl;

  less<ratio::priv::GreaterEq, false>::run(">=");
  equal<ratio::priv::GreaterEq, true>::run(">=");
  greater<ratio::priv::GreaterEq, true>::run(">=");

  std::cout << std::endl;
}

void test_pow() {
  using a = ratio::priv::Rational<2,1>;
  using result = ratio::priv::Pow<a, 2>::value;
  std::cout << frac2str<a>() << " to the power of 2: ";
  std::cout << frac2str<result>() << std::endl;
}

template<long long N, long long D>
void __sqrt__() {
  using r = ratio::priv::Rational<N,D>;
  using result = typename ratio::priv::Sqrt<r, 5>::value;
  std::cout << "sqrt(" << frac2str<r>() << ") = ";
  std::cout << frac2str<result>() << " \t(" << std::sqrt(double(N) / double(D)) << ")" << std::endl;
};

void test_sqrt() {
  std::cout << "Squareroot tests:" << std::endl;

  __sqrt__<100,1>();
  __sqrt__<3,1>();
  __sqrt__<1,3>();
  __sqrt__<3,25>();

  std::cout << std::endl;
}

template<typename frac, typename expected>
struct AbsTester {
  using result = typename ratio::priv::Absolute<frac>::value;

  static_assert(ratio::priv::Equal<result, expected>::value, "Incorrect absolute valie");

  static void run() {
    std::cout << "abs(" << frac2str<frac>() << ") = " << frac2str<result>() << std::endl;
  };
};

void test_abs() {
  std::cout << "Absolute tests:" << std::endl;

  AbsTester<ratio::priv::Rational<3,7>, ratio::priv::Rational<3,7>>::run();
  AbsTester<ratio::priv::Rational<-5,9>, ratio::priv::Rational<5,9>>::run();
  AbsTester<ratio::priv::Rational<-13,-6>, ratio::priv::Rational<13,6>>::run();
  AbsTester<ratio::priv::Rational<1,-25>, ratio::priv::Rational<1,25>>::run();

  std::cout << std::endl;
}

void test_values() {
  std::cout << "Rational values tests:" << std::endl;

  std::cout << frac2str<ratio::priv::Rational<0, 23456>>() << std::endl;
  std::cout << frac2str<ratio::priv::Rational<-90, 195>>() << std::endl;
  std::cout << frac2str<ratio::priv::Rational<-1078, -63>>() << std::endl;
  std::cout << frac2str<ratio::priv::Rational<12, -2079>>() << std::endl;

  std::cout << frac2str<ratio::priv::Rational<1, 1>>() << std::endl;
  std::cout << frac2str<ratio::priv::Rational<-1, 1>>() << std::endl;
  std::cout << frac2str<ratio::priv::Rational<1, -1>>() << std::endl;
  std::cout << frac2str<ratio::priv::Rational<-1, -1>>() << std::endl;

  std::cout << std::endl;

}

int main() {
  std::cout << std::endl;

  test_values();

  test_add();
  test_sub();
  test_mul();
  test_div();

  test_equal();
  test_not_equal();

  test_less();
  test_less_equal();
  test_greater();
  test_greater_equal();

  test_pow();
  test_sqrt();

  test_abs();

}



