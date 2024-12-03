#include <ranges>


#include "..\utils\utils.h"

pair<vector<int>,vector<int>> setup(string path){
   const auto strings = aoc::read_lines(path);
   vector<int> first, second;
    for(const auto& s : strings){
        const auto v = aoc::split(s, " ");

        first.push_back(stoi(v[0]));
        second.push_back(stoi(v[1]));
    }
    return {move(first), move(second)};
}

long long Run(pair<vector<int>,vector<int>> inputs){
    auto& [a, b] = inputs;

    std::ranges::sort(a);
    std::ranges::sort(b);

    const auto sum = views::zip_transform([](auto x, auto y) {return abs(x-y);}, a, b);

    return  reduce(sum.begin(), sum.end(), 0LL);
   
}

void printResult(long long res){
    cout << "Result: " << res << endl;
}



int main() {

    aoc::timer t;
    // Load inputs and run computation
    const auto inputs = setup("input.txt");
    const auto result = Run(inputs);
    // Print the result
    printResult(result);

    return 0;
}