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



# CTest aktivieren
include(CTest)            # setzt u.a. die Variable BUILD_TESTING
if (BUILD_TESTING)
  # Catch2 beziehen (v3 empfohlen)
  include(FetchContent)
  FetchContent_Declare(
    catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.5.2      # oder eine aktuelle stabile Version
  )
  FetchContent_MakeAvailable(catch2)

  # Test-Executable (ohne FLTK!)
  add_executable(tests
      tests/test_calculator.cpp
      calculator.cpp          # nur die Logik einbinden, NICHT main.cpp
  )
  target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
  target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

  # Catch2 test discovery -> ctest kann einzelne TEST_CASEs erkennen
  include(Catch)
  catch_discover_tests(tests)
endif()
