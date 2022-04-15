# cpp-concurrency-in-action

计划写一系列《C++ concurrency in action》相关的读书笔记

主要记录一下自己的理解和相应的知识点总结。

本文的代码采用bazel构建:

**bazel build //code/XXX:all**

关于bazel安装可参考：https://docs.bazel.build/versions/4.1.0/install.html

# 参考文献

[How C++ Resolves a Function Call](https://preshing.com/20210315/how-cpp-resolves-a-function-call/)

[Double-Checked Locking is Broken](https://www.cs.cornell.edu/courses/cs6120/2019fa/blog/double-checked-locking/)

[Double-Checked Locking is Fixed In C++11](https://preshing.com/20130930/double-checked-locking-is-fixed-in-cpp11/)

[How can memory_order_relaxed work for incrementing atomic reference counts in smart pointers?](https://stackoverflow.com/questions/27631173/how-can-memory-order-relaxed-work-for-incrementing-atomic-reference-counts-in-sm)

[Acquire and Release Fences Don't Work the Way You'd Expect](https://preshing.com/20131125/acquire-and-release-fences-dont-work-the-way-youd-expect/)

[This Is Why They Call It a Weakly-Ordered CPU](https://preshing.com/20121019/this-is-why-they-call-it-a-weakly-ordered-cpu/)

[An Introduction to Lock-Free Programming](https://preshing.com/20120612/an-introduction-to-lock-free-programming/#sequential-consistency)

[The Purpose of memory_order_consume in C++11](https://preshing.com/20140709/the-purpose-of-memory_order_consume-in-cpp11/)

[The Synchronizes-With Relation](https://preshing.com/20130823/the-synchronizes-with-relation/)

[Weak vs. Strong Memory Models](https://preshing.com/20120930/weak-vs-strong-memory-models/)

[Acquire and Release Semantics](https://preshing.com/20120913/acquire-and-release-semantics/)

[Memory Ordering at Compile Time](https://preshing.com/20120625/memory-ordering-at-compile-time/)

[The Happens-Before Relation](https://preshing.com/20130702/the-happens-before-relation/)

[A Look Back at Single-Threaded CPU Performance](https://preshing.com/20120208/a-look-back-at-single-threaded-cpu-performance/)

[Memory Reordering Caught in the Act](https://preshing.com/20120515/memory-reordering-caught-in-the-act/)

[Locks Aren't Slow; Lock Contention Is](https://preshing.com/20111118/locks-arent-slow-lock-contention-is/)

[Memory Barriers Are Like Source Control Operations](https://preshing.com/20120710/memory-barriers-are-like-source-control-operations/)



[Introduction to thread synchronization](https://www.internalpointers.com/post/introduction-thread-synchronization)

[A gentle introduction to multithreading](https://www.internalpointers.com/post/gentle-introduction-multithreading)

[Understanding memory reordering](https://www.internalpointers.com/post/understanding-memory-ordering)



[C++ Data-Dependency Ordering: Atomics and Memory Model](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2008/n2664.htm)

[Example POWER Implementation for C/C++ Memory Model](http://www.rdrop.com/users/paulmck/scalability/paper/N2745r.2011.03.04a.html)

[Relaxed-Memory Concurrency](https://www.cl.cam.ac.uk/~pes20/weakmemory/)

[Validating Memory Barriers and Atomic Instructions](https://lwn.net/Articles/470681/)

[herb publications](http://www.gotw.ca/publications/)

[Concurrency memory model compiler consequences](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2007/n2338.html)

# 论文

[Memory Barriers: a Hardware View for Software Hackers](https://www.researchgate.net/publication/228824849_Memory_Barriers_a_Hardware_View_for_Software_Hackers)

[Memory Models for C/C++ Programmers](https://par.tuwien.ac.at/teaching/2021s/memory-models.pdf)

[A Better x86 Memory Model: x86-TSO](https://www.cl.cam.ac.uk/~pes20/weakmemory/x86tso-paper.tphols.pdf)

# 书籍

[A Primer on Memory Consistency and Cache Coherence](https://book.douban.com/subject/6829746/)
