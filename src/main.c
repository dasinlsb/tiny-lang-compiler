
#include <stdio.h>
#include "lexer/lexer.h"
#include "syntax/syntax_analyze.h"
#include "lexer/token.h"

char buffer[1<<12];

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
  raw_program = buffer;
  fprintf(out,"scanned program:\n");
  fprintf(out, "%s\n", buffer);
  fprintf(out, "---------------\n");
  fflush(out);
  token_data **tokens = lexer(buffer);
  fprintf(out, "tokens:\n");
  fprintf(out, "%s", format_tokens((const token_data**)tokens));
  fprintf(out, "---------------\n");
  fflush(out);
  AST *ast = syntax_analyze(parser_name, tokens);
  fprint_ast(ast, out, 0);
  fprintf(out, "------FINISHED-----");
  fflush(out);
  fclose(out);
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    fprintf(stderr, "usage: ./main parser-name file-suffix");
    fprintf(stderr, "e.g. ./main prog sample will parse ./data/r-sample and output result to ./data/w-sample");
    exit(1);
  }
  const char *parser_name = argv[1];
  const char *file_name = argv[2];
  my_test(parser_name, file_name);
  return 0;
}