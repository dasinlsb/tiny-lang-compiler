//
// Created by dasin on 2019/11/2.
//

#include <criterion/criterion.h>
#include <string.h>
#include "../src/lexer/defs.h"
#include "../src/lexer/lexer.h"

const char* format_token_datas (const char *data[], int n) {
  string *buf = empty_string();
  append_const_str(buf, "token datas:");
  for (int i = 0; i < n; i++) {
    append_char(buf, '[');
    //printf("*** token datas: {%s}\n", data[i]);
    append_const_str(buf, data[i]);
    //printf("**  token buf  : {%s}\n", buf->data);
    append_const_str(buf, "], ");
  }
  append_char(buf, '\n');
  return buf->data;
}

#define judge_tokens_data(tokens,ans) do { \
if (ans == NULL && vector_size(tokens) == 0) break; \
int n = sizeof(ans) / sizeof(char*); \
if (n != vector_size(tokens)) { \
cr_log_warn("tokens do not have expected length with datas."); \
cr_log_info("%s", format_tokens(tokens)); \
cr_log_info("%s", format_token_datas(ans,n)); \
cr_assert(n == vector_size(tokens)); \
} \
for (int i = 0; i < n; i++) { \
if (strcmp(tokens[i]->data.data, ans[i]) != 0) { \
cr_log_warn("token datas incorrect."); \
cr_log_info("%s", format_tokens(tokens)); \
cr_log_info("%s", format_token_datas(ans,n)); \
cr_assert(strcmp(tokens[i]->data.data, ans[i]) == 0); \
} \
} \
} while(0);

#define judge_tokens_type(tokens,ans) do { \
if (ans == NULL && vector_size(tokens) == 0) break; \
int n = sizeof(ans) / sizeof(token_t); \
if (n != vector_size(tokens)) { \
cr_log_warn("tokens do not have expected length with types."); \
cr_log_info("%s", format_tokens(tokens)); \
cr_log_info("%s", format_token_types(ans,n)); \
cr_assert(n == vector_size(tokens)); \
} \
for (int i = 0; i < n; i++) { \
if (tokens[i]->type != ans[i]) { \
cr_log_warn("token types incorrect."); \
cr_log_info("%s", format_tokens(tokens)); \
cr_log_info("%s", format_token_types(ans,n)); \
cr_assert(tokens[i]->type == ans[i]); \
} \
} \
} while(0);

#define quick_check(input,s,t) do { \
const token_data **tokens = (const token_data **)lexer(input); \
judge_tokens_data(tokens,s) \
judge_tokens_type(tokens,t) \
} while(0);

Test(lexer, comment) {
  const char *input = " /**  \n \n\n **/";
  const char **s = NULL;
  const token_t *t = NULL;
  quick_check(input,s,t)
}

Test(lexer, READ) {
  const char *input = "READ(x, \"bob\");";
  const char *s[] = {"READ", "(", "x", ",", "\"bob\"", ")", ";"};
  const token_t t[] = {TRead, TLParen, TIdentifier, TComma, TConstString, TRParen, TSemi};
  quick_check(input,s,t)
}

Test(lexer, add_expr) {
  const char *input = "z := f1(x,y)+f2();";
  const char *s[] = {"z", ":=", "f1", "(", "x", ",", "y", ")", "+", "f2", "(", ")", ";"};
  const token_t t[] = {TIdentifier, TAssign,
                      TIdentifier, TLParen, TIdentifier, TComma, TIdentifier, TRParen,
                      TPlus,
                      TIdentifier, TLParen, TRParen, TSemi};
  quick_check(input,s,t)
}

Test(lexer, begin_end_block) {
  const char *input = "BEGIN \n\tINT x;\t\n\tEND";
  const char *s[] = {"BEGIN", "INT", "x", ";", "END"};
  const token_t t[] = {TBegin, TInt, TIdentifier, TSemi, TEnd};
  quick_check(input,s,t)
}

Test(lexer, begin_end_block_inside_block) {
  const char *input = "BEGIN\n \tINT  x;\n"
                      "BEGIN\nREAL  y;\nEND\n \t"
                      "END";
  const char *s[] = {"BEGIN", "INT", "x", ";",
                     "BEGIN", "REAL", "y", ";", "END",
                     "END"};
  const token_t t[] = {TBegin, TInt, TIdentifier, TSemi,
                      TBegin, TReal, TIdentifier, TSemi, TEnd,
                      TEnd};
  quick_check(input,s,t)
}