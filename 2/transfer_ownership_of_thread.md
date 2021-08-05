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

