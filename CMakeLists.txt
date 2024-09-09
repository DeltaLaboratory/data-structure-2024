cmake_minimum_required(VERSION 3.29)
project(csorts C)

set(CMAKE_C_STANDARD 11)

add_executable(csorts
        selection/selectionSort.c
        insertion/insertionSort.c
        bubble/bubbleSort.c
        shell/shellSort.c)
