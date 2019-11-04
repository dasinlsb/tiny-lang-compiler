//
// Created by dasin on 2019/11/3.
//


#include "syntax/parser_combinator.h"

sa_env_t* sa_env_empty () {
  sa_env_t *e = malloc(sizeof(sa_env_t));
  e->keys = NULL;
  e->values = NULL;
  return e;
}

sa_parser_t* find_parser_by_name (sa_env_t *env, const char *name) {
  int i;
  for (i = 0; i < (int)vector_size(env->keys); i++) {
    if (strcmp(env->keys[i], name) == 0) {
      return env->values[i];
    }
  }
  return NULL;
}

void insert_parser(sa_env_t *env, char *name, sa_parser_t* parser) {
  vector_push_back(env->keys, name);
  vector_push_back(env->values, parser);
}

sa_parser_t* sa_parser_empty() {
  sa_parser_t *p = (sa_parser_t*)malloc(sizeof(sa_parser_t));
  p->type = 0;
  p->info = 0;
  p->name = NULL;
  return p;
}

int sa_run_parser (sa_input_t *in, sa_env_t *env, sa_parser_t *p, sa_result_t **r) {
  int j;
  sa_result_t *result = NULL;
  *r = (sa_result_t*)malloc(sizeof(sa_result_t));
  (*r)->ast = empty_syntax_tree();
  (*r)->ast->type = p->info;
  switch (p->type) {
    case SA_TYPE_AND: {
      sa_input_push_mark(in);
      for (j = 0; j < p->data.and.n; j++) {
        if (sa_run_parser(in, env, p->data.and.ps[j], &result)) {
          append_ast_child((*r)->ast, result->ast);
        } else {
          (*r)->ast = NULL;
          sa_input_pop_mark(in);
          return 0;
        }
      }
      ast_move_child_up(&(*r)->ast);
      return 1;
    }
    case SA_TYPE_GRAMMAR: {
      sa_parser_t *parser = find_parser_by_name(env, p->data.grammar.name);
      assert(parser != NULL);
      if (sa_run_parser(in, env, parser, &result)) {
        (*r)->ast = result->ast;
        return 1;
      } else {
        (*r)->ast = NULL;
        return 0;
      }
    }
    case SA_TYPE_IGNORE: {
      if (sa_run_parser(in, env, p->data.ignore.p, &result)) {
        (*r)->ast = NULL;
        return 1;
      } else {
        (*r)->ast = NULL;
        return 0;
      }
    }
    // 0 or more times
    case SA_TYPE_MANY: {
      while (1) {
        if (sa_run_parser(in, env, p->data.repeat.p, &result)) {
          append_ast_child((*r)->ast, result->ast);
        } else {
          break;
        }
      }
      ast_move_child_up(&(*r)->ast);
      return 1;
    }
    case SA_TYPE_MAYBE: {
      if (sa_run_parser(in, env, p->data.maybe.p, &result)) {
        append_ast_child((*r)->ast, result->ast);
      } else {

      }
      ast_move_child_up(&(*r)->ast);
      return 1;
    }
    // 1 or more times
    case SA_TYPE_SOME: {
      j = 0;
      while (1) {
        if (sa_run_parser(in, env, p->data.repeat.p, &result)) {
          append_ast_child((*r)->ast, result->ast);
          j++;
        } else {
          break;
        }
      }
      ast_move_child_up(&(*r)->ast);
      return j > 0;
    }
    case SA_TYPE_OR: {
      for (j = 0; j < p->data.or.n; j++) {
        if (sa_run_parser(in, env, p->data.or.ps[j], &result)) {
          (*r)->ast = result->ast;
          return 1;
        }
      }
      (*r)->ast = NULL;
      return 0;
    }
    case SA_TYPE_TOKEN: {
      token_data *token = sa_peek_input(in);
      if (token != NULL && token->type == p->data.token.t) {
        sa_forward_input(in);
        append_ast_token((*r)->ast, token);
        return 1;
      } else {
        return 0;
      }
    }
  }
}

sa_parser_t* sa_make_and (int n, ...) {
  int i;
  sa_parser_t *p = sa_parser_empty();
  p->type = SA_TYPE_AND;
  p->data.and.n = n;
  p->data.and.ps = malloc(sizeof(sa_parser_t*) * n);
  va_list(va);
  va_start(va, n);
  for (i = 0; i < n; i++) {
    p->data.and.ps[i] = va_arg(va, sa_parser_t*);
  }
  va_end(va);
  return p;
}

sa_parser_t* sa_make_ignore (sa_parser_t* parser) {
  sa_parser_t *p = sa_parser_empty();
  p->type = SA_TYPE_IGNORE;
  p->data.ignore.p = parser;
  return p;
}

sa_parser_t* sa_make_grammar (char *name) {
  sa_parser_t *p = sa_parser_empty();
  p->type = SA_TYPE_GRAMMAR;
  p->data.grammar.name = name;
  return p;
}

sa_parser_t* sa_make_many (sa_parser_t* parser) {
  int i;
  sa_parser_t *p = sa_parser_empty();
  p->type = SA_TYPE_MANY;
  p->data.repeat.p = parser;
  return p;
}

sa_parser_t* sa_make_maybe (sa_parser_t *parser) {
  sa_parser_t *p = sa_parser_empty();
  p->type = SA_TYPE_MAYBE;
  p->data.maybe.p  = parser;
  return p;
}

sa_parser_t* sa_make_or (int n, ...) {
  int i;
  sa_parser_t *p = sa_parser_empty();
  p->type = SA_TYPE_OR;
  p->data.or.n = n;
  p->data.or.ps = malloc(sizeof(sa_parser_t*) * n);
  va_list(va);
  va_start(va, n);
  for (i = 0; i < n; i++) {
    p->data.or.ps[i] = va_arg(va, sa_parser_t*);
  }
  va_end(va);
  return p;
}

sa_parser_t* sa_make_some (sa_parser_t *parser) {
  sa_parser_t *p = sa_parser_empty();
  p->type = SA_TYPE_SOME;
  p->data.repeat.p = parser;
  return p;
}

sa_parser_t* sa_make_token (token_t t) {
  sa_parser_t *p = sa_parser_empty();
  p->type = SA_TYPE_TOKEN;
  p->data.token.t = t;
  return p;
}
