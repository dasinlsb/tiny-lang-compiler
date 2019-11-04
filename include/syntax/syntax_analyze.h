//
// Created by dasin on 2019/11/2.
//

#ifndef PARSER_SRC_SYNTAX_SYNTAX_ANALYZE_H_
#define PARSER_SRC_SYNTAX_SYNTAX_ANALYZE_H_

#include "syntax_tree.h"
#include "lexer/token.h"
#include "syntax_analyze_input.h"


AST* syntax_analyze (const char *p_name, token_data **tokens);


#endif //PARSER_SRC_SYNTAX_SYNTAX_ANALYZE_H_
