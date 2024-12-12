#include <ranges>


#include "..\utils\utils.h"
#include <unordered_map>


char rotate(char c){
    switch(c){
            case '^': return '>'; break;
            case '>': return 'v'; break;
            case 'v': return '<'; break;
            case '<': return '^'; break;
    }
    //should never happen
    return '0';
}

const unordered_map<char,pair<int,int>> MoveDirs{
    {'^', {0,-1}},
    {'>', {1,0}},
    {'v', {0,1}},
    {'<', {-1,0}}
};

vector<string> ParseFile(string path){
    //do not be overthinking
    const auto strings = aoc::read_lines(path);
    return strings;
}

bool checkObstacleCycle(vector<string>& str, pair<int,int> start, char startDir, pair<int,int> obstacle){
    map<pair<int,int>,string> DirectionAtPosition;
    char curr = startDir;
    int posX = start.first;
    int posY = start.second;

    DirectionAtPosition.emplace(make_pair(posX,posY), string{startDir}); 
    
    auto isValid = [&str](int x, int y){
        return y >= 0 and y < str.size() and x >= 0 and x < str[y].length();
    };

    do{
        auto move = MoveDirs.at(curr);
        auto [nextX, nextY] = make_pair(posX + move.first, posY + move.second);

        if(!isValid(nextX, nextY)){
            break;
        }

        char nextTile = (nextX == obstacle.first and nextY == obstacle.second) ? 'O' : str[nextY][nextX];

        switch(nextTile){
            case 'O':
            case '#':
                curr = rotate(curr);
            break;

            default:
                posX = nextX;
                posY = nextY;
                auto& history = DirectionAtPosition[make_pair(nextX, nextY)];
                if(history.contains(curr)){
                    return true;
                }
                history.push_back(curr);
                break;

        }

    }while(isValid(posX,posY));
    return false;
}

int FollowPath(vector<string>& vec){
    auto iter = ranges::find_if(vec, [](const auto& s){return s.contains('^') or s.contains('v') or s.contains('<') or s.contains('>');});
    if(iter == vec.end()){
        throw exception("No starting position found");
    }

    int posy = distance(vec.begin(), iter); //row
    int posx = iter->find_first_of("^v<>"); //col
    
    char start = vec[posy][posx];
    char curr = vec[posy][posx];

    int numObstacles = 0;

    for(auto y=0; y < vec.size(); y++){
        auto& row = vec[y];
        for(auto x=0; x < row.length(); x++){
            if(row[x] == '#'){

            }
            if(checkObstacleCycle(vec, make_pair(posx,posy),start,make_pair(x,y))){
                numObstacles++;
            }
        }
    }
    return numObstacles;

}

int main(){
    aoc::timer t;
    vector<string> vec = ParseFile("input.txt");

    int x = FollowPath(vec);
    cout << x << endl;



}