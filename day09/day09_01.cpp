#include <ranges>

#include "..\utils\utils.h"

struct File{
    int Id;
    bool IsEmpty;
};

auto ParseData(const string& path) {
    vector<File> blocks;
    vector<string> data = aoc::read_lines(path);
    //std::vector<std::string> data = { "2333133121414131402" };
    string str= data[0];
    
    int num = 0;
    for(int i = 0; i < str.size(); i++){
        if(i%2 ==0){
            File f;
            f.Id = num;
            f.IsEmpty = false;
            num++;
            for(int j = 0; j < str[i]-'0'; j++){
                blocks.push_back(f);
            }
        }else{
            File f;
            f.Id = -1;
            f.IsEmpty = true;
            for(int j = 0; j < str[i]-'0'; j++){
                blocks.push_back(f);
            }

        }
    }
    return blocks;
}
void PrintTheList(const vector<File>& data, ofstream& outFile){
    for(int i = 0; i < data.size(); i++){
        if(data[i].IsEmpty){
            cout << "." << ",";
        }else{
            cout << data[i].Id << ",";
        }
    }
    cout << endl;
}

void PrintTheList2(const std::vector<File>& data, ofstream& outFile){

    if (!outFile) {
        std::cerr << "Error opening file for writing." << std::endl;
        return;
    }
    for (int i = 0; i < data.size(); i++) {
        if (data[i].IsEmpty) {
            outFile << "." << ",";
        } else {
            outFile << data[i].Id << ",";
        }
    }
    outFile << "\n \n";
}

void SortFileInPlace(vector<File>& data){
    std::ofstream outFile("output.txt");
   // PrintTheList2(data, outFile);
    int R = data.size()-1;
    int L = 0;
    while(L < R){
        while(!data[L].IsEmpty && L < R){
            L++;
        }
        while(data[R].IsEmpty && L < R){

            R--;
        }

        if(data[L].IsEmpty && !data[R].IsEmpty){
            swap(data[L], data[R]);
            //PrintTheList2(data, outFile);
            L++;
            R--;
        }
    }



}

long long calculateChecksum(const std::vector<File>& blocks) {
    long long checksum = 0;
    for (int i = 0; i < blocks.size(); ++i) {
        if (!blocks[i].IsEmpty) { // Skip free space blocks
            checksum += i * blocks[i].Id;
        }
    }
    return checksum;
}

int main(){
    aoc::timer t;
    vector<File> data = ParseData("input.txt");
    
    SortFileInPlace(data);

    auto CheckSum = calculateChecksum(data);
    cout << "Checksum: " << CheckSum << endl;

}