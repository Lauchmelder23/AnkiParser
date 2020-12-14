cmake_minimum_required(VERSION 3.10)

project(AnkiParser)

file(GLOB_RECURSE target_src
	"src/*.cpp"
)

file(GLOB_RECURSE target_inc
	"include/*.hpp"
)

add_subdirectory(vendor/libzip)

add_library(ankiparser
	${target_inc}
	${target_src}
)

target_include_directories(ankiparser PRIVATE
	${target_inc}
)