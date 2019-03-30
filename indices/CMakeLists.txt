add_executable(extractIndices extractIndices.cpp indexArgs.h indexArgs.cpp)
target_link_libraries(extractIndices demux_common)
