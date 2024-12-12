 #include <ranges>


#include "..\utils\utils.h"

auto ParseData(string path){
    vector<string> data = aoc::read_lines(path);
    vector<tuple<long long, vector<long>>> result;
    //sample line:
    //166170: 970 917 29 667 3
    for (const string& line : data) {
        size_t colon_pos = line.find(':'); // Find the colon separator


        // Parse the number before the colon
        long long key = stoll(line.substr(0, colon_pos));

        // Parse the numbers after the colon
        vector<long> values;
        stringstream ss(line.substr(colon_pos + 1)); // Create a stream for parsing the rest
        long value;
        while (ss >> value) { // Extract each number
            values.push_back(value);
        }

        // Add the parsed data to the result
        result.push_back(make_tuple(key, values));

}

    return result;
}

bool CanProduceKey1(long long key, const vector<long>& values, size_t idx = 1, long long curr = 0) { 
    if(idx == values.size()){
        return curr == key;
    }

    if(CanProduceKey1(key, values, idx + 1, curr + values[idx])){
        return true;
    }

    if(CanProduceKey1(key, values, idx + 1, curr * values[idx])){
        return true;
    }

    return false;
}

bool CanProduceKey2(long long key, const vector<long>& values, size_t idx = 1, long long curr = 0) { 
    if(idx == values.size()){
        return curr == key;
    }

    if(CanProduceKey2(key, values, idx + 1, curr + values[idx])){
        return true;
    }

    if(CanProduceKey2(key, values, idx + 1, curr * values[idx])){
        return true;
    }


    long long newcurr = stoll(to_string(curr) + to_string(values[idx]));
    if(CanProduceKey2(key, values, idx + 1, newcurr)){
        return true;
    }


    return false;
}

unsigned long long SolvePart1(vector<tuple<long long, vector<long>>> data){
    unsigned long long ans = 0;
    for (const auto& [key, values] : data) {
        if(CanProduceKey1(key, values, 1, values[0])){
            ans += key;
        }
    }
    return ans;
}

unsigned long long SolvePart2(vector<tuple<long long, vector<long>>> data){
    unsigned long long ans = 0;
    for (const auto& [key, values] : data) {
        if(CanProduceKey2(key, values, 1, values[0])){
            ans += key;
        }
    }
    return ans;
}


int main() {
    aoc::timer t;
    auto data = ParseData("input.txt");
    auto ans1 = SolvePart1(data);
    auto ans2 = SolvePart2(data);
    cout << "Answer 1: " << ans1 << endl;
    cout << "Answer 2: " << ans2 << endl;


}