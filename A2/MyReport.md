# Assignment 2 Report
---

### Answers

**1. What happens if a signal handler gets invoked when it’s already handling a signal for that same signal/handler? For example, what happens when a process receives a signal for SIGUSR1 when it’s already handling SIGUSR1?**

- Based on the running result of the program, the child process always handle the first SIGUSR received when two of SIGUSR1 are sent from the parent process close together.


**2. What happens if a signal handler gets invoked if the process is already handling a different signal? For example, what happens when a process receives a signal for SIGUSR2 when it’s busy handling SIGUSR1? For example, what happens when a process receives a signal for SIGUSR2 when it’s busy handling SIGUSR1?**

- Based on the running result of the program, the child process always handle SIGUSR2 first when SIGUSR1 and SIGUSR2 are sent from the parent process close together.

---
> Made by Hao Zheng
---
