cmake_minimum_required(VERSION 3.29)
project(Boose_PA6 C)

set(CMAKE_C_STANDARD 11)

add_executable(Boose_PA6 src/main.c
        src/board.h
        src/ctty/screen.h
        src/ctty/keyselect.h
        src/ctty/keypress-codes.h
        src/ctty/keypress.h
        src/board.c
        src/ctty/keyselect.c
        src/ctty/keypress.c
        src/coord.h
        src/coord.c
        src/ctty/ansi/colors.h
        src/ctty/ansi/cursor.c
        src/ctty/ansi/cursor.h
        src/ctty/ansi/erase.h
        src/ctty/ansi/text-modes.h
)
