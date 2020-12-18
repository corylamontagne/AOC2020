export module Day16;

import std.core;
import AOCUtil;

namespace Day16
{
    export typedef std::unordered_map<std::string, std::vector<int>> TicketDataMap;
    export typedef std::vector<int> TicketInfo;

    std::vector<int> GetDataField(std::string input)
    {
        std::vector<int> result;
        std::replace(input.begin(), input.end(), '-', ' ');
        input.replace(input.find("or"), 2, "  ");

        std::stringstream ss(input);
        while (ss.good())
        {
            int val;
            ss >> val;
            result.push_back(val);
        }
        return result;
    }

    export void PopulateTicketDataInfo(const  std::vector<std::string>& input, TicketDataMap& map, TicketInfo& passenger, std::vector<TicketInfo>& nearby)
    {
        for (int i = 0; i < (int)input.size(); ++i)
        {
            std::string current = input[i];
            std::string key = current.substr(0, current.find(':'));
            if (key.find("your ticket") != std::string::npos)
            {
                passenger = AOC::ConvertCommaSeparatedStringToInts(input[i + 1]);
                i++;
            }
            else if (key.find("nearby tickets") != std::string::npos)
            {
                for (i = i + 1; i < (int)input.size(); ++i)
                {
                    nearby.push_back(AOC::ConvertCommaSeparatedStringToInts(input[i]));
                }
                break;
            }
            else if (!key.empty())
            {
                map[key] = GetDataField(current.substr(current.find(':') + 1, current.length()));
            }
        }
    }

    bool IsFieldInRange(int value, std::tuple<int, int> firstRange, std::tuple<int, int> secondRange)
    {
        return !(value < std::get<0>(firstRange) || value > std::get<1>(secondRange) ||
            (value > std::get<1>(firstRange) && value < std::get<0>(secondRange)));
    }

    export long long GetInvalidFields(const std::vector<TicketInfo>& nearbyTickets, const TicketDataMap& ticketData, std::vector<int>& invalidTickets)
    {
        long long result = 0;

        int index = 0;
        for (auto passenger : nearbyTickets)
        {
            for (int j = 0; j < (int)passenger.size(); ++j)
            {
                int ticketField = passenger[j];
                int invalidFieldValue = 0;
                for (auto [k, v] : ticketData)
                {
                    if (IsFieldInRange(ticketField, { v[0], v[1] }, { v[2], v[3] }))
                    {
                        invalidFieldValue = 0;
                        break;
                    }
                    else
                    {
                        invalidFieldValue = ticketField;
                    }
                }
                result += invalidFieldValue;
                if (invalidFieldValue != 0)
                {
                    invalidTickets.push_back(index);
                }
            }
            index++;
        }

        return result;
    }

    export long long DetermineValidFields(TicketInfo ticket, const std::vector<TicketInfo>& nearbyTickets, const TicketDataMap& ticketData)
    {
        long long result = 1;

        std::map<int, TicketDataMap> ranges;

        for (int i = 0; i < (int)ticketData.size(); ++i)
        {
            ranges[i] = ticketData;
        }

        for (auto passenger : nearbyTickets)
        {
            for (int j = 0; j < (int)passenger.size(); ++j)
            {
                TicketDataMap& currentRange = ranges[j];
                std::vector<std::string> remove;
                for (auto tm : currentRange)
                {
                    auto [k, v] = tm;
                    if (!IsFieldInRange(passenger[j], { v[0], v[1] }, { v[2], v[3] }))
                    {
                        remove.push_back(k);
                    }
                }
                for (auto s : remove)
                {
                    currentRange.erase(currentRange.find(s));
                }
            }
        }

        std::set<std::string> check;
        int size = 1;
        int found = 0;
        while (found < 6)
        {
            while (size < (int)ticketData.size())
            {
                int i = 0;
                for (auto tm : ranges)
                {
                    if (tm.second.size() == size)
                    {
                        for (auto [n, m] : tm.second)
                        {
                            if (n.find("departure") != std::string::npos)
                            {
                                if (check.find(n) == check.end())
                                {
                                    check.insert(n);
                                    result *= ticket[tm.first];
                                    found++;
                                    break;
                                }
                            }
                        }
                        i++;
                    }
                }
                size++;
            }
        }

        return result;
    }
}