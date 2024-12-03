#include <ranges>


#include "..\utils\utils.h"

string setup(string path){
    std::ifstream file(path, std::ios::in);
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    return content;
        
}

long long run(regex MulPattern, regex DoPattern, regex DontPattern, string content){
    std::smatch match;
    long long res = 0;
    while (std::regex_search(content, match, MulPattern)) {
        auto [a, b] = aoc::parse_line<int, int>(R"(mul\((\d+),(\d+)\))", match[0]);
        res += a * b;
        content = match.suffix();
    }
    return res;
}



int main() {
    //regex for mul
    aoc::timer t;
    const regex MulPattern(R"(mul\([0-9]*,[0-9]*\))");
    const regex DoPattern(R"(do\(\))");
    const regex DontPattern(R"(don't\(\))");
    auto str = setup("input.txt");
    auto res = run(MulPattern, DoPattern, DontPattern, str);
    cout << "Result: " << res << endl;  
}