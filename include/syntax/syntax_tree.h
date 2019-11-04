//
// Created by dasin on 2019/11/2.
//

#ifndef PARSER_SRC_SYNTAX_SYNTAX_TREE_H_
#define PARSER_SRC_SYNTAX_SYNTAX_TREE_H_

#include "../util/vector.h"
#include "../lexer/token.h"

typedef struct syntax_tree AST;

typedef int ast_node_t;

enum {
  AST_NODE_PROG = 1,
  AST_NODE_METHOD_DECL = 2,
  AST_NODE_FORMAL_PARAMS = 3,
  AST_NODE_FORMAL_PARAM = 4,
  AST_NODE_TYPE = 5,
  AST_NODE_BLOCK = 6,
  AST_NODE_STMT = 7,
  AST_NODE_LOCAL_VAR_DECL = 8,
  AST_NODE_ASSIGN_STMT = 9,
  AST_NODE_RETURN_STMT = 10,
  AST_NODE_IF_STMT = 11,
  AST_NODE_WRITE_STMT = 12,
  AST_NODE_READ_STMT = 13,
  AST_NODE_QSTRING = 14,
  AST_NODE_EXPR = 15,
  AST_NODE_MULTI_EXPR = 16,
  AST_NODE_PRIMARY_EXPR = 17,
  AST_NODE_BOOL_EXPR = 18,
  AST_NODE_ACTUAL_EXPR = 19,

  AST_NODE_IGNORE = 100,
  AST_NODE_VIRT = 101
};

/**
 * @brief inner defination of AST
 * @field children - child nodes of AST
 * @field tokens - data represented by array of tokens
 */
struct syntax_tree {
  ast_node_t type;
  struct syntax_tree **children;
  token_data **tokens;
};

AST* empty_syntax_tree ();

void append_ast_child (AST *ast, AST *child);

void append_ast_token (AST *ast, token_data *token);

void fprint_ast (AST *ast, FILE *out, int indent);

#endif //PARSER_SRC_SYNTAX_SYNTAX_TREE_H_
