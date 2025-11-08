cmake_minimum_required(VERSION 3.10)
project(rmqone LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Path to SimpleAmqpClient ---
set(SIMPLE_AMQP_CLIENT_INCLUDE "C:/work/projects/cppprojects/SimpleAmqpClient/src")
set(SIMPLE_AMQP_CLIENT_LIB "C:/work/projects/cppprojects/SimpleAmqpClient/build/Debug/SimpleAmqpClient.7.lib")

# --- Boost paths ---
set(BOOST_ROOT "C:/local/boost_1_89_0")
set(BOOST_INCLUDEDIR "${BOOST_ROOT}")
set(BOOST_LIBRARYDIR "${BOOST_ROOT}/stage/lib")

find_package(Boost REQUIRED)

if(Boost_FOUND)
    message(STATUS "Boost include dir: ${Boost_INCLUDE_DIRS}")
else()
    message(FATAL_ERROR "Boost not found!")
endif()

# --- Add subdirectories ---
add_subdirectory(Sender)
add_subdirectory(Receiver)
