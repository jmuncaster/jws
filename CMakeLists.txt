cmake_minimum_required(VERSION 3.2.2)

project(json_schema_test)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

if (APPLE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcolor-diagnostics")
endif(APPLE)

# From https://github.com/pboettch/json-schema-validator

# Create an interface-target called json-hpp
add_library(json-hpp INTERFACE)
target_include_directories(json-hpp INTERFACE nlohmann/json-3.1.1)

# Add json-schema-validator
add_subdirectory(pboettch/json-schema-validator-ad9e992 json-schema-validator)

# JWS = JSON With Schema
# Our target brings in both nlohmann/json and pboettch/json-schema-validator-1.0.0
# and includes some convenience functions
add_library(jws INTERFACE)
target_include_directories(jws INTERFACE include)
target_sources(jws INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/jws/json_with_schema.hpp)
target_link_libraries(jws INTERFACE json-hpp json-schema-validator)

# Examples and tests
add_subdirectory(examples)
enable_testing()
add_subdirectory(tests)
