# A1 README
---

- Name: Hao Zheng
- Student number: 7870389
- Course: COMP3430, section A02/B04
- Instructor: Franklin Bristow
- Assignment: Assignment 1
- Remarks: This is the description file for Assignment 1.

### Hypothesis:

- Processes require longer time than threads to create.

### Concurrency design:

- first, launch the processes/threads in one concurrency (aka the y of processes/threads), then repeat this by x/y times in order to launch x processes/threads eventually.
- Time complexity is supposed to be O(n^2) since 2 for loops are applied.

### Operation procedure on Terminal:

1. Input `make p1` to build `process.c`, `make p2` to build `thread.c`, `make` or `make all` to build both of the c files.
2. Input `process` followed by 2 integers as the arguments representing #processes and #concurrency to run the program `work_process.c`.
3. Input `thread ` followed by 2 integers as the arguments representing #threads and #concurrency to run the program `work_thread.c `.
4. To remove the executables, input `make clean`.
5. The file `MyReport.md` contains my answers for the 3 questions.

---
> Made by Hao Zheng
---
