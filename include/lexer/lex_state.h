//
// Created by dasin on 2019/11/1.
//

#ifndef PARSER_SRC_LEXER_LEX_STATE_H_
#define PARSER_SRC_LEXER_LEX_STATE_H_

#include "util/file_position.h"
#include "util/util.h"
#include <assert.h>

typedef struct {
  char *sp; // str position
  const char *end;
  filepos fp;
} lex_state;

char* peek_lex_state (lex_state *lex);

char* forward_lex_state (lex_state *lex);

char* lex_state_match_word (lex_state *lex, const char *word) ;
char* lex_state_find_next_match (lex_state *lex, const char *word);

#endif //PARSER_SRC_LEXER_LEX_STATE_H_
