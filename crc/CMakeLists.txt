cmake_minimum_required(VERSION 3.30)

project(CRC VERSION 0.1.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED On)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

add_compile_definitions(CRC_VERSION=\"${PROJECT_VERSION}\")
if (CMAKE_BUILD_TYPE STREQUAL Release)
else()
    add_compile_definitions(DEBUG)
endif()
if (WIN32)
    if (CMAKE_BUILD_TYPE STREQUAL Release)
        add_compile_options(/O2)
    endif()
else()
    add_compile_options(-Wall -Wextra)
    if (CMAKE_BUILD_TYPE STREQUAL Release)
        add_compile_options(-O3)
    endif()
endif()

add_executable(${PROJECT_NAME} "src/main.cpp" "include/option/option.h" "src/option.cpp"
                               "include/compiler/compiler.h" "src/compiler.cpp" "include/compiler/parser.h" "include/compiler/dictionary.h" "src/dictionary.cpp")
target_link_libraries(${PROJECT_NAME} PRIVATE ArgsParser ErrorManager Lexer)
target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_SOURCE_DIR}/libs/ArgsParser/include"
    "${CMAKE_SOURCE_DIR}/libs/ErrorManager/include" "${CMAKE_SOURCE_DIR}/libs/Lexer/include")
target_include_directories(${PROJECT_NAME} PRIVATE "include")
