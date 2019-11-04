cmake_minimum_required(VERSION 3.5)

set(CMAKE_C_FLAGS "-g")

project(tiny)

include_directories(../include)

set(error_src error/parse_error.c)
set(lex_src lexer/defs.c
        lexer/token.c
        lexer/lexer.c
        lexer/lex_state.c)
set(syntax_src syntax/parser_combinator.c
        syntax/syntax_analyze.c
        syntax/syntax_analyze_input.c
        syntax/syntax_tree.c)
set(util_src util/file_position.c
        util/string.c
        util/util.c ../include/util/log.h)

add_executable(tiny main.c
        ${error_src}
        ${lex_src}
        ${syntax_src}
        ${util_src}
        )

