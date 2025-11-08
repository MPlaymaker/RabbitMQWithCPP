add_executable(receiver main.cpp)

# You can do either of following
#target_include_directories(receiver PRIVATE C:\work\projects\cppprojects\SimpleAmqpClient\src\SimpleAmqpClient)
target_include_directories(receiver PRIVATE ${SIMPLE_AMQP_CLIENT_INCLUDE} ${Boost_INCLUDE_DIRS})

# You can do either of following
#target_link_libraries(receiver PRIVATE C:\work\projects\cppprojects\SimpleAmqpClient\build\Debug\SimpleAmqpClient.7.lib)
target_link_libraries(receiver PRIVATE ${SIMPLE_AMQP_CLIENT_LIB})

# Copy DLLs automatically to output directory after build
add_custom_command(TARGET receiver POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/work/projects/cppprojects/SimpleAmqpClient/build/Debug/SimpleAmqpClient.7.dll"
        $<TARGET_FILE_DIR:receiver>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/work/projects/cppprojects/rabbitmq-c/librabbitmq/Debug/rabbitmq.4.dll"
        $<TARGET_FILE_DIR:receiver>
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "C:/local/boost_1_89_0/stage/lib"
        $<TARGET_FILE_DIR:receiver>
)