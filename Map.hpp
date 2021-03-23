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
#include "Element.hpp"

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
        int id;
        bool isTidakAdaEngimon;
        for (int i = 0; i < render.size(); ++i)
        {
            for (int j = 0; j < render[i].size(); ++j)
            {

                if (i == playerPosition.getYPos() && j == playerPosition.getXPos())
                {
                    cout << 'P';
                }
                else if (i == activeEngimonPosition.getYPos() && j == activeEngimonPosition.getXPos())
                {
                    cout << 'X';
                }

                else
                {
                    // ITERASI listEngimonLiar
                    isTidakAdaEngimon = true;
                    int k = 0;
                    while (k < listEngimonLiar.size() && isTidakAdaEngimon)
                    {
                        // Jika terdapat Engimon Liar
                        if (i == listEngimonLiar[k].getPosition().getYPos() && j == listEngimonLiar[k].getPosition().getYPos())
                        {
                            id = listEngimonLiar[k].getId();
                            // Jika Tipenya Fire
                            if (id > 2600 && id < 2700)
                            {
                                cout << "E";
                            }
                            else if (id > 2700 && id < 2800)
                            {
                                cout << "F";
                            }
                            else if (id > 2800 && id < 2900)
                            {
                                cout << "G";
                            }
                            else if (id > 2900 && id < 3000)
                            {
                                cout << "I";
                            }
                            else // artinya water
                            {
                                cout << "W";
                            }
                            isTidakAdaEngimon = false;
                        }
                        k++;
                    }
                    if (isTidakAdaEngimon)
                    {
                        cout << render[i][j];
                    }
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
        EngimonEnemy enemy(engimonPosition, dapet.getName(), "bebas", dapet.getId(), el);

        // TAMBAHKAN KE listEngimonLiar
        listEngimonLiar.push_back(enemy);

        return listEngimonLiar;
    }
};

#endif