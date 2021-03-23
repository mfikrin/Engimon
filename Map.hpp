#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
// #include <string>
#include <fstream>
// #include <time>

//#include "EngimonEnemy.hpp"
//#include "EngimonUser.hpp"
#include "Position.hpp"
#include "BookOfLore.hpp"
#include "Player.hpp"
#include <vector>
#include "EngimonEnemy.hpp"
#include "Engimon.hpp"

using namespace std;

class Map
{
private:
    string namaFile;
    //   EngimonEnemy Enemy;
    //   EngimonUser User;
    vector<string> render;
    Position playerPosition;
    Position activeEngimonPosition;
    Position engimonPosition;

    // vector<EngimonEnemy> listEnemy;

public:
    Map(string namaFile)
    {
        this->namaFile = namaFile;
    }
    void BacaFile()
    {
        string baris;
        //Membuka file dalam mode membaca
        ifstream infile;
        //menunjuk ke sebuah file
        infile.open(this->namaFile);

        //cout << endl    << ">= Membuka dan membaca file " << endl;
        //jika file ada maka
        //int i = 0
        if (infile.is_open())
        {
            //melakukan perulangan setiap barus
            //string row = "";
            while (getline(infile, baris))
            {
                //dan tampilkan di sini
                //for (int j = 0; j < 12; j++)
                //{
                // if (isEnemy(i, j))
                // {
                //     cout << "E";
                // }
                // else if (isUser(i, j))
                // {
                //     cout << "P";
                // }

                //cout << baris[j];
                // row += baris[j];
                // }
                //cout << '\n';
                //i += 1;
                render.push_back(baris);
            }
            //tutup file tersebut setelah selsai
            infile.close();
        }
        //jika tidak ditemukan file maka akan menampilkan ini
        else
            cout << "Unable to open file";
    }

    void Render(Player &player, vector<EngimonEnemy> listEngimonLiar)
    {
        // srand(time(NULL));
        playerPosition = player.getPosition();
        activeEngimonPosition = player.getActiveEngimonPosition();

        // // DEFINISIKAN POSITION ENGIMON YANG BARU
        // int x = rand() % 12;
        // int y = rand() % 10;

        // Position engimonPosition(x, y);
        //
        // //INISIALISASI ENEMY BARU
        // vector<Element> el;
        // EngimonEnemy enemy(engimonPosition, "bebas", "bebas", 1, el);
        // this->enemy

        for (int i = 0; i < render.size(); ++i)
        {
            for (int j = 0; j < render[i].size(); ++j)
            {
                // ITERASI listEngimonLiar
                for (int k = 0; k < listEngimonLiar.size(); k++)
                {
                    if (i == listEngimonLiar[k].getPosition().getYPos() && j == listEngimonLiar[k].getPosition().getYPos())
                    {
                        cout << 'W';
                    }
                }

                if (i == playerPosition.getYPos() && j == playerPosition.getXPos())
                {
                    cout << 'P';
                }
                else if (i == activeEngimonPosition.getYPos() && j == activeEngimonPosition.getXPos())
                {
                    cout << 'X';
                }

                // else if (i == engimonPosition.getYPos() && j == engimonPosition.getXPos())
                // {
                //     cout << 'W';
                // }
                else
                {
                    cout << render[i][j];
                }
            }
            cout << endl;
        }
    }

    // bool isEnemy(int i, int j)
    // {
    //     return Enemy.getPosition().getYPos() == i && Enemy.getPosition().getXPos() == j;
    // }

    // bool isUser(int i, int j)
    // {
    //     return User.getPosition().getYPos() == i && User.getPosition().getXPos() == j;
    // }

    vector<EngimonEnemy> addEngimonEnemy(vector<EngimonEnemy> listEngimonLiar, Player pemain)
    {
        BookOfLore ensiklopedia;
        vector<vector<Engimon>> ensiklopediaEngimon = ensiklopedia.allEngimon();
        vector<vector<Skill>> ensiklopediaSkill = ensiklopedia.allSkill();

        // RANDOM ENGIMON YANG MUNCUL
        int indexElementEngimon = rand() % ensiklopediaEngimon.size();
        int indexEngimon = rand() % ensiklopediaEngimon[indexElementEngimon].size();
        int x, y;
        if (indexElementEngimon == 1 || indexElementEngimon == 4) //jika engimon liar yang muncul bertipe water atau ice
        {
            x = rand() % 12;
            y = rand() % 10;
            while ((x < 6 || y > 5) && (x == pemain.getPosition().getXPos() && y == pemain.getPosition().getYPos())) // ulangi terus, karena daerah ini daerah land
            {
                x = rand() % 12;
                y = rand() % 10;
            }
        }
        else
        {
            x = rand() % 12;
            y = rand() % 10;

            while ((x > 5 && y < 6) && (x == pemain.getPosition().getXPos() && y == pemain.getPosition().getYPos())) // ulangi terus, karena daerah ini daerah sea
            {
                x = rand() % 12;
                y = rand() % 10;
            }
        }

        Engimon dapet = ensiklopediaEngimon[indexElementEngimon][indexEngimon];

        // int x = rand() % 12;
        // int y = rand() % 10;

        Position engimonPosition(x, y);

        //INISIALISASI ENEMY BARU
        vector<Element> el;
        EngimonEnemy enemy(engimonPosition, "bebas", "bebas", 1, el);

        // TAMBAHKAN KE listEngimonLiar
        listEngimonLiar.push_back(enemy);

        return listEngimonLiar;
    }
};

#endif