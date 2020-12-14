export module Day14;

import std.core;
import AOCUtil;

namespace Day14
{
    std::string GetMemoryId(const std::string& input)
    {
        //pull out memory id
        unsigned first = input.find('[') + 1;
        unsigned last = input.find(']');
        return input.substr(first, last - first);
    }

    long long GetValue(const std::string& input)
    {
        std::string result(input);
        auto rem = result.find("= ");
        result.erase(0, rem + 2);
        return stoll(result);
    }

    std::string LongtoBinaryString(long long value)
    {
        std::bitset<36> val(value);
        return val.to_string();
    }

    export long long GetMemorySum(const std::map<int, std::vector<std::string>>& data, bool floatingBit = false)
    {
        long long result = 0;

        std::map<int, long long> maskedValues;

        for (auto [index, values] : data)
        {
            std::string mask = values[0];
            auto rem = mask.find("mask = ");
            mask.erase(rem, 7);

            for (int i = 1; i < (int)values.size(); ++i)
            {
                std::string valString = values[i];

                int memoryId = stoi(GetMemoryId(valString));

                std::string memValString = LongtoBinaryString(GetValue(valString));

                for (size_t j = 0; j < mask.length(); ++j)
                {
                    char bit = mask[j];
                    if (bit == 'X') continue;
                    else
                    {
                        memValString[j] = bit;
                    }
                }

                maskedValues[memoryId] = std::bitset<36>(memValString).to_ullong();
            }
        }

        std::for_each(maskedValues.begin(), maskedValues.end(), [=, &result](std::pair<int, long long>p) {result += p.second; });
        return result;
    }

    export long long GetFloatingMemory(const std::map<int, std::vector<std::string>>& data, bool floatingBit = false)
    {
        long long result = 0;

        std::map<long long, long long> maskedValues;

        for (auto [index, values] : data)
        {
            //this is gross
            std::string mask = values[0];
            auto rem = mask.find("mask = ");
            mask.erase(rem, 7);

            for (int i = 1; i < (int)values.size(); ++i)
            {
                std::string valString = values[i];

                std::string memoryId = GetMemoryId(valString);

                std::bitset<36> memBits(stoll(memoryId));
                std::string memValString = memBits.to_string();

                long long val = GetValue(valString);

                //build permutations of X bits
                int numFloatingBits = std::count(mask.begin(), mask.end(), ('X'));
                std::set<std::string> allFloatingBits{ std::string(numFloatingBits, '0') };
                AOC::GenerateAllBinaryPermutations(*allFloatingBits.begin(), allFloatingBits);

                for (auto b : allFloatingBits)
                {
                    int floatingIndex = (*allFloatingBits.begin()).length() - 1;
                    for (size_t j = 0; j < mask.length(); ++j)
                    {
                        //as we hit an X bit, copy in the right bit from the current permutation
                        char bit = mask[j];
                        if (bit == 'X')
                        {
                            memValString[j] = b[floatingIndex];
                            floatingIndex--;
                        }
                        else if (bit == '1')
                        {
                            memValString[j] = bit;
                        }
                    }
                    maskedValues[std::bitset<36>(memValString).to_ullong()] = val;
                }
            }
        }

        std::for_each(maskedValues.begin(), maskedValues.end(), [=, &result](std::pair<long long, long long>p) {result += p.second; });
        return result;
    }
}