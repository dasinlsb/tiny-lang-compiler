//
// Created by dasin on 2019/11/1.
//

#ifndef PARSER_SRC_UTIL_FILE_POSITION_H_
#define PARSER_SRC_UTIL_FILE_POSITION_H_

typedef struct {
  int line;
  int column;
} filepos;

void update_filepos(filepos *pos, int l, int c);
void update_filepos_nextline(filepos *pos);
void update_filepos_forward(filepos *pos, int c);
#endif //PARSER_SRC_UTIL_FILE_POSITION_H_
