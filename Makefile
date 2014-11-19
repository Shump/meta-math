



all: tests

tests:
	clang++ -std=c++1y -stdlib=libc++ ratio_test.cpp

