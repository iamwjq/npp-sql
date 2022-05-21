/**
 * @file sql.h
 * @author your name (you@domain.com)
 * @brief 完全采用CPP方式实现SQL转换
 * @version 0.1
 * @date 2022-05-11
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef SQL_H
#define SQL_H

#include <string>

/**
 * @brief mybatis log转换成sql，这个实现不是最快的，还可以继续优化
 *
 * @param mybatis_log 日志报文
 * @return std::string sql
 */
std::string to_sql(const std::string &mybatis_log);

#endif