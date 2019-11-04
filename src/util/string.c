//
// Created by dasin on 2019/11/1.
//


#include "util/string.h"

string* empty_string() {
  string *s = (string*)malloc(sizeof(string));
  s->len = 0;
  s->cap = 1;
  s->data = (char *)malloc(s->cap);
  s->data[0] = '\0';
  return s;
}

// twice cap
void expand_cap(string *s) {
  char *new_data = (char*)malloc(s->cap*2);
  memcpy(new_data, s->data, s->len);
  memset(new_data + s->len, 0, sizeof(char)*(s->cap*2 - s->len));
  free(s->data);
  s->data = new_data;
  s->cap *= 2;
}

int try_append(string *s, const char *from, int n) {
  if (s->len + n >= s->cap) return 0;
  memcpy(s->data + s->len, from, n);
  s->len += n;
  s->data[s->len] = '\0';
  return 1;
}
void append_const_str(string *s, const char *from) {
  int n = (int)strlen(from);
  while (!try_append(s, from, n)) {
    expand_cap(s);
  }
}
void append_chars(string *s, const char *from, int n) {
  while (!try_append(s, from, n)) {
    expand_cap(s);
  }
}
void append_char (string *s, char c) {
  char *cs = (char *)malloc(2);
  cs[0] = c;
  cs[1] = '\0';
  append_const_str(s, cs);
  free(cs);
}
void append_into(string *s, const string *t) {
  append_chars(s, t->data, t->len);
}




