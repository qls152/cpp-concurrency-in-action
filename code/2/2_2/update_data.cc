#include <thread>
#include <iostream>

struct WidgetData {
  int inner_{0};

  void set_inner_val(int val) {
    inner_ = val;
  }
};

// 注意：该例子只是为了演示，在实际多线程中这样做是不安全的
void f(int val, WidgetData& data) {
  data.set_inner_val(val);
}

int main() {
  WidgetData data;
  data.set_inner_val(10);
  // 想要在线程t中通过f的引用修改data
  // 该版本构建会报错
  // std::thread t(f, 100, data);

  // 利用std::ref封装data，此时构建能成功
  std::thread t(f, 100, std::ref(data));
  t.join();
  std::cout << "data inner: " << data.inner_ << "\n";
  return 0;
}