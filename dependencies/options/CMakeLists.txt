cmake_minimum_required(VERSION 3.31)

project(CrushaOptionsLib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED On)

file(GLOB SRC_FILES "src/*.cppm")

add_library(${PROJECT_NAME} STATIC)
target_sources(${PROJECT_NAME} PUBLIC FILE_SET modules_public TYPE CXX_MODULES FILES ${SRC_FILES})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)

# Doxygen
find_package(Doxygen REQUIRED)
if(DOXYGEN_FOUND)
    message("Doxygen build started")
 	add_custom_target(${PROJECT_NAME}Doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        VERBATIM)
    message("Doxygen build finished")
else()
    message("Doxygen need to be installed to generate the doxygen documentation")
endif()

# Tests
include(CTest)
enable_testing()
file(GLOB TEST_SRC_FILES "test/*.cpp")
find_package(GTest REQUIRED)
add_executable(${PROJECT_NAME}Tests ${TEST_SRC_FILES})
target_link_libraries(${PROJECT_NAME}Tests PRIVATE GTest::gtest GTest::gtest_main GTest::gmock
                                                   GTest::gmock_main ${PROJECT_NAME})
