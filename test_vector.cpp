
#include "Rational.hpp"
#include "Vector.hpp"

#include <iostream>
#include <sstream>
#include <string>

using namespace mmath;

template<typename v>
std::string vec2str() {
  std::stringstream ss;
  ss << "[ " << v::x::value() << ", " << v::y::value() << ", " << v::z::value() << " ]";
  
  return ss.str();
};

using one_tenth = ratio::rational<1,10>;
using one = ratio::rational<1,1>;
using two = ratio::rational<2,1>;
using three = ratio::rational<3,1>;
using four = ratio::rational<4,1>;

using one_tenths = vec::vector<one_tenth, one_tenth, one_tenth>;
using one_two_three = vec::vector<one, two, three>;
using three_two_one = vec::vector<three, two, one>;
using ones = vec::vector<one, one, one>;
using twos = vec::vector<two, two, two>;
using threes = vec::vector<three, three, three>;

template<typename A, typename B, template<typename, typename> class Op>
void tester(std::string op_char) {
  std::cout << vec2str<A>() << " " << op_char << " " << vec2str<B>() << " = "
    << vec2str<Op<A,B>>() << std::endl;
}

template<template<typename,typename> class Op>
struct test_suit {

  static void run(std::string op_name, std::string op_char) {
    
    std::cout << op_name << " tests:" << std::endl;

    tester<one_tenths, one_tenths, Op>(op_char);
    tester<ones, one_tenths, Op>(op_char);
    tester<one_tenths, ones, Op>(op_char);
    tester<twos, ones, Op>(op_char);
    tester<ones, twos, Op>(op_char);
    tester<one_two_three, one_tenths, Op>(op_char);
    tester<one_two_three, three_two_one, Op>(op_char);
    tester<three_two_one, one_two_three, Op>(op_char);

    std::cout << std::endl;
  }

};

void test_eq() {
  std::cout << "Equal tests:" << std::endl;

  std::cout << vec::eq<ones, vec::div<threes, threes>>::value << std::endl;
  std::cout << vec::eq<ones, threes>::value << std::endl;

  std::cout << std::endl;
}

void test_neq() {
  std::cout << "Not equal tests:" << std::endl;

  std::cout << vec::neq<ones, vec::div<threes, threes>>::value << std::endl;
  std::cout << vec::neq<ones, threes>::value << std::endl;

  std::cout << std::endl;
}

int main() {
  std::cout << std::endl;

  test_suit<vec::add>::run("Addition", "+");
  test_suit<vec::sub>::run("Subtraction", "-");
  test_suit<vec::mul>::run("Multiplication", "*");
  test_suit<vec::div>::run("Divistion", "/");

  test_eq();
  test_neq();

}




