cmake_minimum_required(VERSION 3.2.2)

project(jws)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# From https://github.com/pboettch/json-schema-validator

# Create an interface-target called json-hpp
add_library(json-hpp INTERFACE)
set(nlohmann_json_DIR ${CMAKE_CURRENT_SOURCE_DIR}/nlohmann/json-3.9.1/single_include)
target_include_directories(json-hpp INTERFACE ${nlohmann_json_DIR})

# Add json-schema-validator
add_subdirectory(pboettch/json-schema-validator-e1cef0b json-schema-validator)

# JWS = JSON With Schema
# Our target brings in both nlohmann/json and pboettch/json-schema-validator-e1cef0b
# and includes some convenience functions
add_library(jws INTERFACE)
target_include_directories(jws INTERFACE include)
target_sources(jws INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/jws/json_with_schema.hpp)
target_link_libraries(jws INTERFACE json-hpp nlohmann_json_schema_validator)

# Examples and tests
option(BUILD_JWS_EXAMPLES "Build examples" OFF)
if (BUILD_JWS_EXAMPLES)
  add_subdirectory(examples)
endif()

option(BUILD_JWS_TESTS "Build examples" OFF)
if (BUILD_JWS_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
