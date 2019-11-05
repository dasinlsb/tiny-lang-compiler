//
// Created by dasin on 2019/11/1.
//

#include "lexer/defs.h"


const char *predefined_symbols[] = {
    ";",
    ",",
    "(",
    ")",
    "+",
    "-",
    "*",
    "/",
    ":=",
    "==",
    "!="
};

const char *predefined_keywords[] = {
    "IF",
    "ELSE",
    "WRITE",
    "READ",
    "RETURN",
    "BEGIN",
    "END",
    "MAIN",
    "INT",
    "REAL"
};

const char *my_defined_keywords[] = {
    "ConstString",
    "ConstNumber",
    "Identifier"
};

token_t symbolIndex2token_t (int i) {
  return (token_t)(51+i);
}
token_t keywordIndex2token_t (int i) {
  return (token_t)(1+i);
}
const char* token_t2str (token_t i) {
  if (1 <= i && i <= 10) return predefined_keywords[i-1];
  if (11 <= i && i < 50) {
    if (i - 10 > sizeof(my_defined_keywords) / sizeof(char*)) {
      parse_error("token_t to string error: ask for %d\n", i);
    }
    return my_defined_keywords[i-11];
  }
  if (i > 50) return predefined_symbols[i-51];
}

const char *format_token_types (const token_t t[], int n) {
  string *buf = empty_string();
  append_const_str(buf, "token types:");
  for (int i = 0; i < n; i++) {
    append_char(buf, '[');
    append_const_str(buf, token_t2str(t[i]));
    append_const_str(buf, "], ");
  }
  append_char(buf, '\n');
  return buf->data;
}


