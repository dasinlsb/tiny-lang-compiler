//
// Created by dasin on 2019/11/1.
//

#ifndef PARSER_SRC_ERROR_COMPILATION_ERROR_H_
#define PARSER_SRC_ERROR_COMPILATION_ERROR_H_

#include <stdio.h>
#include <stdarg.h>
#include "../util/file_position.h"

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
#endif //PARSER_SRC_ERROR_COMPILATION_ERROR_H_
