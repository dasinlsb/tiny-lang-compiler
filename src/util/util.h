//
// Created by dasin on 2019/11/1.
//

#ifndef PARSER_SRC_UTIL_UTIL_H_
#define PARSER_SRC_UTIL_UTIL_H_

#include "../error/parse_error.h"
#include <ctype.h>

char escape_char (char c) {
  if (c == 'a') return '\a';
  if (c == 'b') return '\b';
  if (c == 'n') return '\n';
  if (c == 'r') return '\r';
  if (c == 't') return '\t';
  if (c == '\\') return c;
  if (c == '\'') return c;
  if (c == '\"') return c;
  parse_error("unknown escaped char: %c", c);
}

int is_number (char c) {
  return isdigit(c) || c == '.';
}

int is_identifier_head (char c) {
  return isalpha(c) || c == '_';
}
int is_identifier_body (char c) {
  return is_identifier_head(c) || isdigit(c);
}

/**
 * @return char* - if success then consume strlen(word) chars else NULL
 */
char* match_word (char *begin, const char *end, const char *word) {
  int n = (int)strlen(word);
  if (n > (end - begin)) return NULL;
  for (int i = 0; i < n; i++) {
    if (begin + i >= end || *(begin + i) != word[i]) return NULL;
  }
  return begin + n;
}

char* find_next_match (char *begin, const char *end, const char *word) {
  char *next;
  for (; begin < end; begin ++) {
    if ((next = match_word(begin, end, word)) != NULL) {
      return next;
    }
  }
  return NULL;
}

#endif //PARSER_SRC_UTIL_UTIL_H_
