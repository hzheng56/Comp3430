# Assignment 2 Report
---

### Answers

**1. What happens if a signal handler gets invoked when it’s already handling a signal for that same signal/handler? For example, what happens when a process receives a signal for SIGUSR1 when it’s already handling SIGUSR1?**

- Based on the running result of the program, only 1 of the 2 `SIGUSR1` signals are handled. The child process always handle the first `SIGUSR1` received when two of `SIGUSR1` are sent from the parent process close together.
- My viewpoint: If a process receives a signal (i.e. `SIGUSR1`) that is identical to the signal that it’s already handling, then the signal arrives later will be sent to SIG_DFL.
- Quote from `man`: `when a handler that was established using signal() was invoked by the delivery of a signal, the disposition of the signal would be reset to SIG_DFL, and the system did not block delivery of further instances of the signal.`

**2. What happens if a signal handler gets invoked if the process is already handling a different signal? For example, what happens when a process receives a signal for SIGUSR2 when it’s busy handling SIGUSR1? For example, what happens when a process receives a signal for SIGUSR2 when it’s busy handling SIGUSR1?**

- Based on the running result of the program, both signals of `SIGUSR1` and `SIGUSR2` are handled. However, the child process always handle `SIGUSR2` first when `SIGUSR1` and `SIGUSR2` are sent from the parent process close together.
- My viewpoint: Signals are not queued, instead are stack structure (aka FILO). If a process recieves a different signal (i.e. `SIGUSR2`) when it's already handling a signal (i.e. `SIGUSR1`), then the new arrived signal will be on the top of the stack, hence it will be handled first.

---
> Made by Hao Zheng
---
