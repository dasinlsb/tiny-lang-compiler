//
// Created by dasin on 2019/11/1.
//

#include "lexer/token.h"


token_data* create_token_data (filepos pos) {
  token_data *token = (token_data*)malloc(sizeof(token_data));
  memcpy(&token->data, empty_string(), sizeof(string));
  token->pos = pos;
  return token;
};

token_t parse_predefined_symbols (token_data *token) {
  int n = sizeof(predefined_symbols)/sizeof(char*);
  for (int i = 0; i < n; i++) {
    string s = token->data;
    char *next = match_word(s.data, s.data+s.len, predefined_symbols[i]);
    if (next != NULL) {
      return symbolIndex2token_t(i);
    }
  }
  //parse_error_with_pos(&token->pos, "try to parse as predefined symbols error");
  return -1;
};

token_t parse_predefined_keywords (token_data *token) {
  int n = sizeof(predefined_keywords) / sizeof(char*);
  for (int i = 0; i < n; i++) {
    string s = token->data;
    char *next = match_word(s.data, s.data+s.len, predefined_keywords[i]);
    if (next != NULL) {
      return keywordIndex2token_t(i);
    }
  }
  //parse_error_with_pos(&token->pos, "try to parse as predefined keyword error");
  return -1;
}

token_t get_token_type (token_data *token) {
  return token->type;
}

token_t* get_tokens_type (token_data **tokens) {
  token_t *types = NULL;
  for (int i = 0; i < (int)vector_size(tokens); i++) {
    vector_push_back(types, tokens[i]->type);
  }
  return types;
}

const char *format_tokens (const token_data **tokens) {
  string *buf = empty_string();
  append_const_str(buf, "data:");
  for (int i = 0; i < (int)vector_size(tokens); i++) {
    append_char(buf, '[');
    append_into(buf, &tokens[i]->data);
//    append_char(buf, '|');
//    append_const_str(buf, token_t2str(tokens[i]->type));
    append_const_str(buf, "], ");
  }
  append_char(buf, '\n');
  return buf->data;
}

void fprint_token (FILE *out, token_data *token) {
  fprintf(out, "%s", token->data.data);
}


