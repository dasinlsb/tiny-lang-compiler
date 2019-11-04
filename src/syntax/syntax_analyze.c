//
// Created by dasin on 2019/11/2.
//

#include "syntax/syntax_analyze.h"
#include "syntax/syntax_analyze_input.h"
#include "syntax/parser_combinator.h"
#include "util/log.h"

static char* toplevel_parse_error = NULL;

#define MK_DEFN(n,t,p) do {\
sa_parser_t *parser = p; \
parser->name = #n; \
parser->info = t; \
DebugLog(3,"made defination name[%s] info[%d]\n", #n, t); \
insert_parser(sa_global_env, #n, parser); \
} while(0);


/**
 * Toplevels
 */


static sa_env_t *sa_global_env;

void make_parsers () {
  sa_global_env = sa_env_empty();
  // Program -> MethodDecl+
  MK_DEFN(prog,
      AST_NODE_PROG,
      MK_SOME(MK_GRAMMAR(method_decl))
  )
  // MethodDecl -> Type [MAIN] Id '(' FormalParams ')' Block
  MK_DEFN(method_decl,
      AST_NODE_METHOD_DECL,
  MK_AND(
      MK_GRAMMAR(type),
      MK_MAYBE(MK_TOKEN(TMain)),
      MK_TOKEN(TIdentifier),
      MK_TOKEN_I(TLParen),
      MK_GRAMMAR(formal_params),
      MK_TOKEN_I(TRParen),
      MK_GRAMMAR(block)
  ))
  // FormalParams -> [FormalParam (',' FormalParam)*]
  MK_DEFN(formal_params,
      AST_NODE_FORMAL_PARAMS,
      MK_MAYBE(MK_AND(
          MK_GRAMMAR(formal_param),
          MK_MANY(MK_AND(
              MK_TOKEN_I(TComma),
              MK_GRAMMAR(formal_param)
              ))
      )))

  // FormalParam -> Type Id
  MK_DEFN(formal_param,
      AST_NODE_FORMAL_PARAM,
      MK_AND(
          MK_GRAMMAR(type),
          MK_TOKEN(TIdentifier)
          ))
  // Type -> INT | REAL
  MK_DEFN(type,
      AST_NODE_FORMAL_PARAM,
      MK_OR(
          MK_TOKEN(TInt),
          MK_TOKEN(TReal)
      ))
  /**
   *  Statement
   */
   // Block -> BEGIN Statement* END
   MK_DEFN(block,
       AST_NODE_BLOCK,
       MK_AND(
           MK_TOKEN_I(TBegin),
           MK_MANY(MK_GRAMMAR(stmt)),
           MK_TOKEN_I(TEnd)
       ))
  // Statement -> ...
  MK_DEFN(stmt,
      AST_NODE_STMT,
      MK_OR(
          MK_GRAMMAR(block),
          MK_GRAMMAR(local_var_decl),
          MK_GRAMMAR(assign_stmt),
          MK_GRAMMAR(return_stmt),
          MK_GRAMMAR(if_stmt),
          MK_GRAMMAR(write_stmt),
          MK_GRAMMAR(read_stmt)
      ))
  // LocalVarDecl -> INT Id ';' | REAL Id ';'
  MK_DEFN(local_var_decl,
      AST_NODE_LOCAL_VAR_DECL,
      MK_OR(
          MK_AND(
              MK_TOKEN(TInt),
              MK_TOKEN(TIdentifier),
              MK_TOKEN_I(TSemi)
              ),
          MK_AND(
              MK_TOKEN(TReal),
              MK_TOKEN(TIdentifier),
              MK_TOKEN_I(TSemi)
              )
      ))
  // AssignStmt -> Id := Expr ';'
  MK_DEFN(assign_stmt,
      AST_NODE_ASSIGN_STMT,
      MK_AND(
          MK_TOKEN(TIdentifier),
          MK_TOKEN_I(TAssign),
          MK_GRAMMAR(expr),
          MK_TOKEN_I(TSemi)
      ))
  // ReturnStmt -> RETURN Expr ';'
  MK_DEFN(return_stmt,
      AST_NODE_RETURN_STMT,
      MK_AND(
          MK_TOKEN(TReturn),
          MK_GRAMMAR(expr),
          MK_TOKEN_I(TSemi)
      ))
  // IfStmt -> IF '(' BoolExpr ')' Stmt
  //         | IF '(' BoolExpr ')' Stmt ELSE Stmt
  MK_DEFN(if_stmt,
      AST_NODE_IF_STMT,
  MK_OR(
      MK_AND(
          MK_TOKEN(TIf),
          MK_TOKEN_I(TLParen),
          MK_GRAMMAR(bool_expr),
          MK_TOKEN_I(TRParen),
          MK_GRAMMAR(stmt),
          MK_TOKEN(TElse),
          MK_GRAMMAR(stmt)
          ),
      MK_AND(
          MK_TOKEN(TIf),
          MK_TOKEN_I(TLParen),
          MK_GRAMMAR(bool_expr),
          MK_TOKEN_I(TRParen),
          MK_GRAMMAR(stmt)
          )
  ))
  // WriteStmt -> WRITE '(' Expr ',' QString ')' ';'
  MK_DEFN(write_stmt,
      AST_NODE_WRITE_STMT,
      MK_AND(
          MK_TOKEN(TWrite),
          MK_TOKEN_I(TLParen),
          MK_GRAMMAR(expr),
          MK_TOKEN_I(TComma),
          MK_TOKEN(TConstString),
          MK_TOKEN_I(TRParen),
          MK_TOKEN_I(TSemi)
      ))
  // ReadStmt -> READ '(' Id ',' QString ')' ';'
  MK_DEFN(read_stmt,
      AST_NODE_READ_STMT,
      MK_AND(
          MK_TOKEN(TRead),
          MK_TOKEN_I(TLParen),
          MK_TOKEN(TIdentifier),
          MK_TOKEN_I(TComma),
          MK_TOKEN(TConstString),
          MK_TOKEN_I(TRParen),
          MK_TOKEN_I(TSemi)
      ))
  /**
   * Expressions
   */
  // Expr -> MultiExpr (('+'|'-') MultiExpr)*
  MK_DEFN(expr,
      AST_NODE_EXPR,
      MK_AND(
          MK_GRAMMAR(multi_expr),
          MK_MANY(
              MK_AND(
              MK_OR(
                  MK_TOKEN(TPlus),
                  MK_TOKEN(TMinus)
                  ),
              MK_GRAMMAR(multi_expr)
              ))
      ))
  // MultiExpr-> PrimaryExpr -> (('*'|'/') PrimaryExpr)*
  MK_DEFN(multi_expr,
      AST_NODE_MULTI_EXPR,
      MK_AND(
          MK_GRAMMAR(primary_expr),
          MK_MANY(
              MK_AND(
                  MK_OR(
                      MK_TOKEN(TMult),
                      MK_TOKEN(TDiv)
                  ),
                  MK_GRAMMAR(primary_expr)
                  )
          )
      )
  )
  // PrimaryExpr -> Num | Id | '(' Expr ')' | Id '(' ActualParams ')'
  MK_DEFN(primary_expr,
      AST_NODE_PRIMARY_EXPR,
          MK_OR(
              MK_TOKEN(TConstNumber),
              MK_AND(
                  MK_TOKEN_I(TLParen),
                  MK_GRAMMAR(expr),
                  MK_TOKEN_I(TRParen)
                  ),
              MK_AND(
                  MK_TOKEN(TIdentifier),
                  MK_TOKEN_I(TLParen),
                  MK_GRAMMAR(actual_params),
                  MK_TOKEN_I(TRParen)
                  ),
              MK_TOKEN(TIdentifier)
              )
      )
  // BoolExpr -> Expr '==' Expr | Expr '!=' Expr
  MK_DEFN(bool_expr,
      AST_NODE_ACTUAL_PARAMS,
      MK_OR(
          MK_AND(
              MK_GRAMMAR(expr),
              MK_TOKEN(TEqual),
              MK_GRAMMAR(expr)
              ),
          MK_AND(
              MK_GRAMMAR(expr),
              MK_TOKEN(TNotEqual),
              MK_GRAMMAR(expr)
              )
      )
  )
  // ActualParams -> [Expr (',' Expr)*]
  MK_DEFN(actual_params,
      AST_NODE_ACTUAL_PARAMS,
      MK_MAYBE(
          MK_AND(
              MK_GRAMMAR(expr),
              MK_MANY(MK_AND(
                  MK_TOKEN_I(TComma),
                  MK_GRAMMAR(expr)
                  )))
      ))
}


AST* syntax_analyze (const char *p_name, token_data **tokens) {
  make_parsers();
  sa_input_t *i = sa_input_create(tokens);
  sa_parser_t *p = find_parser_by_name(sa_global_env, p_name);
  sa_result_t *r;
  if (sa_run_parser(i, sa_global_env, p, &r)) {
    if (sa_peek_input(i) == NULL) {
      return r->ast;
    } else {
      parse_error("not consumed all input");
    }
  } else {
    parse_error("parse AST error");
  }
}