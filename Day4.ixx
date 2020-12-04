export module Day4;

import std.core;
import std.regex;

namespace Day4
{
    export unsigned int CountValidPassports(const std::map<int, std::vector<std::string>>& input, const std::map<std::string, std::string>& requiredFields, bool validate)
    {
        unsigned int result = 0;

        for (auto pp : input)
        {
            //isolate the required set of codes from the required fields to ensure we get them all
            std::vector<std::string> codes;
            std::transform(requiredFields.begin(), requiredFields.end(), back_inserter(codes), [](std::pair<std::string, std::string> p) { return p.first; });

            for (auto data : pp.second)
            {
                std::string code = data.substr(0, data.find(":"));
                std::string value = data.substr(data.find(":") + 1);

                //find the code in the required fields and then rund validation if necessary
                auto i = requiredFields.find(code);
                if (i != requiredFields.end())
                {
                    //execute regex validation
                    if (validate)
                    {
                        if (std::regex_match(value, std::regex(i->second)))
                        {
                            codes.erase(std::remove(codes.begin(), codes.end(), code), codes.end());
                        }
                    }
                    //its existance is validation
                    else
                    {
                        codes.erase(std::remove(codes.begin(), codes.end(), code), codes.end());
                    }
                }
            }

            //only count results for items that have all required fields validated
            result += (codes.size() == 0);
        }

        return result;
    }
}
