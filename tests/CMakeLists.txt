add_executable(test_jws test_jws.cpp)
target_link_libraries(test_jws jws)
add_test(NAME test_jws COMMAND test_jws --working_dir $<TARGET_FILE_DIR:test_jws>)
add_custom_command(TARGET test_jws PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:test_jws>)
