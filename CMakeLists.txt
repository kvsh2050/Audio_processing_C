cmake_minimum_required(VERSION 4.0)
project(Hello_test)
set(CMAKE_C_STANDARD 99)



find_package(PkgConfig REQUIRED)
pkg_check_modules(PORTAUDIO REQUIRED portaudio-2.0)
include_directories(${PORTAUDIO_INCLUDE_DIRS})
link_directories(${PORTAUDIO_LIBRARY_DIRS})




file(GLOB SOURCES "AudioLibrary/*.c")
add_executable(Hello_test ${SOURCES})
target_link_libraries(Hello_test ${PORTAUDIO_LIBRARIES})
