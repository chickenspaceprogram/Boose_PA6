cmake_minimum_required(VERSION 3.15)
project(Boose_PA6 C)

set(CMAKE_C_STANDARD 11)
add_subdirectory(../src/ctty ./ctty)
add_subdirectory(../src/ui ./ui)
add_executable(Boose_PA6 
        ../src/main.c
        ../src/rand.c
        ../src/rand.h
        ../src/battleship.c
        ../src/battleship.h
        ../src/log.c
        ../src/log.h
        ../src/board-spot-checking.c
        ../src/board-spot-checking.h
        ../src/ai.h
        ../src/ai.c
)
target_link_libraries(Boose_PA6 ctty ui)
