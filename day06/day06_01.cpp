#include <ranges>


#include "..\utils\utils.h"


enum Direction{
    UP = 0,
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3
};
enum Tile{
    EMPTY = 0,
    TREE = 1,

    GUARD = 2,
    VISITED = 6,
    
};


vector<vector<int>> ParseFile(string path){
    const auto strings = aoc::read_lines(path);
    vector<vector<int>> res;
    for(const auto& s : strings){
        vector<int> temp;
        for(const auto& c : s){
            switch (c)
            {
            case '.': temp.push_back(0); break;
                /* code */
            case '#': temp.push_back(1); break;

            case '^': temp.push_back(2); break;
            case '>': temp.push_back(3); break;
            case 'v': temp.push_back(4); break;
            case '<': temp.push_back(5); break;

            case 'X': temp.push_back(6); break;
            
            default:
                exception("Invalid character in input file");
            break;
            }
        }
        res.push_back(temp);
    }
    return res;
}

int FollowPath(vector<vector<int>>& vec){
    pair<int,int> pos = {0,0};

    int rows = vec.size();
    int cols = vec[0].size();
    cout << rows << " " << cols << endl;

    // find position of 2 in vector
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(vec[i][j] == 2){
                pos = {i,j};
                break;
            }
        }
    }

    // follow path
    Direction dir = UP;
    int count = 0;

    // dir 0 ^, 1 >, 2 v, 3 <, 

    cout << "starting loop" << endl;
    //while in bounds
    while((pos.first >= 0 && pos.first < rows) && (pos.second >= 0 && pos.second < cols)){
           //cin >> x;
        cout<< pos.first << " " << pos.second << " " <<dir << endl;
        vec[pos.first][pos.second] = VISITED; //6 is visited value

        switch (dir)
        {
        case UP:
            //mark current as visited, then move foreward if possible. If not, change direction
            if(pos.first > 0 && vec[pos.first-1][pos.second] == TREE){
                dir = RIGHT;
            }
            else{
                pos.first--; //move up
            }
        break;

        case RIGHT:
            if(pos.first+1 < cols && vec[pos.first][pos.second+1] == TREE){
                dir = DOWN;
            }
            else{
                pos.second++; //move right
            }

        break;

        case DOWN:
        cout << "down start" << endl;
            if(pos.first+1 < rows && vec[pos.first+1][pos.second] == TREE){
                dir = LEFT;
            }
            else{
                pos.first++; //move down
            }        
        cout << "down end" << endl;
        break;

        case LEFT:
            if(pos.second > 0 && vec[pos.first][pos.second-1] == TREE){
                dir = UP;
            }
            else{
                pos.second--; //move left
                
            }        
        break;
        }
        if((pos.first < 0 || pos.first >= rows) || (pos.second < 0 || pos.second >= cols)){
                cout << "breaking" << endl;  
            break;
        }
        //vec[pos.first][pos.second] = GUARD; //2 is guard value
    }
    cout << "exited loop" << endl;  

    for_each(vec.begin(), vec.end(), [&count](const auto& v){
        for(const auto& i : v){
            if(i == VISITED){
                count++;
            }
        }
    });
    return count;
}

int main(){
    vector<vector<int>> vec = ParseFile("input.txt");

    int x = FollowPath(vec);
    cout << x << endl;

    for(const auto& v : vec){
        for(const auto& i : v){
            cout << i << " ";
        }
        cout << endl;
    }
    cout << x << endl;

}