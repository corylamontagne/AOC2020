export module AOCUtil;

import std.core;

export namespace AOC
{
    template<typename T>
    std::vector < T > ParseListFromFile(const std::string& file)
    {
        std::vector<T> input;
        std::ifstream is(file);

        T x;
        while (!is.eof() && is >> x)
        {
            input.push_back(x);
        }

        return input;
    }

    std::vector<std::string> ParseFileByLine(const std::string& file)
    {
        std::vector<std::string> input;
        std::ifstream is(file);

        std::string line;
        while (std::getline(is, line))
        { 
            input.push_back(line);
        }
        return input;
    }

    std::vector<long long> ConvertCommaSeparatedStringToLongs(std::string input)
    {
        std::vector<long long> result;
        std::for_each(input.begin(), input.end(), [&input](char &c) {if (c == ',') c = ' '; });

        std::stringstream ss(input);
        while (1) {
            long n;
            ss >> n;
            if (!ss)
                break;
            result.push_back(n);
        }

        return result;
    }

    std::vector<int> ConvertCommaSeparatedStringToInts(std::string input)
    {
        std::vector<int> result;
        std::for_each(input.begin(), input.end(), [&input](char& c) {if (c == ',') c = ' '; });

        std::stringstream ss(input);
        while (1) {
            int n;
            ss >> n;
            if (!ss)
                break;
            result.push_back(n);
        }

        return result;
    }

    std::vector<long long> ConvertInputToLongs(std::vector<std::string> input)
    {
        std::vector<long long> result;
        std::transform(input.begin(), input.end(), std::back_inserter(result), [](const std::string& s) { return std::stoll(s); });
        return result;
    }

    std::vector<int> ConvertInputToIntegers(const std::vector<std::string>& input)
    {
        std::vector<int> result;
        std::transform(input.begin(), input.end(), std::back_inserter(result), [](const std::string& s) { return std::stoi(s); });
        return result;
    }

    std::string ReplicateString(std::string s,  unsigned int n) {
        std::ostringstream os;
        for (unsigned int i = 0; i < n; i++)
            os << s;
        return os.str();
    }

    std::map<int, std::vector<std::string>> GroupParsedFileByTokens(const std::vector<std::string>& parsedFile, const std::vector<char>& tokens, bool tokenizeEmptyLines)
    {
        std::map<int, std::vector<std::string>> output;

        unsigned int i = 0;
        for (auto line : parsedFile)
        {
            if (line.empty())
            {
                i++;
                continue;
            }
            std::stringstream ss(line);
            std::copy(std::istream_iterator<std::string>{ss}, std::istream_iterator<std::string>{}, std::back_inserter(output[i]));
        }

        return output;
    }

    std::map<int, std::vector<std::string>> GroupParsedFileWord(const std::vector<std::string>& parsedFile, const std::vector<char>& tokens, std::tuple<std::string, bool> group)
    {
        std::map<int, std::vector<std::string>> output;

        unsigned int i = 0;
        for (auto line : parsedFile)
        {
            auto [groupString, skip] = group;
            if (line.find(groupString) != std::string::npos)
            {
                i++;
                if (skip) continue;
            }
            output[i].push_back(line);
        }

        return output;
    }

    std::map<int, std::unordered_set<char>> GetUniqueDataFromLists(std::map<int, std::vector<std::string>> input)
    {
        std::map<int, std::unordered_set<char>> uniqueData;

        for (auto pp : input)
        {
            for (auto data : pp.second)
            {
                std::for_each(data.begin(), data.end(), [pp, &uniqueData](char const& c) {uniqueData[pp.first].insert(c); });
            }
        }

        return uniqueData;
    }

    std::vector<std::tuple<std::string, int>> SplitInputIntoPairs(std::vector<std::string> input)
    {
        std::vector<std::tuple<std::string, int>> returnData;

        for (auto i : input)
        {
            size_t pos = i.find(' ');
            returnData.push_back({ i.substr(0, pos), stoi(i.substr(pos + 1)) });
        }

        return returnData;
    }

    export void GenerateAllBinaryPermutations(std::string bitsSring, std::set<std::string>& binaryStrings, int index = 0)
    {
        if (index == bitsSring.length()) { return; }


        bitsSring[index] = '0';
        GenerateAllBinaryPermutations(bitsSring, binaryStrings, index + 1);

        bitsSring[index] = '1';
        GenerateAllBinaryPermutations(bitsSring, binaryStrings, index + 1);

        binaryStrings.insert(bitsSring);
    }
}