//
// Created by dasin on 2019/11/1.
//



#include "lexer/lexer.h"

// next_token will consume @arg input
token_data* next_token(lex_state *input) {
  while (peek_lex_state(input) != NULL && isspace(*peek_lex_state(input))) {
    forward_lex_state(input);
  }
  if (peek_lex_state(input) == NULL) {
    return NULL;
  }
  // comment
  if (*input->sp == '/') {
    char *comment_l = lex_state_match_word(input, "/**");
    if (comment_l != NULL) { // is comment
      // skip `/**`
      for (int i = 0; i < 3; i++) forward_lex_state(input);
      char *comment_r = lex_state_find_next_match(input, "**/");
      if (comment_r != NULL) {
        while (input->sp < comment_r) {
          forward_lex_state(input);
        }
        return next_token(input);
      } else {
        parse_error_with_pos(&input->fp, "no comment end flag `**/` found!");
      }
    }
  }
  // number
  if (is_number(*input->sp)) {
    int has_dot = *input->sp == '.';
    token_data *token = create_token_data(input->fp);
    char *c = peek_lex_state(input);
    while (c != NULL && is_number(*c)) {
      if (*c == '.') {
        if (has_dot) {
          parse_error_with_pos(&input->fp, "meet dot more than once within single number");
        } else {
          has_dot = 1;
        }
      }
      append_char(&token->data, *c);
      c = forward_lex_state(input);
    }
    token->type = TConstNumber;
    return token;
  }
  // identifier
  else if (is_identifier_head(*input->sp)) {
    token_data *token = create_token_data(input->fp);
    append_char(&token->data, *input->sp);
    char *c = forward_lex_state(input);
    while (c != NULL && is_identifier_body(*c)) {
      append_char(&token->data, *c);
      c = forward_lex_state(input);
    }
    token->type = parse_predefined_keywords(token);
    if (token->type == -1) token->type = TIdentifier;
    return token;
  }
  // constant string
  else if (*input->sp == '"') {
    char *c;
    int is_escaped = 0;
    token_data *token = create_token_data(input->fp);
    append_char(&token->data, *input->sp);
    while ((c = forward_lex_state(input)) != NULL) {
      if (*c == '\\') {
        if (is_escaped == 1) {
          append_char(&token->data, escape_char(*c));
          is_escaped = 0;
        } else {
          is_escaped = 1;
        }
      } else if (*c == '"'){
        if (is_escaped) {
          append_char(&token->data, escape_char(*c));
          is_escaped = 0;
        } else {
          append_char(&token->data, *c);
          forward_lex_state(input);
          break;
        }
      } else {
        if (is_escaped == 1) {
          append_char(&token->data, escape_char(*c));
          is_escaped = 0;
        } else {
          append_char(&token->data, *c);
        }
      }
    }
    token->type = TConstString;
    return token;
  }
  // symbol
  else {
    token_data *token = create_token_data(input->fp);
    char *c = peek_lex_state(input);
    while (c != NULL && !isspace(*c)) {
      append_char(&token->data, *c);
      c = forward_lex_state(input);
      token->type = parse_predefined_symbols(token);
      if (token->type != -1) {
        return token;
      }
    }
    parse_error_with_pos(&input->fp, "unknown symbol");
  }
}

token_data** lexer(const char *input_data) {
  int input_n = (int)strlen(input_data);
  lex_state input;
  input.sp = (char*)input_data;
  input.end = input_data + input_n;
  input.fp = (filepos) {1, 1};
  token_data **tokens = NULL;
  token_data *token;
  while ((token = next_token(&input)) != NULL) {
    vector_push_back(tokens, token);
  }
  return tokens;
}


