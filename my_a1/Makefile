CC = clang
CFLAGS = -g -Wall -Wpedantic -Wextra -Werror

PROG1 = process
PROG2 = thread
SRCS1 = work_process.c
SRCS2 = work_thread.c

#Compiling rules

all: $(PROG1) $(PROG2)

$(PROG1): $(SRCS1)
	$(CC) $(CFLAGS) -o $(PROG1) $(SRCS1)

$(PROG2): $(SRCS2)
	$(CC) $(CFLAGS) -pthread -o $(PROG2) $(SRCS2)

clean:
	rm -f $(PROG1)
	rm -f $(PROG2)