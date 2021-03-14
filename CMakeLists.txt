cmake_minimum_required(VERSION 3.17)
project(Comp3430 C)

set(CMAKE_C_STANDARD 11)

include_directories(.
		A1
)

add_executable(Comp3430
		A2/a2q1.c
#		A2/q1.c
#		A1/work_process.c
)
