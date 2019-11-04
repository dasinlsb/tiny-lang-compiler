//
// Created by dasin on 2019/11/4.
//

#ifndef PARSER_INCLUDE_UTIL_LOG_H_
#define PARSER_INCLUDE_UTIL_LOG_H_

static int DEBUG_LEVEL = 1;

#define DebugLog(i,fmt,...) do { \
if (i<=DEBUG_LEVEL) printf(fmt, __VA_ARGS__); \
} while(0);


#endif //PARSER_INCLUDE_UTIL_LOG_H_
