cmake_minimum_required(VERSION 3.23.0 FATAL_ERROR)

project(Kumo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# check for mold linker
if (UNIX)
    find_program(MOLD_LINKER mold)
    if(MOLD_LINKER)
        message(STATUS "Using mold linker: ${MOLD_LINKER}")
        add_link_options(-fuse-ld=mold)
    endif()
endif()

add_executable(Kumo
    src/main.cpp
    src/StreamWrapper.cpp
)

# 3rd party libs
find_package(PkgConfig REQUIRED)
pkg_check_modules(POPPLER_CPP REQUIRED IMPORTED_TARGET poppler-cpp)
target_link_libraries(Kumo PRIVATE PkgConfig::POPPLER_CPP)

# compiler options
if (UNIX)
    target_compile_options(Kumo PRIVATE -Wall -Wextra -Werror)
elseif(MSVC)
    target_compile_options(Kumo PRIVATE /W4 /WX)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()