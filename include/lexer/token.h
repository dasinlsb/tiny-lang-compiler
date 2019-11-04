//
// Created by dasin on 2019/11/1.
//

#ifndef PARSER_SRC_LEXER_TOKEN_H_
#define PARSER_SRC_LEXER_TOKEN_H_

#include "util/util.h"
#include "util/string.h"
#include "util/file_position.h"
#include "util/vector.h"
#include "defs.h"

typedef struct {
  string data;
  filepos pos;
  token_t type;
} token_data;

token_data* create_token_data (filepos pos) ;

token_t parse_predefined_symbols (token_data *token);

token_t parse_predefined_keywords (token_data *token) ;

token_t get_token_type (token_data *token);

token_t* get_tokens_type (token_data **tokens) ;

const char *format_tokens (const token_data **tokens);;

void fprint_token (FILE *out, token_data *token);

#endif //PARSER_SRC_LEXER_TOKEN_H_
