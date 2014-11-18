
#include "Fraction.hpp"

#include <iostream>
#include <string>
#include <sstream>

#include <type_traits>

template<typename Frac>
std::string frac2str() {
  std::stringstream ss;
  ss << Frac::Nom << " / " << Frac::Denom << " [" << Frac::value() << "]";
  return ss.str();
};

template<typename frac1,
         typename frac2,
         template<typename, typename> class Op,
         typename expected>
struct BinaryTester {
  using result = typename Op<frac1, frac2>::value;

  static_assert(Fraction::Equal<result, expected>::value, "Result is not equal expected value.");

  static void run(std::string op_name) {
    std::cout << frac2str<frac1>() << " " << op_name << " " << frac2str<frac2>() << " = " << frac2str<result>() << std::endl;
  };
};

void test_add() {
  std::cout << "Addition tests:" << std::endl;

  BinaryTester<Fraction::Fraction<1,3>, Fraction::Fraction<1,3>, Fraction::Add, Fraction::Fraction<2,3>>::run("+");
  BinaryTester<Fraction::Fraction<4,1>, Fraction::Fraction<15,1>, Fraction::Add, Fraction::Fraction<19,1>>::run("+");
  BinaryTester<Fraction::Fraction<195,642>, Fraction::Fraction<76,34>, Fraction::Add, Fraction::Fraction<195*34+76*642,642*34>>::run("+");

  std::cout << std::endl;
};

void test_sub() {
  std::cout << "Subtraction tests:" << std::endl;

  BinaryTester<Fraction::Fraction<2,3>, Fraction::Fraction<1,3>, Fraction::Sub, Fraction::Fraction<1,3>>::run("-");

  std::cout << std::endl;
};

void test_div() {
  std::cout << "Division tests:" << std::endl;

  BinaryTester<Fraction::Fraction<1,3>, Fraction::Fraction<3,1>, Fraction::Div, Fraction::Fraction<1,9>>::run("/");

  std::cout << std::endl;
}

void test_mul() {
  std::cout << "Division tests:" << std::endl;

  BinaryTester<Fraction::Fraction<1,3>, Fraction::Fraction<1,3>, Fraction::Mul, Fraction::Fraction<1,9>>::run("*");

  std::cout << std::endl;
};

void test_pow() {
  using a = Fraction::Fraction<2,1>;
  using result = Fraction::Pow<a, 2>::value;
  std::cout << frac2str<a>() << " to the power of 2: ";
  std::cout << frac2str<result>() << std::endl;
}

template<int i>
void temp() {
  using a = Fraction::Fraction<3,10>;
  using result = typename Fraction::Sqrt<a, i>::value;
  std::cout << "sqrt of " << frac2str<a>() << ": ";
  std::cout << frac2str<result>() << std::endl;
};

void test_sqrt() {
  temp<3>();
}

int main() {
  std::cout << std::endl;
  test_add();
  test_sub();
  test_mul();
  test_div();

  test_pow();
  test_sqrt();
}



