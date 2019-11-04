//
// Created by dasin on 2019/11/1.
//

#include "lexer/lex_state.h"


char* peek_lex_state (lex_state *lex) {
  if (lex->sp == lex->end) return NULL;
  return lex->sp;
}

char* forward_lex_state (lex_state *lex) {
  assert(lex->sp <= lex->end);
  if (lex->sp == lex->end) return NULL;
  if (*lex->sp == '\n') {
    update_filepos_nextline(&lex->fp);
  } else {
    update_filepos_forward(&lex->fp, 1);
  }
  lex->sp++;
  return lex->sp;
}

char* lex_state_match_word (lex_state *lex, const char *word) {
  return match_word(lex->sp, lex->end, word);
}
char* lex_state_find_next_match (lex_state *lex, const char *word) {
  return find_next_match(lex->sp, lex->end, word);
}


