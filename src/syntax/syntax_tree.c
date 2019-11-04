//
// Created by dasin on 2019/11/2.
//

#include "syntax/syntax_tree.h"





AST* empty_syntax_tree () {
  AST *ast = (AST*)malloc(sizeof(AST));
  ast->type = (ast_node_t)0;
  ast->children = NULL;
  ast->tokens = NULL;
  return ast;
}

void append_ast_child (AST *ast, AST *child) {
  assert(ast != NULL);
  assert(child != NULL);
  vector_push_back(ast->children, child);
}

void append_ast_token (AST *ast, token_data *token) {
  vector_push_back(ast->tokens, token);
}

void fprint_ast (AST *ast, FILE *out, int indent) {
  if (ast == NULL) return;
  int i;
  for (i = 0; i < indent; i++) {
    if (i < indent - 1)fputc(' ', out);
    if (i == indent-1) fputc('-', out);
  }
  switch (ast->type) {
    case AST_NODE_PROG: {
      fprintf(out, "prog");
      break;
    }
    case AST_NODE_METHOD_DECL: {
     fprintf(out, "method");
      break;
    }
    case AST_NODE_FORMAL_PARAMS: {
     fprintf(out, "params");
      break;
    }
    case AST_NODE_FORMAL_PARAM: {
     fprintf(out, "param");
      break;
    }
    case AST_NODE_TYPE: {
     fprintf(out, "type");
      break;
    }
    case AST_NODE_BLOCK: {
     fprintf(out, "block");
      break;
    }
    case AST_NODE_STMT: {
     fprintf(out, "stmt");
      break;
    }
    case AST_NODE_LOCAL_VAR_DECL: {
     fprintf(out, "var decl");
      break;
    }
    case AST_NODE_ASSIGN_STMT: {
     fprintf(out, "assign");
      break;
    }
    case AST_NODE_RETURN_STMT : {
     fprintf(out, "return ");
      break;
    }
    case AST_NODE_IF_STMT : {
     fprintf(out, "if");
      break;
    }
    case AST_NODE_WRITE_STMT : {
     fprintf(out, "write");
      break;
    }
    case AST_NODE_READ_STMT : {
     fprintf(out, "read");
      break;
    }
    case AST_NODE_QSTRING : {
     fprintf(out, "Qstring");
      break;
    }
    case AST_NODE_EXPR : {
     fprintf(out, "expr");
      break;
    }
    case AST_NODE_MULTI_EXPR : {
     fprintf(out, "multi expt");
      break;
    }
    case AST_NODE_PRIMARY_EXPR : {
     fprintf(out, "prim expr");
      break;
    }
    case AST_NODE_BOOL_EXPR : {
     fprintf(out, "bool expr");
      break;
    }
    case AST_NODE_ACTUAL_EXPR : {
     fprintf(out, "actual expr");
      break;
    }
   case AST_NODE_IGNORE : {
     fprintf(out, "IGNORE");
     break;
   }
  }
  fprintf(out, " : ");
  for (i = 0; i < (int)vector_size(ast->tokens); i++) {
    fprint_token(out, ast->tokens[i]);
    fprintf(out, " ");
  }
  fprintf(out, "\n");
  for (i = 0; i < (int)vector_size(ast->children); i++) {
    fprint_ast(ast->children[i], out, indent+2);
  }
}

