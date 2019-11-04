#引入pkg-config
find_package(PkgConfig)
#通过pkg-config获得criterion
pkg_check_modules(UNITTEST criterion)

#如果成功获取criterion说明机器是安装了criterion，可进入单测环节
if (UNITTEST_FOUND)
    #设置单元测试的源码
    include_directories(../include)
    add_library(lib_lex
            ../src/lexer/defs.c
            ../src/lexer/token.c
            ../src/lexer/lex_state.c
            ../src/lexer/lexer.c
            ../src/util/string.c
            ../src/util/util.c
            ../src/util/file_position.c ../include/util/log.h)

    aux_source_directory(../src/error lib_error_src)
    add_library(lib_error ${lib_error_src})
    set(UNITTEST_SOURCE test_lexer.c)
    #打开cmake测试编译
    enable_testing()
    #打印一些信息 提示用户在make之后执行make test就是单元测试
    message("-- be ready to run test case, usage: make && make test")
    #把所有的测试源码编译成可执行文件runtest
    add_executable(runtest ${UNITTEST_SOURCE} ${HEADER_FILES} ${SOURCE_FILES})
    #执行runtest需要criterion库依赖
    target_link_libraries(runtest ${UNITTEST_LIBRARIES} lib_lex util lib_error)
    add_test(runtest runtest)
endif (UNITTEST_FOUND)