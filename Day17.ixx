export module Day17;

import std.core;

namespace Day17
{
    constexpr int SIZE = 20;
    export typedef std::bitset<2> TwoBits;
    export typedef std::bitset<4> FourBits;
    export typedef std::vector<FourBits> BitSetRow;
    export typedef std::vector<BitSetRow> BitSetPlane;
    export typedef std::vector<BitSetPlane> BitSetCube;
    export typedef std::vector<BitSetCube> BitSetHyperCube;
    static FourBits highMask(12);

    void CloneState(BitSetHyperCube& powerSource)
    {
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                for (int k = 0; k < SIZE; ++k)
                {
                    for (int w = 0; w < SIZE; ++w)
                    {
                        FourBits& b = powerSource[i][j][k][w];
                        b.set(3, b.test(1));
                        b.set(2, b.test(0));
                    }
                }
            }
        }
    }

    export BitSetHyperCube ConvertInputPowerSource(std::vector<std::string> input, std::map<char, TwoBits> mapping)
    {
        BitSetRow row = BitSetRow(SIZE, FourBits());
        BitSetPlane plane = BitSetPlane(SIZE, row);
        BitSetCube cube = BitSetCube(SIZE, plane);
        BitSetHyperCube map(SIZE, cube);
        size_t inputStart = input.size()/2;
        size_t halfStart = SIZE / 2;
        size_t startPoint = halfStart - inputStart;

        int j = startPoint;
        for (auto v : input)
        {
            int k = startPoint;
            for (auto c : v)
            {
                map[halfStart][halfStart][j][k] = FourBits(mapping[c].to_ulong());
                k++;
            }
            j++;
        }

        CloneState(map);
        return map;
    }

    std::tuple<bool, FourBits> GetSeatState(std::tuple<int, int, int, int> seatIndex, const BitSetHyperCube& powerSource)
    {
        auto [x, y, z, w] = seatIndex;

        if (x >= 0 && x < SIZE)
        {
            if (y >= 0 && y < SIZE)
            {
                if (z >= 0 && z < SIZE)
                {
                    if (w >= 0 && w < SIZE)
                    {
                        return { true, powerSource[x][y][z][w] };
                    }
                }
            }
        }
        return { false, FourBits(0) };
    }

    export void PrintBoard(const BitSetHyperCube& powerSource)
    {
        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                for (int k = 0; k < SIZE; ++k)
                {
                    for (int w = 0; w < SIZE; ++w)
                    {
                        bool on = ((powerSource[i][j][k][w] & highMask) == FourBits(TwoBits(1).to_ulong() << 2));
                        std::cout << ((on) ? "#" : ".");
                    }
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }

        std::cout << "========================================" << std::endl;
    }

    int CountNeighbors(const BitSetHyperCube& powerSource, std::tuple<int, int, int, int> coord, TwoBits seatState)
    {
        int result = 0;
        auto [x, y, z, w] = coord;

        for (int i = x - 1; i <= x + 1; ++i)
        {
            for (int j = y - 1; j <= y + 1; ++j)
            {
                for (int k = z - 1; k <= z + 1; ++k)
                {
                    for (int l = w - 1; l <= w + 1; ++l)
                    {
                        if (std::tuple<int, int, int, int>(i, j, k, l) == coord) continue;
                        auto [suc, state] = GetSeatState({ i, j, k, l }, powerSource);
                        if (suc)
                        {
                            FourBits s = state & highMask;
                            FourBits test(seatState.to_ulong() << 2);
                            result += (s == test);
                        }
                    }
                }
            }
        }

        return result;
    }

    export long long GetActiveConwayCubes(BitSetHyperCube powerSource, std::tuple<int, int> activeRange, std::tuple<int, int> inactiveRange, int passes = 6)
    {
        long long result = 0;
        TwoBits activeSeat(1);
        TwoBits inactiveSeat(0);

        auto [aLow, aHigh] = activeRange;
        auto [iLow, iHigh] = inactiveRange;

        bool checkEmpty = true;
        int count = 0;
        while (count < passes)
        {
            for (int i = 0; i < SIZE; ++i)
            {
                for (int j = 0; j < SIZE; ++j)
                {
                    for (int k = 0; k < SIZE; ++k)
                    {
                        for (int l = 0; l < SIZE; ++l)
                        {
                            auto [suc, state] = GetSeatState({ i, j, k, l }, powerSource);
                            if (suc)
                            {
                                int neighbors = CountNeighbors(powerSource, { i, j, k, l }, activeSeat);
                                bool active = ((state & highMask) == FourBits(activeSeat.to_ulong() << 2));

                                if (active)
                                {
                                    if (neighbors >= aLow && neighbors <= aHigh)
                                    {
                                    }
                                    else
                                    {
                                        powerSource[i][j][k][l].set(0, 0);
                                        powerSource[i][j][k][l].set(1, 0);
                                    }
                                }
                                else
                                {
                                    if (neighbors >= iLow && neighbors <= iHigh)
                                    {
                                        powerSource[i][j][k][l].set(0, 1);
                                        powerSource[i][j][k][l].set(1, 0);
                                    }
                                }
                            }
                        }
                    }
                }
            }
            count++;
            CloneState(powerSource);
            //PrintBoard(powerSource);
        }

        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                for (int k = 0; k < SIZE; ++k)
                {
                    for (int l = 0; l < SIZE; ++l)
                    {
                        auto [suc, state] = GetSeatState({ i, j, k, l }, powerSource);
                        result += ((state & highMask) == FourBits(activeSeat.to_ulong() << 2));
                    }
                }
            }
        }
        return result;
    }
}