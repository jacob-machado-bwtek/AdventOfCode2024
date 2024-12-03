#include <ranges>


#include "..\utils\utils.h"
auto setup(string path){
    const auto strings = aoc::read_lines(path);
    vector<vector<int>> Collection;
    for(const auto& s : strings){
        const auto v = aoc::split(s, " ");
        vector<int> nums;
        std::transform(v.begin(), v.end(), std::back_inserter(nums), [](const auto& s) { return std::stoi(s); });

        Collection.push_back(nums);
    }

    auto criteria = [](const vector<int>& numbers) -> bool {
        bool direction = numbers[1] > numbers[0];
        for(int i = 1; i < numbers.size(); i++){
            if((numbers[i] > numbers[i-1]) != direction){
                return false;
            }
            if(abs(numbers[i] - numbers[i-1]) < 1 || abs(numbers[i] - numbers[i-1]) > 3){
                return false;
            }
        }
        return true;
    };


    int count = 0;
    for(const auto& n : Collection){
        if(criteria(n)){
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