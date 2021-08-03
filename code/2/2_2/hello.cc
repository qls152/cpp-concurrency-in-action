#include <thread>
#include <string>
#include <iostream>

void f(int i, const std::string& hello) {
  std::cout << hello << ". " << std::to_string(i) << "\n";
}

int main() {
  std::thread t(f, 3," hello");
  t.join();
  return 0;
}