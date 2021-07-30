#include "detach_obj_lifetime.h"
#include <thread>

int main() {
  int some_local_state = 0;
  Func my_func(some_local_state);
  std::thread my_thread(my_func);
  my_thread.detach();

  return 0;
}                     // 此时，新线程可能仍然在跑