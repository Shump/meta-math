



all: test_vector

mega: test_vector test_ratio

test_ratio:
	clang++ -ftemplate-backtrace-limit=0 -std=c++1y -stdlib=libc++ test_ratio.cpp

test_vector:
	clang++ -ftemplate-backtrace-limit=0 -std=c++1y -stdlib=libc++ test_vector.cpp


