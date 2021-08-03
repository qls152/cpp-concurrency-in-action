#pragma once
#include <iostream>

struct Func {
  int& val_;
  Func(int& val) : val_(val) {}
  void operator() () {
      for(unsigned j = 0; j < 100000; ++j) {
	      std::cout << "output val " << val_;
      }
  }
};