//
// Created by dasin on 2019/11/1.
//

#ifndef PARSER_SRC_UTIL_DEFS_H_
#define PARSER_SRC_UTIL_DEFS_H_

#include "../util/string.h"
#include "../error/parse_error.h"

typedef int token_t;

#define TIf           1
#define TElse         2
#define TWrite        3
#define TRead         4
#define TReturn       5
#define TBegin        6
#define TEnd          7
#define TMain         8
#define TInt          9
#define TReal         10
#define TConstString  11
#define TConstNumber  12
#define TIdentifier   13

#define TSemi     51
#define TComma    52
#define TLParen   53
#define TRParen   54
#define TPlus     55
#define TMinus    56
#define TMult     57
#define TDiv      58
#define TAssign   59
#define TEqual    60
#define TNotEqual 61

extern const char *predefined_symbols[11];

extern const char *predefined_keywords[10];

extern const char *my_defined_keywords[3];

token_t symbolIndex2token_t (int i);
token_t keywordIndex2token_t (int i);
const char* token_t2str (token_t i);

const char *format_token_types (const token_t t[], int n);

#endif //PARSER_SRC_UTIL_DEFS_H_
