cmake_minimum_required(VERSION 3.15)
project(ui)

set(UI_SOURCES 
    place-ships.c place-ships.h 
    board.c board.h 
    select-shot-spot.c select-shot-spot.h 
    space-print-info.h)

add_library(ui ${UI_SOURCES})