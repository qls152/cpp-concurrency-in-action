# 引言

本部分主要总结 **std::thread**所有权相关知识。

# std::thread所有权

std::thread与std::unique_ptr类似，

1. std::unique_ptr拥有其管理资源的所有权，std::thread拥有其可执行线程的所有权。

2. std::unique_ptr是可移动但非拷贝的类，std::thread同样是可移动非拷贝的类

3. std::unique_ptr可以传递其资源所有劝，std::thread同样可在同类型之间传递其底

层可执行线程的所有权。

假设有三个std::thread对象t1,t2,t3,其可执行线程的转换过程可参考如下代码（详细的过程可参考2_3/owner1.cc):

```
// some_function, some_other_function函数仅仅用来创建可执行线程
   // 3个std::thread对象t1,t2,t3
   std::thread t1(some_function);
   // 将t1对可执行线程的所有权转移给t2
   std::thread t2 = std::move(t1);
   // 将新创建的可执行线程的所有权转移到t1
   t1 = std::thread(some_other_function);

   std::thread t3;
   t3 = std::move(t2);
   
   // t1已经拥有可执行线程的所有权，此时再将其他线程转移到t1会造成
   // std::terminate()被调用
   // 为了程序能正确运行，注释掉改行
   // t1 = std::move(t3);
```

当std::thread对象的可执行线程被转移后，std::thread对象便不再拥有该资源，其变成不可join。

std::unique_ptr对象即可以作为函数的返回值也可以作为函数的形参，同std::unique_ptr类似，std::thread也具备同样的能力。

利用std::thread的该种能力，可以将std::thread对象管理的可执行线程的所有权转移至某个对象中，从而利用RAII手法来进行线程的管理。在目录2_3/scoped_thread.cc中, 有如下实现：
```

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

```

ScopedThread类，构造函数将线程t的可执行线程的所有权转移至内部std::thread对象中，并在构造函数中检查线程是否可join, 如果不可join，则抛出异常。这个可以简化析构函数的实现。

**注：std::thread对象可以转移其可执行线程的所有权，也意味着可以在函数内构造std::thread对象，并将其生命周期扩展至函数外。**

==========================================================================

C++20预计增加std::jthread, 其大体的实现可参考join_thread.cc文件，其部分实现如下

```
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
```

===================================================================

std::thread对象可转移其可执行线程的所有权也可应用在std::vector等容器上，这使得实现线程池成为可能。 下面的例子，是一个将一些线程放入std::vector中，并等待其完成。

```
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

```
将std::thread对象放入std::vector中是向自动化管理线程的初步尝试，这些线程会被作为一组对待。这也是线程池的初步模型。

