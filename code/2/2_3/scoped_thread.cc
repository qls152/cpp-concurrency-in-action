#include <iostream>
#include <thread>

class ScopedThread {
private:
  std::thread personal_thread_;
public:
  // 将线程t的可执行线程所有权转移至personal_thread_
  explicit ScopedThread(std::thread&& t) 
      : personal_thread_(std::move(t)) {
    if (!personal_thread_.joinable()) {
        throw std::logic_error("No thread");
    }
  }
  /*
  explicit ScopedThread(std::thread t) 
      : personal_thread_(std::move(t)) {
    if (!personal_thread_.joinable()) {
        throw std::logic_error("No thread");
    }
  }*/

  ~ScopedThread() {
    personal_thread_.join();
  }

  ScopedThread(const std::thread&) = delete;
  ScopedThread& operator=(const std::thread&) = delete;
};

void hello(int i) {
  std::cout << "hello world : " << std::to_string(i) << "\n";
} 

int main() {
    std::thread t{hello, 5};
    ScopedThread st(std::move(t));

    return 0;
}