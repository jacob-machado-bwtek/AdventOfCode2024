#include <ranges>


#include "..\utils\utils.h"

auto isSafe(const vector<int> &numbers){

    for(int i = 0; i < numbers.size(); i++){
        auto filtered = numbers 
            | views::enumerate 
            | views::filter([i](const auto &p) { return get<0>(p) != i; })
            | views::values;
        const bool increasing = ranges::is_sorted(filtered, std::less<>()); //thank you gpt for less
        const bool decreasing = ranges::is_sorted(filtered, std::greater<>());

        if(!increasing && !decreasing){
            continue;
        }

        vector<int> diffs;
        diffs.reserve(numbers.size());

        adjacent_difference(filtered.begin(), filtered.end(), back_inserter(diffs), [](int a, int b) { return abs(a-b); });

        if(ranges::all_of(diffs | views::drop(1), [](const int x) { return x > 0 && x < 4; })){
            return true;
        }

    }
    return false;


}


auto setup(string path){
    const auto strings = aoc::read_lines(path);
    vector<vector<int>> Collection;
    for(const auto& s : strings){
        const auto v = aoc::split(s, " ");
        vector<int> nums;
        std::transform(v.begin(), v.end(), std::back_inserter(nums), [](const auto& s) { return std::stoi(s); });

        Collection.push_back(nums);
    }



    int count = 0;
    for(const auto& n : Collection){
        if(isSafe(n)){
            count++;
        }
    }
    return count;

}

int main(){
    aoc::timer t; // Start the timer
    // Load inputs and run computation
        

    const auto res = setup("input.txt");
    // Print the result
    cout << "Result: " << res << endl;

}