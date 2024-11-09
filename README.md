# cango.parallel_group

仅头文件库，用于简化在某个局部创建任务线程然后并行执行的语法。

将如下语法：

```c++
void execute(auto& task1, auto& task2, auto& task3) {
    std::thread thread1(task1);
    std::thread thread2(task2);
    std::thread thread3(task3);
    
    thread1.join();
    thread2.join();
    thread3.join();
}
```

简化为：

```c++
void execute(auto& task1, auto& task2, auto& task3) {
    using namespace cango::parallel_group;
    parallel << group + task1 + task2 + task3;
}
```

语法为：

```c++
parallel << group + task [+ task]...
```

其中 `parallel` 和 `group` 为提示词，提示组合任务会并行执行。  
任务之间通过 `+` 结合，从左到右生成线程，并调用 `std::thread::join` 。  
临时存储线程的数据结构为 `std::list<std::thread>` 。  
