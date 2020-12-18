
import std.core;
import AOCUtil;
import Day1;
import Day2;
import Day3;
import Day4;
import Day5;
import Day6;
import Day7;
import Day8;
import Day9;
import Day10;
import Day11;
import Day12;
import Day13;
import Day14;
import Day15;
import Day16;
import Day17;
import Day18;

int main()
{
    //Start Timer Code
    auto startTime = std::chrono::high_resolution_clock::now();

    //Day 18
    std::vector<std::string> input = AOC::ParseFileByLine("Input/P18-input.txt");
    Day18::OperatorMap ops = { {"+",[=](long long a, long long b) {return a + b; } }, {"*",[=](long long a, long long b) {return a * b; } } };

    //Problem 1 setup
    //Day18::PrecedenceMap precMap = { {"+", 1}, {"*", 1} };
    //Problem 2 setup
    Day18::PrecedenceMap precMap = { {"+", 2}, {"*", 1} };

    long long sum = 0;
    
    for (auto i : input)
    {
        sum += Day18::Calculate(i, ops, precMap);
    }

    std::cout << sum << std::endl;

    //Day 17
    //std::vector<std::string> input = AOC::ParseFileByLine("Input/P17-input.txt");
    //std::map<char, Day17::TwoBits> mapping = { { '.', Day17::TwoBits(0) }, { '#', Day17::TwoBits(1) }};

    //Day17::BitSetHyperCube conwayCube = Day17::ConvertInputPowerSource(input, mapping);
    ////Day17::PrintBoard(conwayCube);

    //std::cout << std::endl << std::endl;
    ////Problem 1
    //std::cout << Day17::GetActiveConwayCubes(conwayCube, { 2, 3 }, { 3, 3 }) << std::endl;

    //Problem 2

    //Day 16 //
    //std::vector<std::string> input = AOC::ParseFileByLine("Input/P16-input.txt");
    //Day16::TicketDataMap map;

    //Day16::TicketInfo passengerTicket;
    //std::vector<Day16::TicketInfo> nearbyTickets;
    //std::vector<int> invalidTicketIndices;

    //Day16::PopulateTicketDataInfo(input, map, passengerTicket, nearbyTickets);

    ////Problem 1
    //std::cout << Day16::GetInvalidFields(nearbyTickets, map, invalidTicketIndices) << std::endl;

    //for (int i = invalidTicketIndices.size() - 1; i >= 0; --i)
    //{
    //    nearbyTickets.erase(nearbyTickets.begin() + invalidTicketIndices[i]);
    //}

    ////Problem 2
    //std::cout << Day16::DetermineValidFields(passengerTicket, nearbyTickets, map) << std::endl;

    //Day 15 //
    //std::vector<std::string> input = AOC::ParseFileByLine("Input/P15-input.txt");
    //std::vector<long long> data = AOC::ConvertCommaSeparatedStringToLongs(input[0]);

    ////Problem 1
    //std::cout << Day15::GetNthNumberGame(data, 2020) << std::endl;

    ////Problem 2
    //std::cout << Day15::GetNthNumberGame_v2(data, 30000000) << std::endl;

    //Dqy 14 //
    //std::vector<std::string> input = AOC::ParseFileByLine("Input/P14-input.txt");
    //std::map<int, std::vector<std::string>> data = AOC::GroupParsedFileWord(input, {}, { "mask", false });

    ////Problem 1
    //std::cout << Day14::GetMemorySum(data) << std::endl;

    ////Problem 2
    //std::cout << Day14::GetFloatingMemory(data) << std::endl;

    //Day 13 //
    //std::vector<std::string> input = AOC::ParseFileByLine("Input/P13-input.txt");

    //auto [arrival, departures] = Day13::ParseBusData(input, ',', 'x');

    //////Problem 1
    //std::cout << Day13::GetBus(arrival, departures) << std::endl;

    //auto [_, secondDepartures] = Day13::ParseBusData(input, ',', 'x', false);
    //////Problem 2
    //std::cout << Day13::GetBus_v2(secondDepartures) << std::endl;

    //Day 12 //
    //std::vector<std::string> input = AOC::ParseFileByLine("Input/P12-input.txt");

    //Day12::CommandValueMap data = Day12::ConvertToCVM(input);

    ////Problem 1
    //std::cout << Day12::GetDistance(data, 'E') << std::endl;

    ////Problem 2
    //std::cout << Day12::GetDistanceToWaypoint(data, Day12::Vec2D(1, 10)) << std::endl;

    //Day 11 //
    //std::vector<std::string> input = AOC::ParseFileByLine("Input/P11-input.txt");

    //std::map<char, Day11::TwoBits> mapping = { { '.', Day11::TwoBits(0) }, { '#', Day11::TwoBits(1) }, { 'L', Day11::TwoBits(2) } };

    ////Problem 1
    ////std::cout << Day11::CalculateOccupiedSeats(input, 4, 8) << std::endl;
    ////Problem 1.2
    //Day11::BitSetMap inputMap = Day11::ConvertInputToGameBoard(input, mapping); 

    //std::cout << Day11::CalculateOccupiedSeats_v2(inputMap, 4) << std::endl;

    //Problem 2
    //std::cout << Day11::CalculateOccupiedSeats(input, 5, 8, true) << std::endl;

    //Day 10 //
    //Day10::IntegerVec input = AOC::ConvertInputToIntegers(AOC::ParseFileByLine("Input/P10-input.txt"));

    ////Problem 1
    //std::cout << Day10::GetProductOfJoltageDifferences(input, 0, { 1, 3 }, 3) << std::endl;

    ////Problem 1
    //std::cout << Day10::GetUniqueCombinationsOfAdapters(input, 3, 0) << std::endl;

    //Day 9 //
    //Day9::LongLongVec input = AOC::ConvertInputToLongs(AOC::ParseFileByLine("Input/P9-input.txt"));

    //long long invalidPreamble = Day9::FindFirstFailedPreamble(input, 25);
    ////Problem 1
    //std::cout << invalidPreamble << std::endl;

    ////Problem 2
    //std::cout << Day9::FindEncryptionWeakness(input, invalidPreamble) << std::endl;

    //Day 8 //
    //std::vector<Day8::CommandValue> input = AOC::SplitInputIntoPairs(AOC::ParseFileByLine("Input/P8-input.txt"));

    ////Problem 1
    //auto [result, success] = Day8::ProcessInput(input);
    //std::cout << result << std::endl;

    ////Problem 2
    //auto [r, s] = Day8::FindSwappedCommand(input, { { "jmp", "nop" }, { "nop", "jmp" } });
    //std::cout << r << std::endl;


    //Day 7 //
    //std::vector<std::string> input = AOC::ParseFileByLine("Input/P7-input.txt");
    //std::string bagToCheck = "shiny gold";

    //Day7::MatryoshkaBags mb = Day7::GetMatryoshkaBags(input, bagToCheck);
    ////Problem 1
    //std::cout << Day7::GetNumberOfParents(mb, bagToCheck) << std::endl;

    ////Problem 1
    //std::cout << Day7::GetNumberOfBagsToContain(mb, bagToCheck) << std::endl;


    //Day 6 //
    //std::map<int, std::vector<std::string>> data = AOC::GroupParsedFileByTokens(AOC::ParseFileByLine("Input/P6-input.txt"), std::vector<char>{' '}, true);

    //std::map<int, std::unordered_set<char>> answers = AOC::GetUniqueDataFromLists(data);

    ////Problem 1
    //std::cout << Day6::GetAnsweredQuestions(answers) << std::endl;

    ////Problem 2
    //std::cout << Day6::GetUnanimousAnswers(data) << std::endl;

    //Day 5 //
    //std::vector<std::string> input = AOC::ParseFileByLine("Input/P5-input.txt");
    //std::pair<unsigned int, unsigned int> rowRange = std::make_pair(0, 127);
    //const unsigned int seatsPerRow = 8;

    //std::vector<unsigned int> seats = Day5::FindSeatNumbersFromBoardingPasses(input, rowRange, seatsPerRow);

    //auto begin = seats.begin();
    //auto end = seats.end();

    ////Problem 1
    //std::sort(begin, end);
    //std::cout << seats.back() << std::endl;

    ////Problem 2
    //for (unsigned int i = 1; i < ((rowRange.second * seatsPerRow) - 1); ++i)
    //{
    //    if (std::find(begin, end, i) == end)
    //    {
    //        if (std::find(begin, end, i - 1) != end && std::find(begin, end, i + 1) != end)
    //        {
    //            std::cout << i << std::endl;
    //            break;
    //        }
    //    }
    //}

    //Day 4 //
    //std::map<int, std::vector<std::string>> data = AOC::GroupParsedFileByTokens(AOC::ParseFileByLine("Input/P4-input.txt"), std::vector<char>{' '}, true);

    //std::map<std::string, std::string> requiredFields { {"byr", "19[2-8][0-9]|199[0-9]|200[0-2]"},
    //                                                    {"iyr", "201[0-9]|2020"},
    //                                                    {"eyr", "202[0-9]|2030"},
    //                                                    {"hgt", "^((1([5-8][0-9]|9[0-3]))cm|(59|6[0-9]|7[0-6])in)"},
    //                                                    {"hcl", "#[0-9a-f]{6}"},
    //                                                    {"ecl", "amb|blu|brn|gr[yn]|hzl|oth"},
    //                                                    {"pid", "^[0-9]{9}$"} };

    ////Problem 1
    //std::cout << Day4::CountValidPassports(data, requiredFields, false) << std::endl;

    ////Problem 2
    //std::cout << Day4::CountValidPassports(data, requiredFields, true) << std::endl;

    //Day 3//
    /*std::vector<std::string> input = AOC::ParseFileByLine("Input/P3-input.txt");
    std::cout << Day3::CountTreesOnToboganPath(input, 3, 1) << std::endl;

    std::array< std::array<int, 2>, 5> slopes{{ {{1, 1}}, {{3, 1}}, {{5, 1}}, {{7,1}}, {{1,2}} }};

    unsigned int trees = 1;
    for (auto a : slopes) { trees *= Day3::CountTreesOnToboganPath(input, a[0], a[1]); };

    std::cout << trees << std::endl;*/

    //Day 2//
    //std::vector<std::string> input = AOC::ParseFileByLine("Input/P2-input.txt");
    //std::cout << Day2::ValidatePasswords(input, Day2::ValidateQuantity) << std::endl;
    //std::cout << Day2::ValidatePasswords(input, Day2::ValidatePosition) << std::endl;

    //Day 1//
    //std::vector<int> input = AOC::ParseListFromFile<int>("Input/P1-input.txt");

    //const int SUM = 2020;
    //std::cout << Day1::FindCoupletSum(input, SUM) << std::endl;
    //std::cout << Day1::FindTripletSum(input, SUM) << std::endl;

    //End Timer Code
    auto stopTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stopTime - startTime);

    std::cout << duration.count() << " microseconds" << std::endl;

    while (!std::cin.get()) {}
    return 0;
}