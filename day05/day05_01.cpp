#include <ranges>


#include "..\utils\utils.h"
#include <unordered_map>

auto parseData(const string& path){
    const auto strings = aoc::read_lines(path, aoc::Blanks::Allow, aoc::Trim::Yes);
    unordered_map<int,vector<int>> rulesForeward;
    unordered_map<int,vector<int>> rulesBackward;
    vector<vector<int>> UpdateData;

    int SeparatorLine = 0;
    //find the first empty line
    for(int i = 0; i < strings.size(); i++){
        if(strings[i].empty()){
            SeparatorLine = i;
            break;
        }

    }

    for(int i = 0; i < SeparatorLine; i++){
        const auto v = aoc::split(strings[i], "|");
        rulesForeward[stoi(v[0])].push_back(stoi(v[1]));
        rulesBackward[stoi(v[1])].push_back(stoi(v[0]));
    }


    for(int i = SeparatorLine+1; i < strings.size(); i++){
        UpdateData.push_back(aoc::make_vector<int>(strings[i]));
        
    }

    return make_tuple(rulesForeward,rulesBackward, UpdateData);
}

int middleValue(vector<int> a){
    //find value of item at center of odd length list
    return a[a.size()/2];

    
}

int isRightOrder(const unordered_map<int,vector<int>>& rules, const vector<int> update){
    for(int i = 0; i < update.size(); ++i){
        for(int j = 0; j < i; ++j){
            auto it = rules.find(update[j]);

            if(it != rules.end()){
                for(int n: it->second){
                    if(update[i] == n){
                        return 0;
                    }
                }             
            }
        }
    }

    return middleValue(update);
}

int verifyPages(unordered_map<int,vector<int>> foreward, unordered_map<int,vector<int>> backward, 
                vector<vector<int>> UpdateData, vector<int>& brokenUpdates){
    int sum = 0;
    int val = 0;

    for(size_t i = 0; i < UpdateData.size(); i++){
        val = isRightOrder(backward, UpdateData[i]);

        if(val != 0){
            sum += val;
        }else{
            brokenUpdates.push_back(i); //store the index of the broken update for part 2
        }
    }
    return sum;
}

int fixTheUpdate(unordered_map<int,vector<int>> foreward, vector<int> &update){
    vector<int> u = update; 

    for(int i =0; i < update.size(); i++){
        bool changed = false;
        auto it = foreward.find(update[i]);

        if(it != foreward.end()){
            for(int j = 0; j < i; j++){
                for(int n : it->second){
                    if(u[j] == n){
                        u.erase(u.begin()+i);
                        changed = true;
                        u.insert(u.begin()+j,update[i]);
                        break;  
                    }
                }

            if(changed){
                break;
                }
            }
        }
    }

    return middleValue(u);
}




int CorrectTheUpdates(unordered_map<int,vector<int>> foreward, unordered_map<int,vector<int>> backward, 
                      vector<vector<int>> UpdateData, vector<int> brokenUpdates){
    //brokenupdates now has all updates to fix
    int sum =0;
    for(int n: brokenUpdates){
        sum += fixTheUpdate(foreward,UpdateData[n]);
    }
    
    return sum;

}



int main(){
    aoc::timer t;
    vector<int> brokenUpdates;

    auto [foreward,backward,list] = parseData("input.txt");

    int sum = verifyPages(foreward,backward,list, brokenUpdates); 
    cout << "Part1 solution: "<< sum << endl;

    //part 2
    int fixed = CorrectTheUpdates(foreward,backward,list,brokenUpdates);

    cout << "Part2 solution: "<< fixed << endl;
    
}