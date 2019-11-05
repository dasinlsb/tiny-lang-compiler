//
// Created by dasin on 2019/11/1.
//




#include "error/parse_error.h"
#include "util/string.h"

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

char *raw_program;

#define FUCK_PRINT(...) do { \
offset = snprintf(buf+cur, n-cur,  __VA_ARGS__); \
cur += offset; \
} while(0);

void global_parse_error_with_pos (filepos *pos, const char *fmt, ...) {
  static char buf[1<<10];
  int i, r, c, cur, n, offset;
  if (pos == NULL) {
    r = 1; c = 1;
    for (i = 0; raw_program[i] != '\0'; i++) {
      if (raw_program[i] == '\n') r++, c = 0;
      c++;
    }
    pos = malloc(sizeof(filepos));
    pos->line = r; pos->column = c;
  }
  cur = 0; n = sizeof(buf);
  FUCK_PRINT("[Line %d, Column %d]:\n", pos->line, pos->column)
  for (r = 1, i = 0; raw_program[i] != '\0' && r <= pos->line; i++) {
    if (r == pos->line) {
      FUCK_PRINT("%c", raw_program[i])
    }
    if (raw_program[i] == '\n') r++;
  }
  if (cur == 0 || buf[cur-1] != '\n') {
    FUCK_PRINT("\n")
  }
  for (i = 0; i < pos->column-1; i++) {
    FUCK_PRINT(" ")
  }
  FUCK_PRINT("^\n")
  for (i = 0; i < pos->column-1; i++) {
    FUCK_PRINT(" ")
  }
  va_list list;
  va_start(list, fmt);
  FUCK_PRINT(fmt, list)
  va_end(list);
  parse_error(buf);
}
