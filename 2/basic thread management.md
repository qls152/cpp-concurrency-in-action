# 引言

本部分主要总结，第二章的第一小节：线程管理的基础知识。

# 启动线程

当std::thread 构造完时，便启动了线程。

std::thread的构造函数的**线程初始化函数**可接受如下三个类型：

1. 函数

2. 函数对象

3. lambda表达式(也可看作函数对象)

函数对象可以作为std::thread的构造函数的参数之一，在目录code/2的func_object.h中实现了如下函数对象
```
class BackgroundTask {
public:
  void operator() () const {
    std::cout << "hello world....\n";
  }
};
```

在相应的code/2的basic_thread_manage.cc中，利用该函数对象进行测试，其测试代码如下
```
int main() {
  BackgroundTask f;
  std::thread my_thread(f);
  my_thread.join();

  return 0;
}
```
函数对象会被拷贝至新创建的可执行线程中，然后从那里被调用。**此处，需要保证拷贝结构与原生对象一致，否则可能观察到不一样的结果。**

当使用函数对象作为线程初始化函数时，会碰到C++中最令人奇怪的解析规则，譬如当实现如下代码时

```
std::thread my_thread1(BackgroundTask());
```
此时，利用clang构建时，会报如下Warning

```
warning: parentheses were disambiguated as a function declaration [-Wvexing-parse]
```
在C++中会将该语句解释成为一个my_thread1函数声明，该函数的返回值为std::thread。

针对上述warning，由两种解决方案：

1. 用另一对大括号括住

```
std::thread my_thread1((BackgroundTask()));
```
2. 利用C++中新式初始化规则{}

```
std::thread my_thread1{BackgroundTask()};
```

当然也可直接传入lambda表达式至std::thread的构造函数，譬如如下形式
```
std::thread my_thread([]() {});
```

--------------------------------------------------
--------------------------------------------------

在code/2/basic_thread_manage.cc文件中，如果未调用std::thread::join()接口，则随着主线程退出，std::thread对象会析构，此时运行该程序会出现如下错误
```
libc++abi.dylib: terminating
zsh: abort      ./bazel-bin/code/2/basic_thread_manage
```
这是由于**std::thread的析构函数会调用std::terminate()函数**，该函数会终止程序。

因此，为了避免std::thread析构问题，需要调用std::thread::join()和std::thread::detach()来join或者detach线程。

针对std::thread::join()接口：

**若std::thread已经join后，该thread对象便不再拥有其可执行线程，变成不可join。**

针对std::thread::detach()接口：

**若std::thread已经detach后，该thread对象便不再拥有其可执行线程，变成不可join，其执行线程由C++ Runtime 库管理和回收**

**使用detach接口需要小心对象生命周期问题**

在code/2/detach_obj_lifetime.cc中有如下实现
```
int main() {
  int some_local_state = 0;
  Func my_func(some_local_state);
  std::thread my_thread(my_func);
  my_thread.detach();

  return;
}                     // 此时，新线程可能仍然在跑
```

Func的详细实现可参考code/2/detach_obj_lifetime.h, 其部分实现如下，
```
struct Func {
  int& val_;
  Func(int& val) : val_(val) {}
  void operator() () {
      for(unsigned j = 0; j < 100000; ++j) {
	      std::cout << "output val " << val_;
      }
  }
};
```

因此，当主线程在my_thread线程之前退出，则会出现悬挂指针问题，导致程序出现未定义行为。

# 在异常存在情况下join线程