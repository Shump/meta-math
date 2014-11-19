
#include "Fraction.hpp"

#include <iostream>



int main() {

  using q = Fraction::Fraction<1234567, 3037000499 * 3>;

  std::cout << q::Nom << " " << q::Denom << " " << q::value() << std::endl;


};







