# 引言

正式进入C++并发编程的世界，首先从最简单的 Hello World 开始，编写最简单的并发编程。

关于相应的并发编程代码，会放到code目录下，并同时在文档中进行说明。

# 1 并发Hello World

简单的并发Hello World实现如下：
```
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
```

1. 同非并发编程相比，需要包含<thread> 头文件，管理thread的类和函数均在该类中，保护共享数据的类和函数在其他头文件。

2. 需要提供std::thread构造函数一个**初始化函数**，该函数作为可执行线程的入口。

3. 针对std::thread对象t，调用了其join方法，该方法会阻塞主线程，直到t中线程执行完毕。

# 附注

本部分代码均采用bazel构建，若要构建hello world，可以利用如下命令

bazel build //code/1:all