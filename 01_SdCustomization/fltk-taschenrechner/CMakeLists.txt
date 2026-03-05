cmake_minimum_required(VERSION 3.16)
project(fltk_calc)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(FLTK REQUIRED)

add_executable(calculator
    main.cpp
    calculator.cpp
    calculator.h
)

target_include_directories(calculator PRIVATE ${FLTK_INCLUDE_DIR})
target_link_libraries(calculator PRIVATE ${FLTK_LIBRARIES})