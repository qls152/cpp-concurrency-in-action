#pragma once
#include <iostream>

// 本文件中的实现意图：为了构造可调用对象，
// 示例thread的构造函数可接受函数对象，和C++
// 中最令人奇怪的语法解析
class BackgroundTask {
public:
  void operator() () const {
    std::cout << "hello world....\n";
  }
};