add_library(crisp
	./lib.cc
)
target_link_libraries(crisp PUBLIC fmt)

target_include_directories(crisp PUBLIC 
	${PROJECT_SOURCE_DIR}/src
	${crab_SOURCE_DIR}/include
)

target_compile_options(crisp PUBLIC 
		-Wall 
		-Werror 
		-Wpedantic 
		-Wextra 
)

