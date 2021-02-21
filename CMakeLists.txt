cmake_minimum_required(VERSION 3.17)
project(Comp3430 C)

set(CMAKE_C_STANDARD 11)

include_directories(.
		my_a1
)

add_executable(Comp3430
	#chpt2/t0.c
		#my_a1/work_process.c
		my_a1/work_thread.c
)
