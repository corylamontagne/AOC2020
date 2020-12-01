export module Day1;

import std.core;

 namespace Day1
{
    /// <summary>
    /// Day 1 Problem 1
    /// Assumes there is only 1 pair
    /// </summary>
    export int FindCoupletSum(const std::vector<int>& arr, int sum)
    {
        int result = -1;
        std::vector<int> values;

        for (size_t i = 0; i < arr.size(); ++i)
        {
            auto x = std::find(values.begin(), values.end(), sum - arr[i]);
            if (x != values.end())
            {
                result = *x * arr[i];
                break;
            }

            values.push_back(arr[i]);
        }

        return result;
    }

    /// <summary>
    /// Day 1 Problem 2
    /// Assumes there is only 1 triplet
    /// </summary>
    export int FindTripletSum(std::vector<int> arr, int sum)
    {
        int result = -1;
        int left, right;
        std::sort(arr.begin(), arr.end());

        //no need to parse > 2020
        auto it = std::remove_if(arr.begin(), arr.end(), [](int n) { return n > 2020; });
        arr.erase(it, arr.end());

        size_t arrSize = arr.size();
        for (size_t i = 0; i < arrSize - 2; ++i)
        {
            left = i + 1;
            right = arrSize - 1;

            //check while walking the end pointers in.
            while (left < right)
            {
                int tripSum = arr[i] + arr[left] + arr[right];
                //nailed it
                if (tripSum == sum)
                {
                    result = arr[i] * arr[left] * arr[right];
                    break;
                }
                //these could be smarter, but w/e
                else if (tripSum < sum) { left++; }
                else if (tripSum > sum) { right--; }
            }
        }

        return result;
    }
}