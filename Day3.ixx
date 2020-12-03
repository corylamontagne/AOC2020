export module Day3;

import std.core;
import AOCUtil;

namespace Day3
{
    /// <summary>
    /// Day 3 Problem 1
    /// </summary>
    export unsigned int CountTreesOnToboganPath(std::vector<std::string> arr, unsigned int col, unsigned int row)
    {
        unsigned int result = 0;

        std::transform(arr.begin(), arr.end(), arr.begin(), 
            [row, col, size = arr.size()](std::string s) { return AOC::ReplicateString(s, ceil(size / s.size())*(row+col));});

        for (size_t i = col, j = row; j < arr.size(); i+=col, j+=row)
        {
            result += (arr[j][i] == '#');
        }

        return result;
    }
}
