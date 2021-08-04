# 引言

本部分为第二章第二小节：传递参数至线程函数中。

本部分的的代码位置：code/2/2_2 目录下，且在总结中也会讲解部分代码实现。

# 传递参数至线程函数

std::thread构造函数可以接受：

1. 函数对象

2. 普通函数

3. 类成员函数

**相应函数的参数可以通过std::thread构造函数作为媒介传递至相应的线程函数。**

下面是一个向普通函数传递参数的例子

```
void f(int i, const std::string& hello) {
  std::cout << hello << ". " << std::to_string(i) << "\n";
}

std::thread t(f, 3," hello");
```
详细代码可参考相应目录下面的hello.cc文件。

函数f有两个参数，其类型分别为int，const std::string&. 

std::thread对象t拥有一个可执行线程，且该线程的入口函数为f，通过std::thread的构造函数传入一个int 3和一个const char*.

**std::thread构造函数会将相应的参数拷贝至可执行线程存储空间中.**

因此，当线程运行时，const char* 会转换成std::string. 该线程可能导致**悬挂指针，产生未定义行为.**

为了更好的理解上述行为，可参考如下示例（其详细代码可参考相应目录下的not_oops.cc)

```

int main() {
  int some_param;
  char buffer[1024]; 
  sprintf(buffer, "%ld", some_param);
  std::thread t(f, 3, buffer);
  t.detach();

  return 0;
}
```
当主线程退出后，可能线程t继续在运行，此时便会产生未定义行为。

原因：

**std::thread会拷贝参数到可执行线程存储中，因此上述会将char\* 拷贝至线程存储中，当线程运行时，会将char\* 转换为std::string, 而在转换的时候可能main线程已经退出。**

解决方案：只需将上述代码的buffer参数变为std::string(buffer), 在std::thread构造函数中，提前转换为string。

=====================================================================

有时候你可能需要在可执行线程中修改某个变量的值，换句话说，你想将函数f声明如下形式
```
void f(int val, WidgetData& data);
```

其详细使用过程如下(详细代码可参考相应目录下的update_data.cc文件)

```
int main() {
  WidgetData data;
  data.set_inner_val(10);
  // 想要在线程t中通过f的引用修改data
  std::thread t(f, 100, data);
  t.join();
  std::cout << "data inner: " << data.inner_ << "\n";
  return 0;
}
```
虽然函数f的第二个参数为WidgetData的引用，但std::thread的构造函数只会拷贝相应的参数，传递到可执行线程中的变量是WidgetData对像的副本。因此无法更改data。

**此外，构建update_data.cc会出错，这是因为std::thread会将拷贝的对象作为右值传递到可执行线程函数,而线程函数的参数为非const引用，故编译器报错.**

解决方案：利用std::ref封装data，既能使构建成功，也会改变相应参数值，具体代码可参考相应目录中的update_data.cc文件。

=====================================================================

std::thread的构造函数也能接受**类成员函数**。 你只需要传递类成员函数的指针和类对象指针作为第一，第二个参数即可。

如下例子所示(具体代码可参考member_func.cc):

```
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
  return;
}
```

上述代码会在线程t中执行myx.do_something()。类成员函数也可以带有形参列表，只需要将参数依次放在std::thread构造函数相应位置即可。

<font color=red> =====================================================================</font>

std::thread构造函数可以接受的参数也包括右值，当某个对象仅仅具有移动语义时，此时需要利用std::move将对象传入std::thread构造函数。


