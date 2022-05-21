cmake_minimum_required(VERSION 3.10)
project(NppSql)
# 插件是一个dll，所以我们的编译目标也就是一个dll
add_library(NppSql SHARED src/framework/NppPluginDemo.cpp src/framework/PluginDefinition.cpp src/app.cpp src/sql/sql.cpp)
# target_link_libraries(NppApple libcurl.lib)
# target_include_directories(NppApple PUBLIC "${PROJECT_SOURCE_DIR}/include")

#用来测试
# add_definitions(-DTEST)
# add_executable(NppApple src/str.cpp src/mystr.cpp)
# add_executable(NappApple src/sql/sql.cpp)
# add_executable(NappApple src/sql2/sql2.cpp src/mystr/mystr.cpp)
# add_executable(NappApple test/string-test.cpp)
# 宏定义
add_compile_definitions(_UNICODE UNICODE)