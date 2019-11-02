#引入pkg-config
find_package(PkgConfig)
#通过pkg-config获得criterion
pkg_check_modules(UNITTEST criterion)

#如果成功获取criterion说明机器是安装了criterion，可进入单测环节
if (UNITTEST_FOUND)
    #设置单元测试的源码
    set(UNITTEST_SOURCE test_lexer.c)
    #打开cmake测试编译
    enable_testing()
    #打印一些信息 提示用户在make之后执行make test就是单元测试
    message("-- be ready to run test case, usage: make && make test")
    #把所有的测试源码编译成可执行文件runtest
    add_executable(runtest ${UNITTEST_SOURCE} ${HEADER_FILES} ${SOURCE_FILES})
    #执行runtest需要criterion库依赖
    target_link_libraries(runtest ${UNITTEST_LIBRARIES})
    add_test(runtest runtest)
endif (UNITTEST_FOUND)