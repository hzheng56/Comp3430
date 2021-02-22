
all: cpu mem threads io

clean:
	rm -f cpu mem threads io

cpu: ../../../Desktop/Comp3430/ostep-code-master/intro/cpu.c common.h
	gcc -o cpu cpu.c -Wall

mem: ../../../Desktop/Comp3430/ostep-code-master/intro/mem.c common.h
	gcc -o mem mem.c -Wall

threads: ../../../Desktop/Comp3430/ostep-code-master/intro/threads.c common.h ../common_threads.h
	gcc -o threads threads.c -Wall -pthread

io: ../../../Desktop/Comp3430/ostep-code-master/intro/io.c common.h
	gcc -o io io.c -Wall

