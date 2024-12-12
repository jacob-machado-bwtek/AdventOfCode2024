#include <ranges>
#include <unordered_set>
#include <unordered_map>


#include "..\utils\utils.h"

struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
    bool operator==(const Point &other) const {
        return x == other.x && y == other.y;
    }
};

struct PointHash{
    size_t operator()(const Point &p) const {
        return hash<int>()(p.x) ^ hash<int>()(p.y << 1);
    }
};

vector<string> ParseInput(string path){
    vector<string> data = aoc::read_lines(path);
    return data;
}

void SolvePart1(const vector<string> &map, unordered_set<Point, PointHash> &data){

    int rows = map.size();
    int cols = map[0].size();

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(!isalnum(map[i][j])){
                continue;
            }

            for(int x = 0; x < rows; x++){
                for(int y = 0; y < cols; y++){
                    if(x == i && y == j){
                        continue;
                    }
                    if(map[x][y] != map[i][j]){
                        continue;
                    }

                    int dx = x - i;
                    int dy = y - j;

                    int mx1 = i - dx;
                    int my1 = j - dy;

                    int mx2 = x + dx;
                    int my2 = y + dy;

                    if(mx1 >= 0 && mx1 < rows && my1 >= 0 && my1 < cols){
                        data.insert(Point(mx1, my1));
                    }

                    if(mx2 >= 0 && mx2 < rows && my2 >= 0 && my2 < cols){
                        data.insert(Point(mx2, my2));
                    }



                }
            }
        }
    }

}



void SolvePart2(const vector<string> &map, unordered_set<Point, PointHash> &antinodes) {
    int rows = map.size();
    int cols = map[0].size();

    // Map antenna positions
    unordered_map<char, vector<Point>> antennaPositions;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (isalnum(map[i][j])) {
                antennaPositions[map[i][j]].emplace_back(i, j);
            }
        }
    }

    // Calculate antinodes
    for (const auto &entry : antennaPositions) {
        const auto &positions = entry.second;
        int n = positions.size();

        // Add all antennas as antinodes
        for (const auto &pos : positions) {
            antinodes.emplace(pos);
        }

        // Find antinodes for each pair of antennas
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int x1 = positions[i].x, y1 = positions[i].y;
                int x2 = positions[j].x, y2 = positions[j].y;

                antinodes.emplace(x1, y1);
                antinodes.emplace(x2, y2);

                // Calculate points in line with the two antennas
                int dx = x2 - x1;
                int dy = y2 - y1;

                // Add antinodes in both directions
                int mx1 = x1 - dx, my1 = y1 - dy;
                while (mx1 >= 0 && mx1 < rows && my1 >= 0 && my1 < cols)
                {
                    antinodes.emplace(mx1, my1);
                    mx1 -= dx;
                    my1 -= dy;
                 
                }
                
                
                
                int mx2 = x2 + dx, my2 = y2 + dy;
                while (mx2 >= 0 && mx2 < rows && my2 >= 0 && my2 < cols)
                {
                    antinodes.emplace(mx2, my2);
                    mx2 += dx;
                    my2 += dy;
                 
                }
            }
        }
    }
}


int main(){
    aoc::timer t;
    auto strs = ParseInput("input.txt");
    unordered_set<Point,PointHash> antinodes;
    //SolvePart1(strs, antinodes);
    SolvePart2(strs, antinodes);
    cout << antinodes.size() << endl;
}


