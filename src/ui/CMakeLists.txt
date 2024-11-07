cmake_minimum_required(VERSION 3.15)
project(ui)

set(UI_SOURCES board.c board.h place-ships.c place-ships.h select-shot-spot.c select-shot-spot.h)
add_library(ui ${UI_SOURCES})