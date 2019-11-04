//
// Created by dasin on 2019/11/4.
//

#include "syntax/syntax_analyze_input.h"
#include "util/log.h"

sa_input_t* sa_input_create(token_data **tokens) {
  sa_input_t *i = malloc(sizeof(sa_input_t));
  i->cur = 0;
  i->tokens = tokens;
  i->marks = NULL;
  return i;
}

token_data* sa_peek_input (sa_input_t *i) {
  if (i->cur == vector_size(i->tokens)) {
    return NULL;
  }
  return i->tokens[i->cur];
}

token_data* sa_forward_input (sa_input_t *i) {
  if (i->cur == vector_size(i->tokens)) {
    return NULL;
  }
  //DebugLog(1, "sa_input forward %s\n", token_t2str(i->tokens[i->cur]->type))
  i->cur ++;
  return i->cur == vector_size(i->tokens)
         ? NULL
         : i->tokens[i->cur];
}

token_data* sa_backward_input (sa_input_t *i) {
  if (i->cur == 0) {
    return NULL;
  }
  i->cur --;
  return i->tokens[i->cur];
}

token_data* sa_get_input (sa_input_t *i) {
  token_data *token = sa_peek_input(i);
  sa_forward_input(i);
  return token;
}

void sa_input_push_mark (sa_input_t *i) {
  vector_push_back(i->marks, i->cur);
}

void sa_input_pop_mark (sa_input_t *i) {
  assert(vector_size(i->marks) > 0);
  i->cur = *vector_last(i->marks);
  vector_pop_back(i->marks);
}
