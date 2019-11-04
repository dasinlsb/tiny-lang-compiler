//
// Created by dasin on 2019/11/1.
//




#include "error/parse_error.h"


void parse_error (const char *fmt, ...) {
  va_list list;
  va_start(list, fmt);
  fprintf(stderr, fmt, list);
  va_end(list);
  exit(1);
}

void parse_error_with_pos (filepos *pos, const char *fmt, ...) {
  fprintf(stderr, "[Line %d, Column %d]: ", pos->line, pos->column);
  va_list list;
  va_start(list, fmt);
  parse_error(fmt, list);
  va_end(list);
  exit(1);
}

char buf[100];

void global_set_parse_error_with_pos (filepos *pos, const char *fmt, ...) {
  snprintf(buf, sizeof(buf), "[Line %d, Column %d]: ", pos->line, pos->column);
  va_list list;
  va_start(list, fmt);
  snprintf(buf, sizeof(buf), fmt, list);
  va_end(list);
}

void global_set_parse_error (const char *fmt, ...) {
  va_list list;
  va_start(list, fmt);
  snprintf(buf, sizeof(buf), fmt, list);
  va_end(list);
}

void global_pop_parse_error () {
  parse_error(buf);
}


