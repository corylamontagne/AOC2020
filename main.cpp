
import std.core;
import AOCUtil;
import Day1;
import Day2;
import Day3;
import Day4;
import Day5;
import Day6;
import Day7;

int main()
{
    //Start Timer Code
    auto startTime = std::chrono::high_resolution_clock::now();

    //Day 7 //
    std::vector<std::string> input = AOC::ParseFileByLine("Input/P7-input.txt");
    std::string bagToCheck = "shiny gold";

    Day7::MatryoshkaBags mb = Day7::GetMatryoshkaBags(input, bagToCheck);
    //Problem 1
    std::cout << Day7::GetNumberOfParents(mb, bagToCheck) << std::endl;

    //Problem 1
    std::cout << Day7::GetNumberOfBagsToContain(mb, bagToCheck) << std::endl;


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