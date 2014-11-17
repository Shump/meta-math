
#include "Fraction.hpp"

#include <iostream>
#include <string>

template<long long N1, long long D1,
         long long N2, long long D2,
         template<typename A, typename B> class Op>
struct BinaryTester {
  using frac1 = Fraction<N1, D1>;
  using frac2 = Fraction<N2, D2>;
  using result = typename Op<frac1, frac2>::value;

  static void run(std::string test_name) {
    std::cout << "Running: " << test_name << std::endl;
    std::cout << result::Nom << " / " << result::Denom << " = " << result::value() << std::endl;
  };

};

void test_add() {
  BinaryTester<1,3,1,3,FractionAdd>::run("Addition");
};

void test_sub() {
  BinaryTester<2,3,1,3,FractionSub>::run("Subtraction");
};

void test_div() {
  BinaryTester<1,3,3,1,FractionDiv>::run("Division");
}

void test_mul() {
  BinaryTester<1,3,1,3,FractionMul>::run("Multiplication");
};

int main() {
  test_add();
  test_sub();
  test_mul();
  test_div();
}



