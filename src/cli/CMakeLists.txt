add_executable(crisp-cli
	./cli.cc
)

target_link_libraries(crisp-cli PUBLIC crisp)

target_compile_options(crisp-cli PUBLIC 
		-Wall 
		-Werror 
		-Wpedantic 
		-Wextra 
)

