export module Day5;

import std.core;

namespace Day5
{
    export std::vector<unsigned int> FindSeatNumbersFromBoardingPasses(const std::vector<std::string> input, std::pair<unsigned int, unsigned int> rowRange, unsigned int seatsPerRow)
    {
        std::vector<unsigned int> seatNumbers;
        for (auto pass : input)
        {
            auto [low, high] = rowRange;
            auto [lowSeat, highSeat] = std::make_pair(0, seatsPerRow -1);
            std::for_each(pass.begin(), pass.end(), [=, &low, &high, &lowSeat, &highSeat](char const& c)
            {
                //I hate literals here, but today was busy. Maybe I will revisit.
                //This should be more data driven and generic.
                if (c == 'F')
                {
                    high -= static_cast<unsigned int>(ceil((high-low) / 2.f));
                }
                else if (c == 'B')
                {
                    low += static_cast<unsigned int>(ceil((high - low) / 2.f));
                }
                else if (c == 'L')
                {
                    highSeat -= static_cast<unsigned int>(ceil((highSeat-lowSeat) / 2.f));
                }
                else if (c == 'R')
                {
                    lowSeat += static_cast<unsigned int>(ceil((highSeat - lowSeat) / 2.f));
                }
            });
            seatNumbers.push_back((low) * seatsPerRow + (lowSeat));
        }
        std::sort(seatNumbers.begin(), seatNumbers.end());

        return seatNumbers;
    }
}