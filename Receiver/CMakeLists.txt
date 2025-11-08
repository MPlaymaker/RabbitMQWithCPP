add_executable(receiver main.cpp)

# You can do either of following
target_include_directories(receiver PRIVATE ${SIMPLE_AMQP_CLIENT_INCLUDE} ${Boost_INCLUDE_DIRS})

# You can do either of following
target_link_libraries(receiver PRIVATE ${SIMPLE_AMQP_CLIENT_LIB})

# Copy DLLs automatically to output directory after build
add_custom_command(TARGET receiver POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SIMPLE_AMQP_CLIENT_DLL}
        $<TARGET_FILE_DIR:receiver>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${RABBITMQC_DLL}
        $<TARGET_FILE_DIR:receiver>
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${BOOST_LIBRARYDIR}
        $<TARGET_FILE_DIR:receiver>
)