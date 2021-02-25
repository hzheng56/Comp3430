# Assignment 1 Report
---

### Hypothesis

- Processes require longer time than threads to create.

### Experiments

- The following experiments are designed for:
  - running a total number of `<Total processes/threads>` processes or threads, where `<Concurrent processes/threads>` of them at a time.
- Note that the recorded execution time values in the table below are not fixed.

  > That means, you will get a very close but slightly different value next time running a same experiment (unless using larger unit such as second instead of miliseconds).

| Total <br> processes/threads | Concurrent <br> processes/threads | Threads time <br> (microseconds) | Processes time <br> (microseconds) |
|:---------:|:---------:|:---------:|:---------:|
| 100 | 4 | 3471 | 12120 |
| 100 | 8 | 5102 | 11803 |
| 100 | 12 | 3963 | 11334 |
| 100 | 24 | 3712 | 11297 |
| 100 | 32 | 4027 | 5686 |
| 1000 | 4 | 28798 | 110234 |
| 1000 | 8 | 42732 | 67910 |
| 1000 | 12 | 14481 | 34087 |
| 1000 | 24 | 15177 | 30513 |
| 1000 | 32 | 16738 | 28017 |
| 10000 | 4 | 276227 | 452496 |
| 10000 | 8 | 170175 | 335521 |
| 10000 | 12 | 119672 | 286486 |
| 10000 | 24 | 128124 | 279241 |
| 10000 | 32 | 136090 | 246002 |

### Conclusions

**1. Which is faster: threads or processes?**
- From the data of experiments (the table above), it can be seen that running threads is faster than running processes.

**2. Does your result match your hypothesis? Why do you think it does, or why do you think it does not? You can refer to our textbook here in terms of what happens when threads and processes are launched.**
- Yes, the result does match the hypothesis.
- The cost of switching processes is higher than that of switching threads since switching processes requires cutting the page table, and it is often accompanied by page scheduling (this is very slow). The code segment of one process needs to be swapped out in order to swap in the content of a process to be executed.
- Switching threads only needs to save the thread context (related register status and stack information), aka the context switching, which is the most time-consuming part of all costs. Context switching costs much less time than page table query hence running threads is faster than running processes.

**3. Is there a point of diminishing returns on how many concurrent processes/threads are running? That is, when does execution time start to grow very quickly as you increase the number of concurrent processes/threads? Try to explain what might be happening here.**
- The diminishing point is supposed to exist at which number of concurrency is 12, since the CPU property shows that there are 12 CPUs working on the an aviary computer (checked by using `lscpu`).
- The results of experiments show that #concurrency=12 gives the least running time (except #thread=100), then is #concurrency=24 (which is a multiples of 12). I think the reason is that we run the code at a device with built-in 12 CPUs, so this computer can only process 12 threads simultaneously at the same time, and the extra threads still have to wait.
- Based on the results of experiments, I assume both the total #processes/threads and #concurrency will affect the execution time. Using multithreading can improve the number of concurrency and execution speed, however it will slow down each thread individually, and more context switchings could be the primary reason for extra time consumed.

---
> Made by Hao Zheng
---
