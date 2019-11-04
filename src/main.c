
#include <stdio.h>
#include "lexer/lexer.h"
#include "syntax/syntax_analyze.h"
#include "lexer/token.h"

char buffer[1<<10];

void my_test(const char *parser_name, const char *spec) {
  char out_name[20];
  char in_name[20];
  sprintf(out_name, "../data/w-%s", spec);
  sprintf(in_name, "../data/r-%s", spec);
  FILE *out = fopen(out_name, "w");
  if (out == NULL) {
    fprintf(stderr, "cannot open output file %s\n", out_name);
    exit(1);
  }
  FILE *in = fopen(in_name, "r");
  if (in == NULL) {
    fprintf(stderr, "cannot open input file %s\n", in_name);
    exit(1);
  }
  fread(buffer, 1, sizeof(buffer), in);
  fclose(in);
  fprintf(out,"scanned program:\n");
  fprintf(out, "%s\n", buffer);
  fprintf(out, "---------------\n");
  token_data **tokens = lexer(buffer);
  fprintf(out, "tokens:\n");
  fprintf(out, "%s\n", format_tokens((const token_data**)tokens));
  fprintf(out, "---------------\n");
  AST *ast = syntax_analyze(parser_name, tokens);
  fprint_ast(ast, out, 0);
  fprintf(out, "------FINISHED-----");
  fclose(out);
}

int main(int argc, char *argv[]) {
  my_test("block", "block");
  my_test("expr", "expr");
  //my_test("prog", 1);
  //my_test("read_stmt", 2);
  return 0;
}