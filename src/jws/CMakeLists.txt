cmake_minimum_required(VERSION 3.2.2)

# From https://github.com/pboettch/json-schema-validator

# Create an interface-target called json-hpp
add_library(json-hpp INTERFACE)
target_include_directories(json-hpp INTERFACE nlohmann/json)

# Add json-schema-validator
add_subdirectory(pboettch/json-schema-validator-ad9e992 json-schema-validator)

# JWS = JSON With Schema
# Our target brings in both nlohmann/json and pboettch/json-schema-validator-1.0.0
# and includes some convenience functions
add_library(jws INTERFACE)
target_include_directories(jws INTERFACE include)
target_sources(jws INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/jws/json_with_schema.hpp)
target_link_libraries(jws INTERFACE json-hpp json-schema-validator)

