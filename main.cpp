#include "Map.hpp"
#include "Player.hpp"
#include "BookOfLore.hpp"
#include "EngimonEnemy.hpp"
#include "Position.hpp"
#include "Engimon.hpp"
//#include "EngimonUser.hpp"
#include <iostream>
using namespace std;

int main()
{
    BookOfLore ensiklopedia;
    vector<vector<Engimon>> ensiklopediaEngimon = ensiklopedia.allEngimon();
    vector<vector<Skill>> ensiklopediaSkill = ensiklopedia.allSkill();

    int indexElementEngimon = rand() % ensiklopediaEngimon.size();
    int indexEngimon = rand() % ensiklopediaEngimon[indexElementEngimon].size();

    Engimon dapet = ensiklopediaEngimon[indexElementEngimon][indexEngimon];

    Map peta("map.txt");

    vector<EngimonEnemy> listEngimonLiar;

    Player pemain("Randy", dapet);

    peta.BacaFile();
    peta.Render(pemain, listEngimonLiar);
    char command;
    do
    {
        cin >> command;
        pemain.Move(command);                                                 // gerakan playernya
        listEngimonLiar = peta.MoveListEngimonEnemy(listEngimonLiar, pemain); //gerakan engimon liarnya
        listEngimonLiar = peta.addEngimonEnemy(listEngimonLiar, pemain);      // tambahkan engimonliar

        peta.Render(pemain, listEngimonLiar);
    } while (command != 'q');
    return 0;
}
