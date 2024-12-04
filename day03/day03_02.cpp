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
    bool AddToSum = true;

    try{
    regex combined(R"((mul\((\d+),(\d+)\))|(do\(\))|(don't\(\)))");




    while(regex_search(content, match, combined)){

        std::string matched_str = match[0].str();

            if(regex_match(matched_str, DontPattern)){
                AddToSum = false;            
            }   
            else if(regex_match(matched_str, DoPattern)){
                AddToSum = true;            
            } 
            else if(regex_match(matched_str, MulPattern) && AddToSum){

                auto [a, b] = aoc::parse_line<int, int>(R"(mul\((\d+),(\d+)\))", match[0]);
                res += a * b;
                
            }
        
            content = match.suffix().str();   

    }
    }
        catch(const std::regex_error& e){
        cout<< "Regex Error" << endl << e.what() << endl;
    }
    return res;
}



int main() {
    //regex for mul
    aoc::timer t;
    const regex MulPattern(R"(mul\((\d+),(\d+)\))");
    const regex DoPattern(R"(do\(\))");
    const regex DontPattern(R"(don't\(\))");
    auto str = setup("input.txt");

    auto res = run(MulPattern, DoPattern, DontPattern, str);
    cout << "Result: " << res << endl;  
}