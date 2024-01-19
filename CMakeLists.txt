cmake_minimum_required(VERSION 3.25.1)
project(Showtime)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)

FetchContent_Declare(
        portaudio
        URL http://files.portaudio.com/archives/pa_stable_v190700_20210406.tgz
)

FetchContent_GetProperties(portaudio)
if(NOT portaudio_POPULATED)
    FetchContent_Populate(portaudio)
    add_subdirectory(${portaudio_SOURCE_DIR} ${portaudio_BINARY_DIR})
endif()

add_executable(Showtime main.cpp)

message(STATUS "portaudio_SOURCE_DIR: ${portaudio_SOURCE_DIR}")

target_include_directories(Showtime PRIVATE ${portaudio_SOURCE_DIR}/include)
target_link_libraries(Showtime PRIVATE portaudio rt asound jack pthread)