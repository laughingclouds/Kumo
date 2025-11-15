cmake_minimum_required(VERSION 3.22.0 FATAL_ERROR)

project(Kumo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# check for mold linker
find_program(MOLD_LINKER mold)
if(MOLD_LINKER)
    message(STATUS "Using mold linker: ${MOLD_LINKER}")
    add_link_options(-fuse-ld=mold)
endif()

add_executable(kumo
    src/main.cpp
    src/StreamWrapper.cpp
)

# kumo libs
target_include_directories(kumo PRIVATE ${PROJECT_SOURCE_DIR}/include)

# 3rd party libs
find_package(PkgConfig REQUIRED)
pkg_check_modules(POPPLER_CPP REQUIRED IMPORTED_TARGET poppler-cpp)
target_link_libraries(kumo PRIVATE PkgConfig::POPPLER_CPP)

# compiler options
if (UNIX)
    target_compile_options(kumo PRIVATE -Wall -Wextra -Werror)
elseif(MSVC)
    target_compile_options(kumo PRIVATE /W4 /WX)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()