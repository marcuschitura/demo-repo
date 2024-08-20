message("Processing CMakeLists.txt...")

cmake_minimum_required(VERSION 3.30.2) # the currently stable version of CMake that is required to build the project
project(elen3009-lab-2) # project name

# require the compiler to support C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# statically link to the standard c++ libraries
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++")

# ====================== Declare Variables ======================

set(SRC_PATH "${CMAKE_SOURCE_DIR}/src/text-query-system/code") # path to source code folder
set(MAIN_CPP "main.cpp") # cpp file containing the main function
set(EXE_NAME "TextQuery") # executable name
set(TESTS_EXE_NAME "TextQueryTests") # test executable name
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin") # sets output directory for targets, supersedes EXECUTABLE_OUTPUT_PATH
set(WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}) # set working directory for main executable so that relative paths are correct when running from within the IDE

# ====================== Select Files for Compilation ======================

# CONFIGURE_DEPENDS is used to make sure that the globbing is re-run when a new file is added
file(GLOB EXE_SRC CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/text-query-system/code/*.cpp)
file(GLOB TESTS_SRC CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/text-query-system/code/*.cpp ${CMAKE_SOURCE_DIR}/src/text-query-system/tests/*.cpp)
list(REMOVE_ITEM TESTS_SRC "${CMAKE_SOURCE_DIR}/src/text-query-system/code/${MAIN_CPP}") # remove MAIN_CPP from the test source files - doctest provides its own main function

# ====================== Download Dependencies ======================

include(FetchContent)

# Download doctest
FetchContent_Declare(
    doctest
    # specify the repository URL
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    # corresponds to doctest v2.4.11 - good practice to specify the commit hash as tags can be moved
    GIT_TAG "ae7a13539fb71f270b87eb2e874fbac80bc8dda2" )

# make the dependencies available to the build system and populate dependency variables like doctest_SOURCE_DIR
FetchContent_MakeAvailable(doctest)

# ====================== Setup Targets ======================

# TextQuery executable
add_executable(${EXE_NAME} ${EXE_SRC})
target_compile_features(${EXE_NAME} PRIVATE cxx_std_17) # enable C++17 features for the target

# Test executable
add_executable(${TESTS_EXE_NAME} ${TESTS_SRC})
target_include_directories(${TESTS_EXE_NAME} PRIVATE ${SRC_PATH})
target_include_directories(${TESTS_EXE_NAME} PRIVATE "${doctest_SOURCE_DIR}/doctest") # include doctest headers
target_compile_features(${TESTS_EXE_NAME} PRIVATE cxx_std_17) # enable C++17 features for the target

# ====================== Post-Build Commands ======================

add_custom_command(TARGET ${EXE_NAME} POST_BUILD
    # TextQuery executable assumes that alice.txt is alongside it in the same directory
    COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${SRC_PATH}/alice.txt $<TARGET_FILE_DIR:${EXE_NAME}>
)

add_custom_command(TARGET ${TESTS_EXE_NAME} POST_BUILD
    # Test executable assumes that alice.txt is alongside it in the same directory
    COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${SRC_PATH}/alice.txt $<TARGET_FILE_DIR:${EXE_NAME}>
)

# ====================== CTest ======================
include(CTest) # include otherwise Site is missing
enable_testing()
include(${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)
# automatically add doctest tests to CTest; specify WORKING_DIRECTORY to ensure that relative paths are correct for CTest
doctest_discover_tests(${TESTS_EXE_NAME} WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})