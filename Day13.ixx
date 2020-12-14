export module Day13;

import std.core;

namespace Day13
{
    export std::tuple<long long, std::vector<int>> ParseBusData(const std::vector<std::string>& input, char delim, char invalid, bool ignoreInvalid = true)
    {
        long long timestamp = stoll(input[0]);
        std::vector<int> busses;

        std::stringstream ss(input[1]);

        while (ss.good()) {
            std::string substr;
            getline(ss, substr, delim);
            if (substr.find(invalid) != std::string::npos)
            {
                if (!ignoreInvalid)
                    busses.push_back(0);
            }
            else
            {
                busses.push_back(stoi(substr));
            }
        }

        return { timestamp, busses };
    }

    export long long GetBus(long long arrival, std::vector<int> departures)
    {
        long long result = -1;
        long long mins = std::numeric_limits<long long>::max();

        std::for_each(departures.begin(), departures.end(), [=, &result, &mins](int i) {int b = i - (arrival % i); if (mins > b) { result = i; mins = b; } });

        return result * mins;
    }

    export long long GetBus_v2(std::vector<int> departures)
    {
        long long result = -1;
        long long mins = std::numeric_limits<long long>::max();

        long long lastDeparture = -1;
        for (size_t i = 0; i < departures.size(); ++i)
        {

        }

        return result * mins;
    }
}