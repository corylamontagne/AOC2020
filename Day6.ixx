export module Day6;

import std.core;

namespace Day6
{
    export unsigned int GetAnsweredQuestions(std::map<int, std::unordered_set<char>> input)
    {
        unsigned int results = 0;

        for (auto pp : input)
        {
            results += pp.second.size();
        }

        return results;
    }

    //this function is similar to one in AOCUtils, maybe find a way to make generic to be used for all cases
    export unsigned int GetUnanimousAnswers(std::map<int, std::vector<std::string>> input)
    {
        unsigned int results = 0;

        for (auto pp : input)
        {
            //concatenate all answers
            std::ostringstream implodedAnswers;
            std::copy(pp.second.begin(), pp.second.end(), std::ostream_iterator<std::string>(implodedAnswers, ""));

            std::string allAnswers = implodedAnswers.str();
            //for each question, add only the answers that were found for every member fo the group
            for (char i = 'a'; i <= 'z'; ++i)
            {
                results += (std::count(allAnswers.begin(), allAnswers.end(), i) == pp.second.size());
            }
        }

        return results;
    }
}