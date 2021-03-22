#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
// #include <string>
#include <fstream>

//#include "EngimonEnemy.hpp"
//#include "EngimonUser.hpp"
#include "Position.hpp"
#include "Player.hpp"
#include <vector>

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

    void Render(Player& player){
        playerPosition = player.getPosition();
        //activeEngimonPosition = player.getActiveEngimonPosition();
        for (int i = 0; i < render.size(); ++i)
        {
            for (int j = 0; j < render[i].size(); ++j)
            {
                if (i == playerPosition.getYPos() && j == playerPosition.getXPos()){
                    cout << 'P';
                }else if (i == activeEngimonPosition.getYPos() && j == activeEngimonPosition.getXPos())
                {
                    cout << 'X';
                }
                else{
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
};

#endif