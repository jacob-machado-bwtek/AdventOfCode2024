#include <ranges>


#include "..\utils\utils.h"



vector<vector<char>> readGridFromFile(const string& path) {
    vector<string> str = aoc::read_lines(path);
    vector<vector<char>> charGrid;
    for (const string& line : str) {
        charGrid.emplace_back(line.begin(), line.end());
    }
    return charGrid;

}

bool SearchWord(const vector<vector<char>>& grid, int row, int col) {
    int rows = grid.size();
    int cols = grid[0].size();

    //check boundaris
    if (row - 1 < 0 || row + 1 >= rows || col - 1 < 0 || col + 1 >= cols) {
        return false;
    }

    // Check all four rotations of the pattern
    // i forgot that it could be rotated so this took me so many tries, im embarrassed i should be embarrassed
    bool original = grid[row - 1][col - 1] == 'M' && grid[row - 1][col + 1] == 'S' &&
                    grid[row + 1][col - 1] == 'M' && grid[row + 1][col + 1] == 'S' &&
                    grid[row][col] == 'A';

    bool rotated90 = grid[row - 1][col - 1] == 'M' && grid[row + 1][col - 1] == 'S' &&
                     grid[row - 1][col + 1] == 'M' && grid[row + 1][col + 1] == 'S' &&
                     grid[row][col] == 'A';

    bool rotated180 = grid[row - 1][col - 1] == 'S' && grid[row - 1][col + 1] == 'M' &&
                      grid[row + 1][col - 1] == 'S' && grid[row + 1][col + 1] == 'M' &&
                      grid[row][col] == 'A';

    bool rotated270 = grid[row - 1][col - 1] == 'S' && grid[row + 1][col - 1] == 'M' &&
                      grid[row - 1][col + 1] == 'S' && grid[row + 1][col + 1] == 'M' &&
                      grid[row][col] == 'A';

    return original || rotated90 || rotated180 || rotated270;
}

//O(rows*cols*8*word.len)
long countXMasOccurances(const vector<vector<char>>& grid){
    int rows = grid.size();
    int cols = grid[0].size();
    long count = 0;
    
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if(SearchWord(grid, row, col)){
                count++;
            }
        }
    }
    return count;
}





int main(){
    aoc::timer t;
    auto grid = readGridFromFile("input.txt");



   long res = countXMasOccurances(grid);
    cout << "Result: " << res << endl;

}