//
// Created by dasin on 2019/11/2.
//

#ifndef PARSER_SRC_SYNTAX_DEF_H_
#define PARSER_SRC_SYNTAX_DEF_H_

typedef int ast_t;

/**
 * Toplevel structures
 */
const ast_t SProgram      = 1;
const ast_t SMethodDecl   = 2;
const ast_t SFormalParams = 3;
const ast_t SFormalParam  = 4;
const ast_t SType         = 5;

/**
 * Statemtents
 */
const ast_t SBlock        = 31;
const ast_t SStatement    = 32;
const ast_t SLocalVarDecl = 33;
const ast_t SAssignStmt   = 34;
const ast_t SReturnStmt   = 35;
const ast_t SIfStmt       = 36;
const ast_t SWriteStmt    = 37;
const ast_t SReadStmt     = 38;
const ast_t QString       = 39;

/**
 * Expression
 */
const ast_t SExpression     = 61;
const ast_t SMultiExpr      = 62;
const ast_t SPrimaryExpr    = 63;
const ast_t SBoolExpression = 64;
const ast_t SActualParams   = 65;

#endif //PARSER_SRC_SYNTAX_DEF_H_
