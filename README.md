meta-math
=========

Math library for template metaprogramming in c++. Main propose of this library was to create a compile-time floating point data type.

However, just like the run-time type, operations are not guarantied to give exact values because of size limitations in c++ data-types as well as the nature of rational numbers.

Current supported features:
---------------------------

- Floating point representation using rational numbers
- The basic four operators implemented (+, -, *, /)
- All comparison operators implemented (=, !=, <, <=, >, >=)
- sqrt() function implemented

TODO:
-----

- Better precision
  - Add seperate member for whole integers
