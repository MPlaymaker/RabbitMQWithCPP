cmake_minimum_required(VERSION 3.10)
project(rmqone LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Path to SimpleAmqpClient & rabbitmq-c ---
set(SIMPLE_AMQP_CLIENT_INCLUDE "C:/work/projects/cppprojects/SimpleAmqpClient/src")
set(SIMPLE_AMQP_CLIENT_LIB "C:/work/projects/cppprojects/SimpleAmqpClient/build/Debug/SimpleAmqpClient.7.lib")
set(RABBITMQC_LIB "C:/work/projects/cppprojects/rabbitmq-c/librabbitmq/Debug/rabbitmq.4.dll")

# --- Boost paths ---
# CMake’s built-in FindBoost.cmake module does not automatically search C:/local or other custom install paths on Windows.
set(BOOST_ROOT "C:/local/boost_1_89_0")

set(BOOST_LIBRARYDIR "C:/local/boost_1_89_0/stage/lib")

find_package(Boost REQUIRED)

# Boost_INCLUDE_DIRS is provided by CMake’s FindBoost module
if(Boost_FOUND)
    message(STATUS "Boost include dir: ${Boost_INCLUDE_DIRS}")
else()
    message(FATAL_ERROR "Boost not found!")
endif()

# --- Add subdirectories ---
add_subdirectory(Sender)
add_subdirectory(Receiver)
