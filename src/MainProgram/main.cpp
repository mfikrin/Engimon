#include "Map.hpp"
#include "../Player//Player.hpp"
#include "BookOfLore.hpp"
#include "../Engimon/EngimonEnemy.hpp"
#include "../Position/Position.hpp"
#include "../Engimon/Engimon.hpp"
#include "../Battle/Battle.hpp"
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
    Map peta("../Map/map.txt");
    vector<EngimonEnemy> listEngimonLiar;

    Player pemain("Randy", dapet);

    peta.BacaFile();
    peta.Render(pemain, listEngimonLiar);
    char command;
    int jumlahIterasi = 0;
    do
    {
        cin >> command;
        pemain.Move(command);
        listEngimonLiar = peta.MoveListEngimonEnemy(listEngimonLiar, pemain); //gerakan engimon liarnya
        if (jumlahIterasi % 3 == 0 && listEngimonLiar.size() < 5)             // tambahin engimon setiap 3 move
        {
            listEngimonLiar = peta.addEngimonEnemy(listEngimonLiar, pemain); // tambahkan engimonliar
        }
        peta.Render(pemain, listEngimonLiar);
        // Battle::battleEngimon(pemain, listEngimonLiar[0]);
        if (peta.EnemyNear(pemain, listEngimonLiar) != 999)
        {
            cout << "APAKAH ANDA INGIN BATTLE ?" << endl;
            cin >> command;
            if (command == 'y')
            {
                int a = Battle::battleEngimon(pemain, listEngimonLiar[peta.EnemyNear(pemain, listEngimonLiar)]);
                if (a == 1)
                {
                    cout << "menang" << endl;
                    listEngimonLiar.erase(listEngimonLiar.begin() + peta.EnemyNear(pemain, listEngimonLiar));
                }
                else
                {
                    cout << "kalah" << endl;
                }
            }
            else
            {
                cout << "okay bubayy" << endl;
            }
            peta.Render(pemain, listEngimonLiar);
        }

        jumlahIterasi++;
    } while (command != 'q');
    return 0;
}
