cmake_minimum_required(VERSION 3.7)

project(demuxFQ)
set (demuxFQ_VERSION_MAJOR 1)
set (demuxFQ_VERSION_MINOR 0)

configure_file("${PROJECT_SOURCE_DIR}/config.h.in" "${PROJECT_BINARY_DIR}/config.h")
include_directories("${PROJECT_BINARY_DIR}")

add_subdirectory(common)
add_subdirectory(demux)
add_subdirectory(indices)
add_subdirectory(test)
