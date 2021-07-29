#include <thread>
#include <iostream>

void print() {
  std::cout << "Hello world...\n";
}

int main() {
  std::thread t(print);
  t.join();

  return 0;
}