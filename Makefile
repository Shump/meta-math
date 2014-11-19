



all: tests

tests:
	clang++ -ftemplate-backtrace-limit=0 -std=c++1y -stdlib=libc++ test_ratio.cpp

