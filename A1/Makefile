CC = clang
CFLAGS = -Wall -Wpedantic -Wextra -Werror -g

PROG1 = process
PROG2 = thread
SRCS1 = work_process.c
SRCS2 = work_thread.c

#Compiling rules

all: $(PROG1) $(PROG2)
p1: $(PROG1)
p2: $(PROG2)

$(PROG1): $(SRCS1)
	$(CC) $(CFLAGS) -o $(PROG1) $(SRCS1)

$(PROG2): $(SRCS2)
	$(CC) $(CFLAGS) -pthread -o $(PROG2) $(SRCS2)

clean:
	rm -f $(PROG1)
	rm -f $(PROG2)