
import std.core;
import AOCUtil;
import Day1;


int main()
{
    //Day 1//
    std::vector<int> input = AOC::PaseListFromFile<int>("P1-input.txt");
    const int SUM = 2020;
    std::cout << Day1::FindCoupletSum(input, SUM) << std::endl;
    std::cout << Day1::FindTripletSum(input, SUM) << std::endl;

    while (!std::cin.get()) {}
    return 0;
}