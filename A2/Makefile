CC = clang
CFLAGS = -Wall -Wpedantic -Wextra -Werror -g

PROG1 = a1q1
PROG2 = a2q2

#Compiling rules

all: $(PROG1) $(PROG2)
q1: $(PROG1)
q2: $(PROG2)

$(PROG1):
	$(CC) $(CFLAGS) $@.c -o $@

$(PROG2):
	$(CC) $(CFLAGS) $@.c -o $@

clean:
	rm -f $(PROG1)
	rm -f $(PROG2)