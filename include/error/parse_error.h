//
// Created by dasin on 2019/11/1.
//

#ifndef PARSER_SRC_ERROR_PARSE_ERROR_H_
#define PARSER_SRC_ERROR_PARSE_ERROR_H_

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "util/file_position.h"

void parse_error (const char *fmt, ...);

void parse_error_with_pos (filepos *pos, const char *fmt, ...);

extern char buf[100];

void global_set_parse_error_with_pos (filepos *pos, const char *fmt, ...);

void global_set_parse_error (const char *fmt, ...);

void global_pop_parse_error ();

#endif //PARSER_SRC_ERROR_PARSE_ERROR_H_
