#include "sql.h"
#include <vector>
#include <regex>

class SqlParam
{
public:
    const std::string type;
    const std::string value;
    SqlParam(const std::string &t, const std::string &v) : type(t), value(v) {}
};

std::vector<SqlParam> parse_sql_param(const std::string preparing_line)
{
    std::regex null_pattern("^null((\\, )|$)");
    std::regex type_pattern("\\(([A-Z][A-Za-z]*)\\)((\\, )|)");
    std::smatch null_match;
    std::smatch type_match;

    std::vector<SqlParam> list;
    for (auto i = preparing_line.begin(), e = preparing_line.end(); i != e;)
    {
        if (std::regex_search(i, e, null_match, null_pattern))
        {
            list.push_back(SqlParam("null", "null"));
            i += null_match.position() + null_match.length();
        }
        else if (std::regex_search(i, e, type_match, type_pattern))
        {
            list.push_back(SqlParam(type_match.str(1).c_str(), std::string(i, i + type_match.position())));
            i += type_match.position() + type_match.length();
        }
        else
        {
            ++i;
        }
    }

    return list;
}

std::string substring(std::string str, std::size_t begin, std::size_t end)
{
    std::size_t count = end - begin;
    return str.substr(begin, count);
}

std::string to_sql(const std::string &mybatis_log)
{
    if (!mybatis_log.empty())
    {
        std::string preparing_pattern("==>  Preparing: ");
        std::string parameters_pattern("==> Parameters: ");
        std::size_t preparing_start = mybatis_log.find(preparing_pattern);
        std::size_t preparing_end = mybatis_log.find('\n', preparing_start);
        std::size_t parameters_start = mybatis_log.find(parameters_pattern);
        std::size_t parameters_end = mybatis_log.find('\n', parameters_start);

        if (preparing_start == std::string::npos || parameters_start == std::string::npos)
        {
            return "选中的内容非MYBATIS日志";
        }

        std::string preparing_line = substring(mybatis_log, preparing_start + preparing_pattern.length(), preparing_end);
        std::string parameters_line = substring(mybatis_log, parameters_start + parameters_pattern.length(), parameters_end);

        std::vector<SqlParam> params = parse_sql_param(parameters_line);
        auto params_i = params.begin();
        std::string result;
        for (auto i = preparing_line.begin(), e = preparing_line.end(); i != e; i++)
        {
            if (*i == '?')
            {
                if (params_i->type == "Integer" || params_i->type == "Long")
                {
                    result.append(params_i->value);
                }
                else
                {
                    result.push_back('\'');
                    result.append(params_i->value);
                    result.push_back('\'');
                }
                ++params_i;
            }
            else
            {
                result.push_back(*i);
            }
        }
        return result;
    }
    return "输入不能为空";
}

#ifdef TEST
#include <iostream>

int main()
{

    // std::vector<SqlParam> list = parse_sql_param("a(String), null, 202(Long), -3090(Long)");
    std::string sql = to_sql(R"(
2021-10-12 20:23:01.076 DEBUG 7648 --- [qtp613652233-34] m.s.e.m.BattleDataDao.queryBattleData    : ==>  Preparing: SELECT b.* FROM battle_data b INNER JOIN dictionary_target_type t ON b.fired_mblx=t.targetCode AND t.category=1 WHERE b.json_name=? AND b.fired_handle IN ( ? , ? , ? , ? , ? , ? , ? , ? , ? ) ORDER BY b.fired_handle,b.fire_handle
2021-10-12 20:23:01.076 DEBUG 7648 --- [qtp613652233-34] m.s.e.m.BattleDataDao.queryBattleData    : ==> Parameters: a(String), 2(Long), 3(Long), 19(Long), 4(Long), 36(Long), 5(Long), 6(Long), 7(Long), 26(Long)
    )");
    std::cout << sql << std::endl;
    return 0;
}

#endif