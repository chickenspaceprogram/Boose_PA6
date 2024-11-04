cmake_minimum_required(VERSION 3.29)
project(Boose_PA6 C)

set(CMAKE_C_STANDARD 11)

add_subdirectory(../src/ctty ctty)

add_executable(Boose_PA6 
        ../src/main.c
        ../src/ui/board.h
        ../src/ui/board.c
        ../src/ui/select-shot-spot.c
        ../src/ui/select-shot-spot.h
        ../src/ui/place-ships.c
        ../src/ui/place-ships.h
        ../src/rand.c
        ../src/rand.h
        ../src/ui/menu.h
        ../src/ui/menu.c
)
