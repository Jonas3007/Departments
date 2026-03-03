cmake_minimum_required(VERSION 3.16)
project(QTCalculator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

add_executable(qtcalc
    main.cpp
)

target_link_libraries(qtcalc Qt6::Widgets)