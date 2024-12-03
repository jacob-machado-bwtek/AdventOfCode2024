#include <ranges>


#include "..\utils\utils.h"
#include <unordered_map>


pair<vector<int>,unordered_map<int,int>> setup(string path){
   const auto strings = aoc::read_lines(path);
   vector<int> first;
    unordered_map<int,int> second;

    for(const auto& s : strings){
        const auto v = aoc::split(s, " ");

        first.push_back(stoi(v[0]));
        second[stoi(v[1])]++;
    }
    return {move(first), move(second)};
}

long long Run(pair<vector<int>,unordered_map<int,int>> inputs){
  long long sum = 0;
  for(auto& i : inputs.first){
    sum += inputs.second[i] * i;
  } 
  return sum;
}


int main() {

    aoc::timer t;
    // Load inputs and run computation
    const auto inputs = setup("input.txt");
    const auto result = Run(inputs);
    // Print the result
    cout << "Result: " << result << endl;

    return 0;
}