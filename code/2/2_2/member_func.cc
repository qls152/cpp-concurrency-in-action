#include <thread>
#include <iostream>

class X {
public:
  void do_something() {
    std::cout << "do something.............\n";
  }
};

int main() {
  X myx;
  std::thread t(&X::do_something, &myx);
  t.join();
  return 0;
}