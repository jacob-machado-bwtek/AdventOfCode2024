#include <ranges>

#include "..\utils\utils.h"

struct File{
    int Id;
    bool IsEmpty;
    int Length;
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
            f.Length = str[i]-'0';
            num++;
           for (int j = 0; j < str[i] - '0'; j++) {
                blocks.push_back(f);
            }
        }else{
            File f;
            f.Id = -1;
            f.IsEmpty = true;
            for (int j = 0; j < str[i] - '0'; j++) {
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

void CompactFiles(std::vector<File>& data) {
    ofstream outFile("output.txt");
    

    int totalBlocks = data.size();


    int maxId = 0;
    for (const auto& block : data) {
        if (!block.IsEmpty) {
            maxId = max(maxId, block.Id);
        }
    }

    for (int id = maxId; id >= 0; --id) {
        int fileStart = -1, fileEnd = -1;
        //find beginning and ending of free space
        for (int i = 0; i < totalBlocks; ++i) {
            if (data[i].Id == id && !data[i].IsEmpty) {
                if (fileStart == -1) fileStart = i;
                fileEnd = i;
            }
        }

        if (fileStart == -1) continue; // File not found

        int fileLength = fileEnd - fileStart + 1;

        // Find the leftmost span of free space that can fit the file
        int freeStart = -1, freeLength = 0;
        for (int i = 0; i < totalBlocks; ++i) {
            if (data[i].IsEmpty) {
                if (freeStart == -1) freeStart = i;
                ++freeLength;
                if (freeLength >= fileLength) break;
            } else {
                freeStart = -1;
                freeLength = 0;
            }
        }

        if (freeLength >= fileLength && freeStart != -1 && freeStart < fileStart) {
            // Move the file to the new location
            for (int i = 0; i < fileLength; ++i) {
                data[freeStart + i] = { id, false };
            }

            // Clear the old file location
            for (int i = fileStart; i <= fileEnd; ++i) {
                data[i] = { -1, true };
            }
        }
    }
    PrintTheList2(data, outFile);
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
    
    CompactFiles(data);

    auto CheckSum = calculateChecksum(data);
    cout << "Checksum: " << CheckSum << endl;

}