#include "detach_obj_lifetime.h"
#include "guard_thread.h"
#include <thread>

int main() {
  int some_local_state = 0;
  int i = 0;
  Func func(some_local_state);
  std::thread t(func);
  ThreadGuard thr(t);
  // try {
  // 	  ++i;
  // } catch(...) {           // ... 此语句捕获所有异常
  //	  t.join();
  // 	  throw;
  // }
  // t.join();

  return 0;
}

