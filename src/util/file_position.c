//
// Created by dasin on 2019/11/1.
//


#include "util/file_position.h"

void update_filepos(filepos *pos, int l, int c) {
  pos->line += l;
  pos->column += c;
}
void update_filepos_nextline(filepos *pos) {
  pos->line ++;
}
void update_filepos_forward(filepos *pos, int c) {
  pos->column += c;
}

