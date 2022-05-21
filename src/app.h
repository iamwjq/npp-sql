#ifndef APP_H
#define APP_H

#define PLUGIN_NAME "NppSql"

/**
 * @brief 插件命令数量
 * 
 */
#define PLUGIN_COMMAND_NUM 2

/**
 * @brief 关于
 * 
 */
void about();

/**
 * @brief 转成SQL语句
 * 
 */
void toSql();

/**
 * @brief 写入一个新的文档中
 * 
 * @param content 写入的内容
 */
void write_in_new_docment(const char *content);
#endif