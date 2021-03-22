#include "Map.hpp"
#include "Player.hpp"
#include "BookOfLore.hpp"
#include "EngimonEnemy.hpp"
#include "Position.hpp"
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
        pemain.Move(command);

        // Nanti mau dibuat fungsi baru yang dibawah ini
        // DEFINISIKAN POSITION ENGIMON YANG BARU
        int x = rand() % 12;
        int y = rand() % 10;

        Position engimonPosition(x, y);

        //INISIALISASI ENEMY BARU
        vector<Element> el;
        EngimonEnemy enemy(engimonPosition, "bebas", "bebas", 1, el);

        // TAMBAHKAN KE listEngimonLiar
        listEngimonLiar.push_back(enemy);

        peta.Render(pemain, listEngimonLiar);
    } while (command != 'q');
    return 0;
}
