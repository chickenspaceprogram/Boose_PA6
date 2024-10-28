cmake_minimum_required(VERSION 3.30)

project(Boose_PA6 VERSION 0.1 LANGUAGES C)

add_executable(Boose_PA6 ../src/main.c)

target_include_directories(Boose_PA6 PUBLIC $(CMAKE_CURRENT_SOURCE_DIR)/src)