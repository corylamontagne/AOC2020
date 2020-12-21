export module Day19;

import std.core;
import AOCUtil;

namespace Day19
{
    export typedef std::map<int, std::map<int, std::vector<int> > > RuleMap;
    export typedef std::map<int, std::string> BaseRuleMap;
    constexpr char Pipe = '|';
    constexpr char Quote = '"';
    constexpr char Colon = ':';
    constexpr char Space = ' ';

    std::tuple<int, std::string> GetRuleNumber(const std::string& rule, char token)
    {
        std::vector<std::string> splitData = AOC::split(rule, token);
        return std::tuple<int, std::string>(std::stoi(splitData[0]), splitData[1]);
    }

    export std::tuple<RuleMap, BaseRuleMap> BuildRuleMap(const std::vector<std::string>& input)
    {
        RuleMap map;
        BaseRuleMap baseMap;
        for (auto data : input)
        {
            bool baseRule = false;
            std::map<int, std::vector<int>> rules;

            auto [ruleNumber, rule] = GetRuleNumber(data, Colon);

            if (ruleNumber == 68)
            {
                int i = 0;
            }

            if (rule.find(Pipe) != std::string::npos)
            {
                std::vector<std::string> splitData = AOC::split(rule, Pipe, false);

                int index = 0;
                for (auto i : splitData)
                {
                    if (i.find(Space) != std::string::npos)
                    {
                        std::vector<std::string> subRules = AOC::split(i, Space, true);
                        for (auto j : subRules)
                        {
                            if (!j.empty())
                            {
                                rules[index].push_back(std::stoi(j));
                            }
                        }
                    }
                    else
                    {
                        rules[index].push_back(std::stoi(i));
                    }
                    index++;
                }
            }
            else if (rule.find(Quote) != std::string::npos)
            {
                baseRule = true;
                rule.erase(remove(rule.begin(), rule.end(), '\"'), rule.end());
                rule.erase(remove(rule.begin(), rule.end(), ' '), rule.end());
                baseMap[ruleNumber] = rule[0];
            }
            else
            {
                std::vector<std::string> splitData = AOC::split(rule, Space, true);
                int index = 0;
                for (auto i : splitData)
                {
                    if (!i.empty())
                    {
                        rules[index].push_back(std::stoi(i));
                        index++;
                    }
                }
            }
            if (!baseRule)
            {
                map[ruleNumber] = rules;
            }
        }

        return { map, baseMap };
    }


    export int CountValidRules(const std::vector<std::string>&data, const RuleMap& ruleMap, const BaseRuleMap& baseRuleMap)
    {
        int result = 0;

        return result;
    }
}