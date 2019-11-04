//
// Created by dasin on 2019/11/2.
//

#ifndef PARSER_SRC_UTIL_SYNTAX_ANALYZE_STATE_H_
#define PARSER_SRC_UTIL_SYNTAX_ANALYZE_STATE_H_

#include "../util/vector.h"
#include "../lexer/token.h"

typedef struct {
  int cur;
  int *marks;
  token_data **tokens;
} sa_input_t;

sa_input_t* sa_input_create(token_data **tokens) ;

token_data* sa_peek_input (sa_input_t *i);

token_data* sa_forward_input (sa_input_t *i);

token_data* sa_backward_input (sa_input_t *i);

token_data* sa_get_input (sa_input_t *i);

void sa_input_push_mark (sa_input_t *i);

void sa_input_pop_mark (sa_input_t *i);

#endif //PARSER_SRC_UTIL_SYNTAX_ANALYZE_STATE_H_
