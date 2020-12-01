export module AOCUtil;

import std.core;

export namespace AOC
{
    template<typename T>
    std::vector < T > PaseListFromFile(const std::string& file)
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
}