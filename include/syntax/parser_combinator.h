//
// Created by dasin on 2019/11/3.
//

#ifndef PARSER_SRC_SYNTAX_PARSER_COMBINATOR_H_
#define PARSER_SRC_SYNTAX_PARSER_COMBINATOR_H_

#include "../util/util.h"
#include "../lexer/token.h"
#include "syntax_analyze_input.h"
#include "syntax_tree.h"
#include "parse_env.h"


enum {
  SA_TYPE_AND = 1,
  SA_TYPE_GRAMMAR = 8,
  SA_TYPE_IGNORE = 2,
  SA_TYPE_MANY = 3,
  SA_TYPE_OR = 4,
  SA_TYPE_SOME = 5,
  SA_TYPE_TOKEN = 6,
  SA_TYPE_MAYBE = 7
};

struct sa_parser_t;
typedef struct sa_parser_t sa_parser_t;

typedef struct { int n; sa_parser_t **ps; } sa_pdata_and_t;
typedef struct { char *name; } sa_pdata_grammar_t;
typedef struct { sa_parser_t *p; } sa_pdata_ignore_t;
typedef struct { sa_parser_t *p; } sa_pdata_maybe_t;
typedef struct { int n; sa_parser_t **ps; } sa_pdata_or_t;
typedef struct { sa_parser_t *p; } sa_pdata_repeat_t;
typedef struct { token_t t; } sa_pdata_token_t;


typedef union {
  sa_pdata_and_t and;
  sa_pdata_grammar_t grammar;
  sa_pdata_ignore_t ignore;
  sa_pdata_maybe_t maybe;
  sa_pdata_or_t or;
  sa_pdata_repeat_t repeat;
  sa_pdata_token_t token;
} sa_pdata_t;

struct sa_parser_t {
  char *name;
  ast_node_t info;
  int type;
  sa_pdata_t data;
};

typedef struct {
  AST *ast;
  char *err_msg;
} sa_result_t;

typedef struct {
  char **keys;
  sa_parser_t **values;
} sa_env_t;

sa_env_t* sa_env_empty ();

sa_parser_t* find_parser_by_name (sa_env_t *env, const char *name);

void insert_parser(sa_env_t *env, char *name, sa_parser_t* parser) ;

int sa_run_parser (sa_input_t *in, sa_env_t *env, sa_parser_t *parser, sa_result_t **res);
sa_parser_t* sa_make_and (int n, ...);
sa_parser_t* sa_make_ignore (sa_parser_t* parser);
sa_parser_t* sa_make_grammar (char *name);
sa_parser_t* sa_make_many (sa_parser_t *parser);
sa_parser_t* sa_make_maybe (sa_parser_t *parser);
sa_parser_t* sa_make_or (int n, ...);
sa_parser_t* sa_make_some (sa_parser_t *parser);
sa_parser_t* sa_make_token (token_t t);

#define MK_OR(...) sa_make_or(PP_NARG(__VA_ARGS__), __VA_ARGS__)
#define MK_AND(...) sa_make_and(PP_NARG(__VA_ARGS__), __VA_ARGS__)
#define MK_MANY(p) sa_make_many(p)
#define MK_MAYBE(p) sa_make_maybe(p)
#define MK_SOME(p) sa_make_some(p)
#define MK_TOKEN(t) sa_make_token(t)
#define MK_GRAMMAR(s) sa_make_grammar(#s)
#define MK_IGNORE(p) sa_make_ignore(p)


#endif //PARSER_SRC_SYNTAX_PARSER_COMBINATOR_H_
