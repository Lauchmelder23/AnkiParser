file(GLOB_RECURSE target_src
	"src/*.cpp"
)

file(GLOB_RECURSE target_inc
	"include/*.hpp"
)

add_library(ankiparser STATIC
	${target_inc}
	${target_src}
)

target_include_directories(ankiparser PUBLIC
	include
	libzip::zip
)

target_link_libraries(ankiparser PUBLIC
	libzip::zip
)