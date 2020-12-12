export module Day11;

import std.core;

/// ///////////////////////////////////////////////////////////////////////////
///.
/// 
/// 
/// DON'T LOOK AT ME, I'M HIDEOUS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/// 
/// 
/// 
/// <shame>
/// .
/// 
/// 
/// 
/// 
/// 
/// 
/// I do all the looping. I know, I feel bad.
/// I check every single direction regardless of if we already know we dont have
/// enough to change the seat state, I know, I know. I am equally disappointed.
/// I copy the data entirely every time we look to change states. You don't have
/// to yell, I already said I feel bad.
/// ///////////////////////////////////////////////////////////////////////////
namespace Day11
{
    char GetSeatState(std::tuple<int, int> seatIndex, const std::vector<std::string>& input)
    {
        char result = ' ';

        auto [row, col] = seatIndex;

        if (row >= 0 && row < (int)input.size())
        {
            if (col >= 0 && col <= (int)input[row].length())
            {
                result = input[row][col];
            }
        }

        return result;
    }

    int GetNumberOfAdjacent(std::tuple<int, int> seatIndex, std::vector<char> seatStates, const std::vector<std::string>& input)
    {
        int result = 0;

        auto [row, col] = seatIndex;

        for (int i = row - 1; i <= row + 1 && i < (int)input.size(); ++i)
        {
            if (i < 0) continue;
            for (int j = col - 1; j <= col + 1 && j <= (int)input[i].length(); ++j)
            {
                if (j < 0) continue;
                if (std::tuple<int, int>{ i, j } != seatIndex)
                {
                    result += std::find(seatStates.begin(), seatStates.end(), GetSeatState({ i, j }, input)) != seatStates.end();
                }
            }
        }

        return result;
    }

