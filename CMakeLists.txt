cmake_minimum_required(VERSION 3.10)
SET(CXX_STANDARD 17)


project(AnkiParser)

add_subdirectory(vendor/libzip)
add_subdirectory(ankiparser)
add_subdirectory(examples)