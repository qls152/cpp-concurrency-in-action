#include <thread>

#include "func_object.h"

int main() {
  BackgroundTask f;
  std::thread my_thread(f);
  // 此处为了实验C++中令人奇怪的语法解析
  // std::thread my_thread1(BackgroundTask());
  my_thread.join();
  //std::thread::join(my_thread)
  return 0;
}