cmake_minimum_required(VERSION 3.23)
project(my_cal C)

set(CMAKE_C_STANDARD 11)

add_executable(my_cal
        main.c
        infix_to_postfix.c
        evaluate_postfix.c)
