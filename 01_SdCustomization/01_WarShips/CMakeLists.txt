cmake_minimum_required(VERSION 3.16)

project(war_ships LANGUAGES CXX)

# =====================================================
# C++ Standard
# =====================================================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# =====================================================
# FLTK (nur Client!)
# =====================================================
find_package(FLTK REQUIRED)

# =====================================================
# Coverage (optional, wie bei dir)
# =====================================================
add_library(coverage_config INTERFACE)
target_compile_options(coverage_config INTERFACE -O0 -g --coverage)
target_link_options(coverage_config INTERFACE --coverage)

# =====================================================
# CORE Library
#   → Spiellogik + Datenmodelle
# =====================================================

file(GLOB_RECURSE CORE_SOURCES CONFIGURE_DEPENDS
    Models/*.cpp
    Context/*.cpp
)

add_library(core STATIC
    ${CORE_SOURCES}
)

target_include_directories(core PUBLIC
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/Models
    ${CMAKE_SOURCE_DIR}/Models/Factory
    ${CMAKE_SOURCE_DIR}/common/Context

)

# =====================================================
# SERVER Executable
# =====================================================

add_executable(server
    server/main.cpp
)

target_link_libraries(server PRIVATE
    core
)

target_compile_definitions(server PRIVATE
    PROJECT_SOURCE_DIR="${CMAKE_SOURCE_DIR}"
)

# =====================================================
# CLIENT Executable
# =====================================================

file(GLOB_RECURSE CLIENT_SOURCES CONFIGURE_DEPENDS
    UI/*.cpp
    UI/Callbacks/*.cpp
    Helper/*.cpp
    client/*.cpp
)

add_executable(client
    ${CLIENT_SOURCES}
)

target_include_directories(client PRIVATE
    ${FLTK_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/UI
    ${CMAKE_SOURCE_DIR}/UI/Callbacks
    ${CMAKE_SOURCE_DIR}/Helper
    ${CMAKE_SOURCE_DIR}/Helper/InputHelper
    ${CMAKE_SOURCE_DIR}/Helper/UIHelper
)

target_link_libraries(client PRIVATE
    core
    ${FLTK_LIBRARIES}
)

target_compile_definitions(client PRIVATE
    PROJECT_SOURCE_DIR="${CMAKE_SOURCE_DIR}"
)