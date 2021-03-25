#include "BookOfLore.hpp"

int main(){
    BookOfLore buku;
    vector<vector<Engimon>> engimonList = buku.allEngimon();
    for(int i = 0; i < engimonList.size(); ++i){
        for(int j = 0; j < engimonList[i].size(); ++j){
            engimonList[i][j].printEngimon();
        }
    }

    vector<vector<Skill>> skillList = buku.allSkill();
    return 0;
}