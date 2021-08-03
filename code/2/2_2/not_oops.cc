#include <thread>
#include <string>
#include <iostream>

void f(int i, const std::string& hello) {
  std::cout << hello << ". " << std::to_string(i) << "\n";
}

int main() {
  int some_param;
  char buffer[1024]; 
  sprintf(buffer, "%ld", some_param);
  std::thread t(f, 3, buffer);
  t.detach();

  return 0;
}