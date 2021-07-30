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

