//
// Created by dasin on 2019/11/1.
//

#ifndef PARSER_SRC_LEXER_H_
#define PARSER_SRC_LEXER_H_

#include "token.h"
#include "lex_state.h"
#include "error/parse_error.h"
#include "util/util.h"
#include "util/file_position.h"
#include "util/vector.h"

// next_token will consume @arg input
token_data* next_token(lex_state *input);

token_data** lexer(const char *input_data);

#endif //PARSER_SRC_LEXER_H_
