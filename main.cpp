
import std.core;
import AOCUtil;
import Day1;
import Day2;


int main()
{
    //Start Timer Code
    auto startTime = std::chrono::high_resolution_clock::now();

    //Day 2//
    std::vector<std::string> input = AOC::ParseFileByLine("Input/P2-input.txt");
    std::cout << Day2::ValidatePasswords(input, Day2::ValidateQuantity) << std::endl;
    std::cout << Day2::ValidatePasswords(input, Day2::ValidatePosition) << std::endl;

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