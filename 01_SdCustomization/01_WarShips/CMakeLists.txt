cmake_minimum_required(VERSION 3.16)
project(war_ships)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Coverage Lib
add_library(coverage_config INTERFACE)
target_compile_options(coverage_config INTERFACE -O0 -g --coverage)
target_link_options(coverage_config INTERFACE --coverage)

# Main executable
add_executable(warShips
    main.cpp
)

target_compile_definitions(warShips PRIVATE PROJECT_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
add_definitions(-DPROJECT_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

target_include_directories(warShips PRIVATE
    ${FLTK_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}
)

target_link_libraries(warShips PRIVATE ${FLTK_LIBRARIES} coverage_config)


# -----------------------
#        TESTING
# -----------------------
include(CTest)

if (BUILD_TESTING)
    include(FetchContent)

    FetchContent_Declare(
        catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.5.2
    )
    FetchContent_MakeAvailable(catch2)

    # ---- Das Test-Target definieren ----
    add_executable(warShips_test
        Tests/test_player.cpp
    )

    target_include_directories(warShips_test PRIVATE
        ${CMAKE_SOURCE_DIR}
    )

    target_link_libraries(warShips_test PRIVATE
        Catch2::Catch2WithMain
        coverage_config
    )

    # Catch2 entdecken lassen
    include(Catch)
    catch_discover_tests(warShips_test)
endif()
