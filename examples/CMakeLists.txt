add_executable(test test.cpp)
target_include_directories(test PRIVATE ankiparser)
target_link_libraries(test PRIVATE ankiparser)