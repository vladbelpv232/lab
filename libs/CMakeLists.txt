cmake_minimum_required(VERSION 3.26)
project(untitled C)

set(CMAKE_C_STANDARD 11)

add_executable(untitled main.c
        libs/string_/string_.c
        libs/string_/string_.h
        libs/string_/tests_for_string.c
        libs/date_structures/lab_18.c
        libs/algorithms/lab_19.c
        libs/exam/exam.c
)


add_subdirectory(libs)
target_link_libraries(untitled  data_structures)
target_link_libraries(untitled algorithms)
target_link_libraries(untitled string_)
target_link_libraries(untitled exam)
