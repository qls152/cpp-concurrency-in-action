#include <iostream>
#include <thread>

class JoinThread {
private:
  std::thread thread_;

public:
  JoinThread() noexcept = default;
  template <typename Callable, typename... Args>
  explicit JoinThread(Callable&& func, Args&& ... args)
      : thread_(std::forward<Callable>(func), std::forward<Args>(args)...) {}

  explicit JoinThread(std::thread t) noexcept 
      : thread_(std::move(t)) {

  }

  JoinThread(JoinThread&& other) noexcept
      : thread_(std::move(other.pthread_)) {

  }

  JoinThread& operator=(JoinThread&& other) noexcept {
      if (joinable()) {
	  join();
      }
      thread_ = std::move(other.thread_);
      return *this;
  }

  JoinThread& operator=(std::thread other) noexcept {
      if (joinable()) {
	  join();
      }

      thread_ = std::move(other);
      return *this;
  }

  ~JoinThread() noexcept {
      if (joinable()) {
	  join();
      }
  }

  void swap(JoinThread& other) noexcept {
      thread_.swap(other.thread_);
  }

  std::thread::id get_id() const noexcept {
      return thread_.get_id();
  }

  bool joinable() const noexcept {
     return thread_.joinable();
  }

  void join() {
      thread_.join();
  }

  void detach() {
      thread_.detach();
  }

  std::thread& as_thread() noexcept {
      return thread_;  
  }

  const std::thread& as_thread() const noexcept {
      return thread_;
  }


};