#pragma once

#include <thread>

class ThreadGuard {
private:
  std::thread& thr_;
public:
  explicit ThreadGuard(std::thread& t) : thr_(t) {}
  ~ThreadGuard() {
	  if (thr_.joinable()) {
		  thr_.join();
	  }
  }
  // 因为std::thread是不可拷贝的，因此需要禁止ThreadGuard
  // 的拷贝构造函数和拷贝赋值函数
  ThreadGuard(const ThreadGuard&) = delete;
  ThreadGuard& operator=(const ThreadGuard&) = delete;
};