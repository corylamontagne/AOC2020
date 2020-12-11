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
}
//</shame>