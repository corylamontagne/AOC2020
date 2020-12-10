export module Day9;

import std.core;

namespace Day9
{
    export typedef std::vector<long long> LongLongVec;

    LongLongVec PrimeListOfSums(const LongLongVec& input, int preamble)
    {
        LongLongVec primed;
        for (int i = 0; i < preamble; i++)
        {
            for (int j = 0; j < preamble; j++)
            {
                if (i == j) continue;
                primed.push_back(input[i] +input[j]);
            }
        }
        return primed;
    }

    export long long FindFirstFailedPreamble(const LongLongVec& input, int preamble)
    {
        long long result = -1;

        LongLongVec sums = PrimeListOfSums(input, preamble);

        //maintain the 'preamble' values we check against
        std::deque<long long> preambleList;
        std::transform(input.begin(), input.begin() + preamble, std::back_inserter(preambleList), [](long long l) { return l; });

        for (size_t i = preamble; i < input.size(); i++)
        {
            long long val = input[i];
            //check our sums
            if (std::find(sums.begin(), sums.end(), val) == sums.end()) 
            { 
                result = val;
                break;
            }

            //remove values related to the 1st of the preamble so we can add the next.
            preambleList.pop_front();
            sums.erase(sums.begin(), sums.begin() + preamble);

            //add the next val
            preambleList.push_back(val);

            //create the next 'preamble' number of sums to check against
            std::for_each(preambleList.begin(), preambleList.end(), [=, &sums](long long n) { sums.push_back(n + val); });
        }

        return result;
    }

    export long long FindEncryptionWeakness(const LongLongVec& input, long long invalidPreamble)
    {
        long long result = -1;

        for (size_t i = 0; i < input.size() - 1; ++i)
        {
            long long weakness = 0;
            size_t j = i;
            while (j < input.size() && weakness < invalidPreamble)
            {
                weakness += input[j];
                j++;
            }

            if (weakness == invalidPreamble) 
            {
                std::vector<long long> weakSet{ input.begin() + i, input.begin() + (j - 1) };
                std::sort(weakSet.begin(), weakSet.end());
                result = weakSet.front() + weakSet.back();
                break;
            }
        }

        return result;
    }
}