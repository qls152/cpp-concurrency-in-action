##  引言
本篇主要总结一下并发的概念，以及计算机中存在的并发和利用并发的方式。

##  并发
**概念：两个或者更多分离的动作(行为）同时发生。**

譬如：你可以边唱歌边走路，边打游戏边骂爹等等，这都是现实世界中的并发。也就是同一时间点，不同的行为同时发生。

##  计算机系统中的并发

计算机系统中存在如下两种并发：

**task switching(任务切换):**  伪并发，在单核体系结构中，OS通过任务调度在不同的任务中进行切换，造成并发的假象。

**hardware concurrency(硬件并发):** 真正的并发，在多核体系结构中，OS中的任务可以真正并行的跑在不同的核上，产生真正的并发。

譬如：

有两个任务1，2，在一个单核体系结构的计算机中运行可能如下所示
![](https://img-blog.csdnimg.cn/5ea977f0c3274927baa81e6bf5c376ee.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FsczMxNQ==,size_16,color_FFFFFF,t_70) 

改图来源于C++并发编程实践第一章。

OS会在task1，2中不断进行**上下文切换**，这个与硬件并发相比 会导致cache miss以及延时增加。

当task1，2运行在有两个核的体系结构中时，其可能如下运行
![在这里插入图片描述](https://img-blog.csdnimg.cn/2d24033e512a4b7591d8a5f4db987c6b.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FsczMxNQ==,size_16,color_FFFFFF,t_70)
该图来源于C++并发编程实践第一章。

此时task1，2实现了真正的并发，运行在单独的核上，与单核相比性能有所提升。

此外，如果任务数多于CPU 核数的时候，会产生如下运行可能
![在这里插入图片描述](https://img-blog.csdnimg.cn/38c8a6911e614c54873b354c148a85e9.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FsczMxNQ==,size_16,color_FFFFFF,t_70)

该图来源于C++并发编程第一章。

此时在同一个核上运行两个任务，为了保持并发也会出现**上下文切换**。从而影响并发程序的性能。

##  并发的实现方式
总体而言并发的实现方式可分为以下两类：

 - 单线程/进程（一个进程一个线程，进程级并发）
 - 多线程/进程（单进程多线程，线程级并发）

当然，可以综合上述两者，实现**单进程多线程且进程级并发**

**单线程/进程 并发实现可参考下图所示**

![在这里插入图片描述](https://img-blog.csdnimg.cn/2ef46667530740268de9d0727fc49767.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FsczMxNQ==,size_16,color_FFFFFF,t_70)

该图来源于C++并发编程实践第一章。

进程之间通过IPC相应设施进行通信。

该种并发方式的优缺点如下

**优点：**

 - 更容易实现出安全的并发程序
 - 通过网络连接，可以在不同的机器实现不同的进程

**缺点：**

 - 进程间通过IPC进行通信，进程的启动过程不仅更复杂且也比较慢
 - 固有的性能损失：OS启动进程慢，且需要消耗更多的资源来管理进程

**多线程/单进程 并发方式可参考**

![在这里插入图片描述](https://img-blog.csdnimg.cn/f7986ce30a4145b9bcc642bbc03f1ac7.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FsczMxNQ==,size_16,color_FFFFFF,t_70)

该图片来源于C++并发编程实践第一章。

线程之间通过共享内存进行通信。

这种并发方式的优缺点如下：

**优点：**

 - 性能开销更小，主要由于OS簿记更少
 - 应用启动更快

**缺点：**

 - 需要维护数据的一致性
 
 ##  总结
本篇仅仅总结了一下**并发相关的基本概念**，后续计划逐渐深入C++并发编程实践，总结相关知识点。
