include_directories("${PROJECT_SOURCE_DIR}/common")

#configure_file("${PROJECT_SOURCE_DIR}/test/sampleSheet_test.cpp.in"
#               "${PROJECT_BINARY_DIR}/test/sampleSheet_test.cpp")

#add_subdirectory(testdata)
file(COPY testdata DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
add_executable(test_demux catch.hpp main_test.cpp sampleSheet_test.cpp)
target_link_libraries(test_demux demux_common)
