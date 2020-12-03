
import std.core;
import AOCUtil;
import Day1;
import Day2;
import Day3;


int main()
{
    //Start Timer Code
    auto startTime = std::chrono::high_resolution_clock::now();

    //Day 2//
    std::vector<std::string> input = AOC::ParseFileByLine("Input/P3-input.txt");
    std::cout << Day3::CountTreesOnToboganPath(input, 3, 1) << std::endl;

    std::array< std::array<int, 2>, 5> slopes{{ {{1, 1}}, {{3, 1}}, {{5, 1}}, {{7,1}}, {{1,2}} }};

    unsigned int trees = 1;
    for (auto a : slopes) { trees *= Day3::CountTreesOnToboganPath(input, a[0], a[1]); };

    std::cout << trees << std::endl;

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