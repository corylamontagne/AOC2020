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

    std::string ReplicateString(std::string s,  int n) {
        std::ostringstream os;
        for (int i = 0; i < n; i++)
            os << s;
        return os.str();
    }
}