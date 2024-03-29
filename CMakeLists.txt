cmake_minimum_required(VERSION 3.10)

if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  message(SEND_ERROR "In-source builds are not allowed.")
endif ()

project(CBSW_Unit_Expect VERSION 1.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (NOT PROJECT_IS_TOP_LEVEL)
  set(CBSW_UNIT_EXPECT_INCLUDED True PARENT_SCOPE)
  set(CBSW_UNIT_EXPECT_INCLUDE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include PARENT_SCOPE)
endif()

set(CBSW_UNIT_EXPECT_INCLUDE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(CBSW_UNIT_EXPECT_SOURCE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(CBSW_UNIT_EXPECT_EXAMPLES_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/examples)
set(CBSW_UNIT_EXPECT_DEPENDENCIES_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/dependencies)

configure_file(${CBSW_UNIT_EXPECT_SOURCE_DIRECTORY}/version.hpp.in src/settings/version.hpp)

add_library(cbsw-unit-expect)

option(CBSW_UNIT_BUILD_EXAMPLES "" OFF)

if(NOT DEFINED CBSW_UNIT_INCLUDED)
add_subdirectory(${CBSW_UNIT_EXPECT_DEPENDENCIES_DIRECTORY}/cbsw-unit cbsw-unit)
endif()

add_subdirectory(${CBSW_UNIT_EXPECT_SOURCE_DIRECTORY})

target_precompile_headers(cbsw-unit-expect PRIVATE ${CBSW_UNIT_EXPECT_SOURCE_DIRECTORY}/pch.hpp)
target_include_directories(cbsw-unit-expect PUBLIC "${PROJECT_BINARY_DIR}/src")
target_include_directories(cbsw-unit-expect PUBLIC "${CBSW_UNIT_EXPECT_INCLUDE_DIRECTORY}")
target_include_directories(cbsw-unit-expect PUBLIC "${CBSW_UNIT_EXPECT_SOURCE_DIRECTORY}")

target_link_libraries(cbsw-unit-expect cbsw-unit)

target_compile_options(cbsw-unit-expect PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

option(CBSW_UNIT_EXPECT_BUILD_EXAMPLES "Build the example applications" ON)

if(CBSW_UNIT_EXPECT_BUILD_EXAMPLES)
    add_subdirectory(${CBSW_UNIT_EXPECT_EXAMPLES_DIRECTORY})
endif()

