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
        pemain.Move(command);

        // // Nanti mau dibuat fungsi baru yang dibawah ini

        // // RANDOM ENGIMON YANG MUNCUL
        // indexElementEngimon = rand() % ensiklopediaEngimon.size();
        // indexEngimon = rand() % ensiklopediaEngimon[indexElementEngimon].size();
        // int x, y;
        // if (indexElementEngimon == 1 || indexElementEngimon == 4) //jika engimon liar yang muncul bertipe water atau ice
        // {
        //     x = rand() % 12;
        //     y = rand() % 10;
        //     while ((x < 6 || y > 5) && (x == pemain.getPosition().getXPos() && y == pemain.getPosition().getYPos())) // ulangi terus, karena daerah ini daerah land
        //     {
        //         x = rand() % 12;
        //         y = rand() % 10;
        //     }
        // }
        // else
        // {
        //     x = rand() % 12;
        //     y = rand() % 10;

        //     while ((x > 5 && y < 6) && (x == pemain.getPosition().getXPos() && y == pemain.getPosition().getYPos())) // ulangi terus, karena daerah ini daerah sea
        //     {
        //         x = rand() % 12;
        //         y = rand() % 10;
        //     }
        // }

        // Engimon dapet = ensiklopediaEngimon[indexElementEngimon][indexEngimon];

        // // DEFINISIKAN POSITION ENGIMON YANG BARU

        // // int x = rand() % 12;
        // // int y = rand() % 10;

        // Position engimonPosition(x, y);

        // //INISIALISASI ENEMY BARU
        // vector<Element> el;

        // EngimonEnemy enemy(engimonPosition, dapet.getName(), "bebas", 1, el);

        // // TAMBAHKAN KE listEngimonLiar
        // listEngimonLiar.push_back(enemy);

        // // for (int i = 0; i < listEngimonLiar.size(); i++)
        // // {
        // //     listEngimonLiar[i].print();
        // // }

        // // batas bawah

        listEngimonLiar = peta.addEngimonEnemy(listEngimonLiar, pemain);

        peta.Render(pemain, listEngimonLiar);
    } while (command != 'q');
    return 0;
}
