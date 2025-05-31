cmake_minimum_required(VERSION 4.0)
project(Hello_test)
file(GLOB SOURCES "AudioLibrary/*.c")
add_executable(Hello_test ${SOURCES})
