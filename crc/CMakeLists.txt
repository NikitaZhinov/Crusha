cmake_minimum_required(VERSION 3.31)

project(CrushaCompiler LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED On)

file(GLOB AST_SRC_FILES "src/ast/*.cpp")
set(SRC_FILES "src/lexer.cpp" "src/driver.cpp" ${AST_SRC_FILES})
file(GLOB HDR_FILES "include/*.hpp" "include/ast/*.hpp")
file(GLOB MODULE_FILES "src/*.cppm" "src/codegen/*.cppm")

add_subdirectory("../dependencies" "${CMAKE_BINARY_DIR}/dependencies")

set(CRC_LIBRARIES CrushaOptionsLib)

# bison
set(GRAMMAR "src/parser.y" CACHE STRING "file with grammar" FORCE)
find_package(BISON REQUIRED)
bison_target(crc_parser ${GRAMMAR} "${CMAKE_CURRENT_BINARY_DIR}/crc_parser.cpp"
    COMPILE_FLAGS "--defines=${CMAKE_CURRENT_BINARY_DIR}/crc.tab.hh")

# flex
find_package(FLEX REQUIRED)
flex_target(crc_lexer "src/lexer.l" "${CMAKE_CURRENT_BINARY_DIR}/crc_lexer.cpp")

add_flex_bison_dependency(crc_lexer crc_parser)

add_executable(crc "src/main.cpp" ${SRC_FILES} ${HDR_FILES} ${BISON_crc_parser_OUTPUTS} ${FLEX_crc_lexer_OUTPUTS})
target_sources(crc PUBLIC FILE_SET modules_public TYPE CXX_MODULES FILES ${MODULE_FILES})
target_link_libraries(crc PUBLIC ${CRC_LIBRARIES})
include_directories("include" ${CMAKE_CURRENT_BINARY_DIR})

if (WIN32)
    target_compile_definitions(crc PUBLIC "YY_NO_UNISTD_H")
    include_directories(${WinFlexBisonSourseDir})
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(crc PUBLIC "LEXER_PRINT_TOKENS_")
    target_compile_definitions(crc PUBLIC "AST_PRINT_")
else()
    target_compile_definitions(crc PUBLIC "NDEBUG")
endif()

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
# include(CTest)
# enable_testing()
# file(GLOB TEST_SRC_FILES "test/*.cpp")
# find_package(GTest REQUIRED)
# add_executable(crc_tests ${TEST_SRC_FILES} ${SRC_FILES})
# target_sources(crc_tests PUBLIC FILE_SET modules_public TYPE CXX_MODULES FILES ${MODULE_FILES})
# target_link_libraries(crc_tests PRIVATE GTest::gtest GTest::gtest_main GTest::gmock
#                                         GTest::gmock_main ${CRC_LIBRARIES})
