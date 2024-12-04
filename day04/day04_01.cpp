#include <ranges>


#include "..\utils\utils.h"



vector<vector<char>> readGridFromFile(const string& path){
     vector<vector<char>> grid;
    ifstream inputFile(path);

    if (!inputFile) {
        cerr << "Error: Unable to open file " << path << endl;
        return grid;
    }

    string line;
    while (getline(inputFile, line)) {
        vector<char> row;
        stringstream ss(line);
        char ch;

        // Split each line into characters (assuming space-separated)
        while (ss >> ch) {
            row.push_back(ch);
        }
        if (!row.empty()) {
            grid.push_back(row);
        }
    }

    inputFile.close();
    return grid;
}

//O(word.len)
bool SearchWord(const vector<vector<char>>& grid, const string& word, int row, int col, int rowDir, int colDir){
    int rows = grid.size();
    int cols = grid[0].size();
    int len = word.length();

    for(int i = 0; i < len; i++){
        int newRow = row + i*rowDir;
        int newCol = col + i*colDir;

        if(newRow<0 || newRow >= rows || newCol < 0 || newCol >= cols || grid[newRow][newCol] != word[i]){
            return false;
        }
    }

    return true;
}

//O(rows*cols*8*word.len)
int countWordOccurances(const vector<vector<char>>& grid, const string& word){
    int rows = grid.size();
    int cols = grid[0].size();
    int len = word.length();
    int count = 0;

    const vector<pair<int, int>> directions = {
        {0, 1},   // Right
        {1, 0},   // Down
        {0, -1},  // Left
        {-1, 0},  // Up
        {1, 1},   // Down-Right
        {1, -1},  // Down-Left
        {-1, -1}, // Up-Left
        {-1, 1}   // Up-Right
    };

    for(int row = 0; row < rows; row++){
        for(int col = 0; col < cols; col++){
            for(const auto& dir : directions){
                if(SearchWord(grid, word, row, col, dir.first, dir.second)){
                    count++;
                }
            }
        }
    }
    return count;
}





int main(){
    aoc::timer t;
    auto grid = readGridFromFile("input.txt");
    int res = countWordOccurances(grid, "XMAS");
    cout << "Result: " << res << endl;

}