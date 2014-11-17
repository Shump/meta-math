
#include "Fraction.hpp"

#include <iostream>
#include <string>
#include <sstream>

template<typename Frac>
std::string frac2str() {
  std::stringstream ss;
  ss << Frac::Nom << " / " << Frac::Denom << " (" << Frac::value() << ")";
  return ss.str();
};

template<typename frac1,
         typename frac2,
         template<typename, typename> class Op>
struct BinaryTester {
  using result = typename Op<frac1, frac2>::value;

  static void run(std::string test_name) {
    std::cout << "Running: " << test_name << std::endl;
    std::cout << result::Nom << " / " << result::Denom << " = " << result::value() << std::endl;
  };
};

void test_add() {
  using a = Fraction<1,3>;
  using b = Fraction<1,3>;
  BinaryTester<a,b,FractionAdd>::run("Addition");
};

void test_sub() {
  using a = Fraction<2,3>;
  using b = Fraction<1,3>;
  BinaryTester<a,b,FractionSub>::run("Subtraction");
};

void test_div() {
  using a = Fraction<1,3>;
  using b = Fraction<3,1>;
  BinaryTester<a,b,FractionDiv>::run("Division");
}

void test_mul() {
  using a = Fraction<1,3>;
  using b = Fraction<1,3>;
  BinaryTester<a,b,FractionMul>::run("Multiplication");
};

void test_pow() {
  using a = Fraction<2,1>;
  using result = FractionPow<a, 3>::value;
  std::cout << frac2str<result>() << std::endl;
}

int main() {
  test_add();
  test_sub();
  test_mul();
  test_div();

  test_pow();
}



