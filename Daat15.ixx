export module Day15;

import std.core;

namespace Day15
{
    export int long long GetNthNumberGame(const std::vector<long long>& input, int numberInSequenceToFind)
    {
        std::vector<long long> result{ input};
        result.resize(numberInSequenceToFind);

        for (int i = input.size(); i < numberInSequenceToFind; i++)
        {
            for (int j = i - 1; j >= 0; j--)
            {
                if (result[j] == result[i])
                {
                    result[i + 1] = i - j;
                    break;
                }
            }
        }

        return result.back();
    }

    //tried a custom struct to stop doing a find and use a default value instead.
    struct DL
    {
        long long v = -1;
        DL operator=(const int& i)
        {
            v = i;
            return *this;
        }
    };

    export int long long GetNthNumberGame_v2(const std::vector<long long>& input, int numberInSequenceToFind)
    {
        std::unordered_map<long long, DL> lastSeen;

        //prime the mpa with our input
        for (int i = 0; i < (int)input.size(); ++i)
        {
            lastSeen[input[i]] = i;
        }

        long long previous = input.back();
        for (int i = (int)input.size(); i < numberInSequenceToFind; i++)
        {
            long long& val = lastSeen[previous].v;
            long long current = 0;
            if (val != -1)
            {
                current = i - 1 - val;
            }
            val = i - 1;
            previous = current;
        }

        return previous;
    }
}