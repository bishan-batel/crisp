add_library(crisp
	./lib.cc
	./token/Keyword.cc
	./token/Identifier.cc
	./lexer/Lexer.cc
	./lexer/Error.cc
	./token/Spanned.cc
)
target_link_libraries(crisp PUBLIC crab fmt)

target_include_directories(crisp PUBLIC 
	${PROJECT_SOURCE_DIR}/src
)

target_compile_options(crisp PUBLIC 
		-Wall 
		-Werror 
		-Wpedantic 
		-Wextra 
)

