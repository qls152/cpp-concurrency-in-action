#include <thread>
#include <iostream>
#include <vector>

void do_something(int i) {
  std::cout << "hello world: " << std::to_string(i) << " \n";
  return;
}

int main() {
  std::vector<std::thread> thread_container;
  int thread_nums = 10;
  for (int i = 0; i < thread_nums; ++i) {
    thread_container.emplace_back(do_something, i);
  }
  
  for (auto& thr : thread_container) {
    thr.join();
  }

  return 0;

}
