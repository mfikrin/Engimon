#ifndef MAP_HPP
#define MAP_HPP
#define MINIMUM_LEVEL 2
#include <iostream>
#include <fstream>
// #include <time>

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
                            printEngimonLiar(listEngimonLiar[k]);
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
            x = rand() % render[0].size();
            y = rand() % render.size();
            while ((x < 6 || y > 5) && (x == pemain.getPosition().getXPos() && y == pemain.getPosition().getYPos())) // ulangi terus, karena daerah ini daerah land
            {
                x = rand() % render[0].size();
                y = rand() % render.size();
            }
        }
        else
        {
            x = rand() % render[0].size();
            y = rand() % render.size();

            while ((x > 5 && y < 6) && (x == pemain.getPosition().getXPos() && y == pemain.getPosition().getYPos())) // ulangi terus, karena daerah ini daerah sea
            {
                x = rand() % render[0].size();
                y = rand() % render.size();
            }
        }

        Engimon dapet = ensiklopediaEngimon[indexElementEngimon][indexEngimon];
        Position engimonPosition(x, y);

        //INISIALISASI ENEMY BARU
        vector<Element> el;
        EngimonEnemy enemy(engimonPosition, dapet.getName(), "bebas", dapet.getId(), el);

        // TAMBAHKAN KE listEngimonLiar
        listEngimonLiar.push_back(enemy);

        return listEngimonLiar;
    }

    void printEngimonLiar(Engimon engimonLiar)
    {
        int id = engimonLiar.getId();
        // Jika Tipenya Fire
        // ANGKA 2 BISA DI GANTI DENGAN MINIMUM LEVEL
        if (id > 2600 && id < 2700)
        {
            if (engimonLiar.getLevel() < MINIMUM_LEVEL)
            {
                cout << "e";
            }
            else
            {
                cout << "E";
            }
        }
        else if (id > 2700 && id < 2800)
        {
            if (engimonLiar.getLevel() < MINIMUM_LEVEL)
            {
                cout << "f";
            }
            else
            {
                cout << "F";
            }
        }
        else if (id > 2800 && id < 2900)
        {
            if (engimonLiar.getLevel() < MINIMUM_LEVEL)
            {
                cout << "g";
            }
            else
            {
                cout << "G";
            }
        }
        else if (id > 2900 && id < 3000)
        {
            if (engimonLiar.getLevel() < MINIMUM_LEVEL)
            {
                cout << "i";
            }
            else
            {
                cout << "I";
            }
        }
        else // artinya water
        {
            if (engimonLiar.getLevel() < MINIMUM_LEVEL)
            {
                cout << "w";
            }
            else
            {
                cout << "W";
            }
        }
    }

    // OTHER METHOD
    vector<EngimonEnemy> MoveListEngimonEnemy(vector<EngimonEnemy> listEngimonLiar, Player player)
    {
        // LOOPING SEMUA ENGIMON ENEMY pada LISTENGIMONLIAR
        int a; // adalah arah gerakan engimon
        for (int i = 0; i < listEngimonLiar.size(); i++)
        {
            a = rand() % 4; // angka 4 = 4 jenis gerakan

            Position P;
            Position oldPosition;
            P = listEngimonLiar[i].getPosition(); // dapatkan posisi awalnya
            oldPosition = P;
            switch (a)
            {
            case 0:
                P.up();
                break;
            case 1:
                P.left();
                break;
            case 2:
                P.down();
                break;
            case 3:
                P.right();
                break;
            }
            // cout << "a: " << a << " x: " << oldPosition.getXPos() << " y: " << oldPosition.getYPos() << " xbaru: " << P.getXPos() << " ybaru: " << P.getYPos();
            P = MoveEnemy(listEngimonLiar, player, listEngimonLiar[i], oldPosition, P);
            // cout << " x: " << P.getXPos() << " y: " << P.getYPos() << endl;
            listEngimonLiar[i].moveEngimonEnemy(P);
        }
        return listEngimonLiar;
    }

    Position MoveEnemy(vector<EngimonEnemy> listEngimonLiar, Player player, EngimonEnemy enemy, Position oldPosition, Position newPosition)
    {
        bool sama = false;
        if (enemy.getPosition().getXPos() == player.getPosition().getXPos() && enemy.getPosition().getYPos() == player.getPosition().getYPos())
        {
            for (int i = 0; i < listEngimonLiar.size(); i++)
            {
                if (isPositionSama(enemy, listEngimonLiar[i]))
                {
                    sama = true;
                    break;
                }
            }
        }
        if (sama)
        {
            return oldPosition;
        }
        else
        {
            return newPosition;
        }
    }

    bool isPositionSama(EngimonEnemy enemy1, EngimonEnemy enemy2)
    {
        if (enemy1.getPosition().getXPos() == enemy2.getPosition().getXPos() && enemy1.getPosition().getYPos() == enemy2.getPosition().getYPos())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

#endif