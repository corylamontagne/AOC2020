export module Day2;

import std.core;

namespace Day2
{
    typedef std::tuple<int, int, char, std::string> PasswordRule;

    //No error checking because I'm inept or insane or both
    PasswordRule ParseRules(std::string data)
    {
        data.replace(data.find("-"), 1, " ");
        data.replace(data.find(":"), 1, " ");

        std::stringstream ss(data);

        int low, high;
        char value;
        std::string password;

        ss >> low;
        ss >> high;
        ss >> value;
        ss >> password;

        return std::make_tuple(low, high, value, password);
    }

    /// <summary>
    /// Day 2 Problem 1 Validator
    /// </summary>
    export bool ValidateQuantity(PasswordRule rule)
    {
        std::string pw = std::get<3>(rule);
        int count = std::count(pw.begin(), pw.end(), std::get<2>(rule));

        return (count >= std::get<0>(rule) && count <= std::get<1>(rule));
    }

    /// <summary>
    /// Day 2 Problem 2 Validator
    /// </summary>
    export bool ValidatePosition(PasswordRule rule)
    {
        char value = std::get<2>(rule);
        std::string pw = std::get<3>(rule);

        return ( (pw[std::get<0>(rule) -1] == value) ^ (pw[std::get<1>(rule) -1] == value));
    }

    /// <summary>
    /// Day 2 Problems
    /// </summary>
    export int ValidatePasswords(const std::vector<std::string>& arr, std::function<bool(PasswordRule) > validator)
    {
        int result = 0;

        for (auto s : arr)
        {
            if (validator(ParseRules(s)))
            {
                result++;
            }
        }

        return result;
    }
}