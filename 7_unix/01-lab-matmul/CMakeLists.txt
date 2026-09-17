cmake_minimum_required(VERSION 3.10)
project(MatrixMultiplicationLab C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(SOURCES
    main.c
    matrix_math.c
    matrix_io.c
)

add_executable(task2_no_opt ${SOURCES})
target_compile_options(task2_no_opt PRIVATE -O0 -Wall -Wextra)
target_link_libraries(task2_no_opt PRIVATE m)

add_executable(task2_opt ${SOURCES})
target_compile_options(task2_opt PRIVATE -O3 -Wall -Wextra)
target_link_libraries(task2_opt PRIVATE m)
