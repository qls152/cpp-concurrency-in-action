#include <iostream>
#include <thread>

void some_function() {
  std::cout << "some function.........\n";
}

void some_other_function() {
  std::cout << "some other function.....\n";
}

int main() {
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

   if (t1.joinable()) {
      t1.join();
   }

   if (t3.joinable()) {
      t3.join();   
   }

   return 0;
}