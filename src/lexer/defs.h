//
// Created by dasin on 2019/11/1.
//

#ifndef PARSER_SRC_UTIL_DEFS_H_
#define PARSER_SRC_UTIL_DEFS_H_

#include "../util/string.h"
#include "../error/parse_error.h"

typedef int token_t;

const token_t TIf          = 1 ;
const token_t TElse        = 2 ;
const token_t TWrite       = 3 ;
const token_t TRead        = 4 ;
const token_t TReturn      = 5 ;
const token_t TBegin       = 6 ;
const token_t TEnd         = 7 ;
const token_t TMain        = 8 ;
const token_t TInt         = 9 ;
const token_t TReal        = 10;
const token_t TConstString = 11;
const token_t TConstNumber = 12;
const token_t TIdentifier  = 13;

const token_t TSemi     = 51;
const token_t TComma    = 52;
const token_t TLParen   = 53;
const token_t TRParen   = 54;
const token_t TPlus     = 55;
const token_t TMinus    = 56;
const token_t TMult     = 57;
const token_t TDiv      = 58;
const token_t TAssign   = 59;
const token_t TEqual    = 60;
const token_t TNotEqual = 61;

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
  if (i > 50) return (char *)predefined_symbols[i-51];
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

#endif //PARSER_SRC_UTIL_DEFS_H_
