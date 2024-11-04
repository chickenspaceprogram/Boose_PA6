cmake_minimum_required(VERSION 3.29)
project(ctty C)

set(CMAKE_C_STANDARD 11)

add_subdirectory(ansi)

add_library(
    keypress-codes.h
    keypress.c
    keypress.h
    keyselect.h
    keyselect.c
    screen.h
)

