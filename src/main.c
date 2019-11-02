
#include "util/string.h"
#include <stdio.h>
#include "lexer/lexer.h"
int main(int argc, char *argv[]) {
  string s;
  s.data = "123";
  printf("test: %s\n", s.data);

  return 0;
}