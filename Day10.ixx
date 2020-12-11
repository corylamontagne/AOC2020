export module Day10;

import std.core;

namespace Day10
{
    export typedef std::vector<int> IntegerVec;

    export int GetProductOfJoltageDifferences(IntegerVec input, int startJoltage, std::tuple<int, int> joltageRange, int deviceJoltageDiff)
    {
        int result = -1;

        std::sort(input.begin(), input.end());

        auto [minJolt, maxJolt] = joltageRange;
        int lastJolt = startJoltage;

        std::array<int, 3> joltageSets{};

        //the device difference
        input.push_back(input.back() + deviceJoltageDiff);

        for (auto i : input)
        {
            joltageSets[i - lastJolt - 1]++;
            lastJolt = i;
        }

        result = joltageSets[0] * joltageSets[2];

        return result;
    }

    //this is inefficient and there is probably a way to use std::transforms and reduce etc
    export long long GetUniqueCombinationsOfAdapters(IntegerVec input, int maxJoltDifference, int outletJoltage)
    {
        long long result = -1;
        //add the outlet joltage before we sort
        input.push_back(outletJoltage);
        std::sort(input.begin(), input.end());

        int size = input.size() - 1;
        std::vector<long long> cumulativeAdapterCombinations(input.size());

        //the main sorted list itself is a combination, start with that and go from there.
        cumulativeAdapterCombinations.back() = 1;

        //calculate combinations backwards so we can cumulatively add and carry combinations along the input
        //can probably do this in a single line but debugging is hard yo
        for (int i = size - 1; i >= 0; --i)
        {
            //as long as we are in the max range and within the list, add combinations
            for (int j = i + 1; j <= size && (input[j] - input[i] <= maxJoltDifference); ++j)
            {
                cumulativeAdapterCombinations[i] += cumulativeAdapterCombinations[j];
            }
            result = cumulativeAdapterCombinations[i];
        }

        return result;
    }
}