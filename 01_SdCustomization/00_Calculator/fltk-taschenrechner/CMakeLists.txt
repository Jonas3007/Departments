cmake_minimum_required(VERSION 3.16)
project(fltk_calc)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(FLTK REQUIRED)

# -------------------------------
# Coverage INTERFACE Library
# -------------------------------
add_library(coverage_config INTERFACE)
target_compile_options(coverage_config INTERFACE -O0 -g --coverage)
target_link_options(coverage_config INTERFACE --coverage)

# -------------------------------
# Hauptprogramm
# -------------------------------
add_executable(calculator
    main.cpp
    Classes/calculator.cpp
    Classes/calculator.h
    Classes/historyService.h
    Classes/historyService.cpp
    Context/Appcontext.h
    UI/Main/UI_MainWindow.cpp
    UI/Main/UI_MainWindow.h
    UI/History/UI_HistoryWindow.cpp
    UI/History/UI_HistoryWindow.h
    UI/Callbacks/Callbacks.cpp
    UI/Callbacks/Callbacks.h

)
target_compile_definitions(calculator PRIVATE PROJECT_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
add_definitions(-DPROJECT_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

target_include_directories(calculator PRIVATE
    ${FLTK_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/Classes
    ${CMAKE_SOURCE_DIR}/Context
    ${CMAKE_SOURCE_DIR}/UI
    ${CMAKE_SOURCE_DIR}/UI/Main
    ${CMAKE_SOURCE_DIR}/UI/History
    ${CMAKE_SOURCE_DIR}/UI/Callbacks
)

target_include_directories(calculator PRIVATE ${FLTK_INCLUDE_DIR})
target_link_libraries(calculator PRIVATE ${FLTK_LIBRARIES} coverage_config)

# -------------------------------
# TESTING
# -------------------------------
include(CTest)

if (BUILD_TESTING)
    include(FetchContent)

    FetchContent_Declare(
        catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.5.2
    )
    FetchContent_MakeAvailable(catch2)

    add_executable(tests
        tests/test_calculator.cpp
        Classes/calculator.cpp
        Classes/calculator.h
    )
    
target_include_directories(tests PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/Classes
)

    target_link_libraries(tests PRIVATE Catch2::Catch2WithMain coverage_config)

    include(Catch)
    catch_discover_tests(tests)
endif()
