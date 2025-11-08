add_executable(sender main.cpp)

# You can do either of following
target_include_directories(sender PRIVATE ${SIMPLE_AMQP_CLIENT_INCLUDE} ${Boost_INCLUDE_DIRS})

# You can do either of following
target_link_libraries(sender PRIVATE ${SIMPLE_AMQP_CLIENT_LIB})

# Copy DLLs automatically to output directory after build
add_custom_command(TARGET sender POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SIMPLE_AMQP_CLIENT_DLL}
        $<TARGET_FILE_DIR:sender>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${RABBITMQC_DLL}
        $<TARGET_FILE_DIR:sender>
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${BOOST_LIBRARYDIR}
        $<TARGET_FILE_DIR:sender>
)
