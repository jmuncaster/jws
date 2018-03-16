add_executable(validate_json validate_json.cpp)
target_link_libraries(validate_json jws)
add_custom_command(TARGET validate_json POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:validate_json>)
