//
// Created by dasin on 2019/11/1.
//

#ifndef PARSER_SRC_UTIL_STRING_H_
#define PARSER_SRC_UTIL_STRING_H_

#include <stdlib.h>
#include <string.h>
typedef struct {
  char *data;
  int len;
  int cap;
} string;

string* empty_string();

// twice cap
void expand_cap(string *s) ;

int try_append(string *s, const char *from, int n);
void append_const_str(string *s, const char *from);
void append_chars(string *s, const char *from, int n);
void append_char (string *s, char c) ;
void append_into(string *s, const string *t);



#endif //PARSER_SRC_UTIL_STRING_H_