    int GetLineOfSight(std::tuple<int, int> seatIndex, std::vector<char> seatStates, const std::vector<std::string>& input, char stopLookingSeat = 'L')
    {
        int result = 0;
        std::vector< std::tuple<int, int> > directions = { { -1, -1 }, { -1, 0 }, { -1, 1 },
                                                           { 0, -1 }, { 0, 1 },
                                                           { 1, -1 }, { 1, 0 }, { 1, 1 } };

        for (size_t dir = 0; dir < directions.size(); ++dir)
        {
            bool found = false;
            std::tuple<int, int> currentIndex = seatIndex;
            while (!found)
            {
                std::get<0>(currentIndex) += std::get<0>(directions[dir]);
                std::get<1>(currentIndex) += std::get<1>(directions[dir]);
                int row = std::get<0>(currentIndex);
                int col = std::get<1>(currentIndex);

                if (row >= 0 && row < (int)input.size())
                {
                    if (col >= 0 && col <= (int)input[row].length())
                    {
                        if (std::tuple<int, int>{ row, col } != seatIndex)
                        {
                            char seatState = GetSeatState({ row, col }, input);
                            if (seatState == stopLookingSeat)
                            {
                                break;
                            }
                            if (std::find(seatStates.begin(), seatStates.end(), seatState) != seatStates.end())
                            {
                                found = true;
                                break;
                            }
                        }
                        else
                        {
                            break;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
            if (found)
            {
                result += 1;
            }
        }

        return result;
    }

    export int CalculateOccupiedSeats(std::vector<std::string> input, int numberOfAdjacentToEmpty, int numberOfAdjacentToFill, bool getFirstInSight = false)
    {
        int result = 0;

        std::vector<std::string> seatsBefore;

        bool seatsChanged = true;
        bool checkEmpty = true;
        while (seatsChanged)
        {
            seatsBefore = input;
            seatsChanged = false;
            //check for empty seats
            for (size_t i = 0; i < seatsBefore.size(); ++i)
            {
                for (size_t j = 0; j <= seatsBefore[i].length(); ++j)
                {
                    int numSeats = (getFirstInSight) ? GetLineOfSight({ i, j }, std::vector<char>{'#'}, seatsBefore) :
                                                       GetNumberOfAdjacent({ i, j }, std::vector<char>{'#'}, seatsBefore);
                    if (checkEmpty)
                    {
                        if (numSeats == 0 && seatsBefore[i][j] == 'L')
                        {
                            input[i][j] = '#';
                            seatsChanged = true;
                        }
                    }
                    else
                    {
                        if (numSeats >= numberOfAdjacentToEmpty && seatsBefore[i][j] == '#')
                        {
                            input[i][j] = 'L';
                            seatsChanged = true;
                        }
                    }
                }
            }
            checkEmpty = !checkEmpty;
        }

        std::for_each(input.begin(), input.end(), [=, &result](std::string s) { result += std::count(s.begin(), s.end(), '#'); });

        return result;
    }




    //This version cuts time in half but I never short circuit the looping logic.
    //It is also currently harder to read
    export typedef std::bitset<2> TwoBits;
    export typedef std::bitset<4> FourBits;
    export typedef std::vector<std::vector<FourBits>> BitSetMap;
    export BitSetMap ConvertInputToGameBoard(std::vector<std::string> input, std::map<char, TwoBits> mapping)
    {
        BitSetMap map;

        for (auto i : input)
        {
            std::vector<FourBits> line;
            for (auto j : i)
            {
                line.push_back(FourBits(mapping[j].to_ulong()));
            }
            map.push_back(line);
        }

        return map;
    }

    void CloneBits(std::vector<FourBits>& bitList, bool left = true)
    {
        std::for_each(bitList.begin(), bitList.end(), [left](FourBits& s) 
        {  
            if (left) { s.set(3, s.test(1)); s.set(2, s.test(0)); }
            else      { s.set(1, s.test(3)); s.set(0, s.test(2)); }
        });
    }

    int CountBits(std::vector<FourBits> input, FourBits val, FourBits mask)
    {
        int result = 0;
        for (auto i : input)
        {
            result += ((i & mask) == (val << 2));
        }
        return result;
    }

    FourBits GetSeatState_v2(std::tuple<int, int> seatIndex, const BitSetMap& input)
    {
        FourBits result(0);

        auto [row, col] = seatIndex;

        if (row >= 0 && row < (int)input.size())
        {
            if (col >= 0 && col < (int)input[row].size())
            {
                result = input[row][col];
            }
        }

        return result;
    }

    int GetNumberOfAdjacent_v2(std::tuple<int, int> seatIndex, TwoBits seatState, const BitSetMap& input, FourBits mask)
    {
        int result = 0;

        auto [row, col] = seatIndex;

        for (int i = row - 1; i <= row + 1 && i < (int)input.size(); ++i)
        {
            if (i < 0) continue;
            for (int j = col - 1; j <= col + 1 && j < (int)input[i].size(); ++j)
            {
                if (j < 0) continue;
                if (std::tuple<int, int>{ i, j } != seatIndex)
                {
                    FourBits state = GetSeatState_v2({ i, j }, input) & mask;
                    FourBits test(seatState.to_ulong() << 2);
                    result += (state == test);
                }
            }
        }

        return result;
    }

    export int CalculateOccupiedSeats_v2(BitSetMap bitMap, int numberOfAdjacentToEmpty, bool getFirstInSight = false)
    {
        int result = 0;

        bool seatsChanged = true;
        bool checkEmpty = true;
        static FourBits highMask(12);
        static FourBits lowMask(3);
        while (seatsChanged)
        {
            std::for_each(bitMap.begin(), bitMap.end(), [=](std::vector<FourBits>& s) {  CloneBits(s); });
            seatsChanged = false;
            for (int i = 0; i < (int)bitMap.size(); ++i)
            {
                for (int j = 0; j < (int)bitMap[i].size(); ++j)
                {
                    int numSeats = GetNumberOfAdjacent_v2({ i, j }, TwoBits(1), bitMap, highMask);
                    if (checkEmpty)
                    {
                        if (numSeats == 0 && 
                            ((bitMap[i][j] & highMask) == (FourBits(TwoBits(2).to_ulong()) << 2)))
                        {
                            //set to 1
                            bitMap[i][j].set(0, 1);
                            bitMap[i][j].set(1, 0);
                            seatsChanged = true;
                        }
                    }
                    else
                    {
                        if (numSeats >= numberOfAdjacentToEmpty && 
                            ((bitMap[i][j] & lowMask) == (FourBits(TwoBits(1).to_ulong()))))
                        {
                            //set to 2
                            bitMap[i][j].set(0, 0);
                            bitMap[i][j].set(1, 1);
                            seatsChanged = true;
                        }
                    }
                }
            }
            checkEmpty = !checkEmpty;
        }

        std::for_each(bitMap.begin(), bitMap.end(), [=, &result](std::vector<FourBits> v) { result += CountBits(v, FourBits(1), highMask); });

        return result;
    }
}
//</shame>