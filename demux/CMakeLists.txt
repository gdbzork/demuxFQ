include_directories("${PROJECT_SOURCE_DIR}/common")
add_executable(demux demuxFQ.cpp)
target_link_libraries(demux demux_common boost_program_options)
