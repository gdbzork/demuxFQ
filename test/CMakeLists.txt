include_directories("${PROJECT_SOURCE_DIR}/common")

#add_subdirectory(testdata)
file(COPY testdata DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
add_executable(test_demux catch.hpp main_test.cpp
                          index_test.cpp indexFriend.cpp indexFriend.h
                          indexPattern_test.cpp
                          lineType_test.cpp lineTypeFriend.cpp lineTypeFriend.h)
target_link_libraries(test_demux demux_common)
