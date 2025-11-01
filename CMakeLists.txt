cmake_minimum_required(VERSION 3.22.0 FATAL_ERROR)

# check for clang
find_program(CLANG_CPP_COMPILER clang++)
if(CLANG_CPP_COMPILER)
    message(STATUS "Using clang++: ${CLANG_CPP_COMPILER}")
    set(CMAKE_CXX_COMPILER clang++)
else()
    set(CMAKE_CXX_COMPILER g++-14)
    message(WARNING "clang++ not found, using default compiler: ${CMAKE_CXX_COMPILER}")
endif()

project(Kumo)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# check for mold linker
find_program(MOLD_LINKER mold)
if(MOLD_LINKER)
    message(STATUS "Using mold linker: ${MOLD_LINKER}")
    add_link_options(-fuse-ld=mold)
else()
    message(WARNING "mold linker not found, using default linker")
endif()

find_package(PkgConfig REQUIRED)
pkg_check_modules(POPPLERCPP REQUIRED poppler-cpp)

add_executable(kumo src/main.cpp)

# kumo lib implementations
target_sources(kumo PRIVATE src/StreamWrapper.cpp)

# kumo libs
target_include_directories(kumo PRIVATE ${CMAKE_SOURCE_DIR}/include)

# 3rd party libs
target_include_directories(kumo PRIVATE ${POPPLERCPP_INCLUDE_DIRS})
target_link_libraries(kumo PRIVATE ${POPPLERCPP_LIBRARIES})

target_compile_options(kumo PRIVATE -Wall -Wextra -Werror)