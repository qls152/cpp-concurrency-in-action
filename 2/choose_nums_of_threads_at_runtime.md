# 引言

本部分主要总结C++中运行时线程数的选择相关知识

# 选择合适的线程数

C++标准提供了std::thread::hardware_ concurrency()函数，该函数的返回值标识在一个平台上多少个线程可以真正并发执行。

譬如，在一个8核系统上，该函数若成功调用，则返回值为系统的核数，即为8. 如果该函数失败，则返回0，这代表没有可用的信息。

利用该函数，下面实现一个并发的std::accumulate算法

```
#include <thread>
#include <numeric>
#include <vector>

template <typename Iterator, typename T>
struct accumulate_block {
  void operator() (Iterator first, Iterator last, T& result) {
    result = std::accumulate(first, last, result);
  }
};

template <typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init) {
  const unsigned long length = std::distance(first, last);
  if (length == 0) {
    return init;
  }

  const unsigned long min_per_thread = 25;
  const unsigned long max_threads = (length + min_per_thread - 1) / min_per_thread;

  const unsigned long hardware_threads = std::thread::hardware_concurrency();
  const unsigned long num_threads = 
      std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);
  
  const unsigned long block_size = length / num_threads;
  std::vector<T> results(num_threads);
  std::vector<std::thread> threads(num_threads - 1);

  Iterator block_start = first;
  for (unsigned long i = 0; i < (num_threads - 1); ++i) {
	  Iterator block_end = block_start;
	  std::advance(block_end, block_size);
	  threads[i] = std::thread(
		  accumulate_block<Iterator, T>(),
		  block_start, block_end, std::ref(results[i])
	  );
	  block_start = block_end;
  }

  accumulate_block<Iterator, T>()(block_start, last, results[num_threads - 1]);

  for (auto& entry : threads) {
     entry.join();
  }

  return std::accumulate(results.begin(), results.end(), init);

}
```

上述算法利用std::thread::hardware_concurrency()接口限制线程数，且该算法没有考虑异常安全问题。

==============================================================================================

# 标识线程

C++标准提供std::thread::id标识一个线程。 获得该对象可通过如下两个途径：

1. 调用std::thread对象的get_id()成员函数。

2. 通过std::this_thread::get_id()获得当前线程的std::thread::id.

**若std::thread对象没有可执行线程，则get_id()返回默认的std::thread::id对象。**

std::thread::id对象具有如下语义：

1. 可以拷贝和比较

2. 其可以用做关联容器的key

3. 由于C++标准库提供了std::hash<std::thread::id>, 因此其也可以用作unordered 关

联容器

4. 可以将标准输出直接应用于std::thread::id对象




