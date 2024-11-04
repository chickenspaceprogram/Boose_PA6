cmake_minimum_required(VERSION 3.29)
project(ctty_ansi C)

set(CMAKE_C_STANDARD 11)
add_library(
    colors.c
    colors.h
    cursor.c
    cursor.h
    erase.h
    text-modes.h
)