#ifndef MAP_HPP
#define MAP_HPP
#define MINIMUM_LEVEL 2
#define MAP_HEIGHT 10 // ???
#define MAP_WIDTH 12  /// ???
#include <iostream>
#include <fstream>
#include <time.h>

#include "../Position/Position.hpp"
#include "BookOfLore.hpp"
#include "../Player/Player.hpp"
#include <vector>
#include "../Engimon/EngimonEnemy.hpp"
#include "../Engimon/Engimon.hpp"
#include "../Element/Element.hpp"
#include "../Skill/Skill.hpp"

using namespace std;

class Map
{
private:
    string namaFile;
    vector<string> render;
    Position playerPosition;
    Position activeEngimonPosition;
    Position engimonPosition;

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

        if (infile.is_open())
        {
            while (getline(infile, baris))
            {
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
        srand(time(NULL));

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
                        if (j == listEngimonLiar[k].getPosition().getXPos() && i == listEngimonLiar[k].getPosition().getYPos())
                        {
                            printEngimonLiar(listEngimonLiar[k]);
                            isTidakAdaEngimon = false;
                        }
                        k++;
                    }
                    if (isTidakAdaEngimon) // jika tidak ada engimon, print peta
                    {
                        cout << render[i][j];
                    }
                }
            }
            cout << endl;
        }
    }
    vector<EngimonEnemy> addEngimonEnemy(vector<EngimonEnemy> listEngimonLiar, Player pemain)
    {
        BookOfLore ensiklopedia;
        vector<vector<Engimon>> ensiklopediaEngimon = ensiklopedia.allEngimon();
        vector<vector<Skill>> ensiklopediaSkill = ensiklopedia.allSkill();

        // RANDOM ENGIMON YANG MUNCUL
        int indexElementEngimon = rand() % ensiklopediaEngimon.size();
        int indexEngimon = rand() % ensiklopediaEngimon[indexElementEngimon].size();
        // CARI SKILLNYA JUGA
        int indexSkill = rand() % ensiklopediaSkill[indexElementEngimon].size();
        Skill dapetSkill = ensiklopediaSkill[indexElementEngimon][indexSkill];
        int x, y;
        if (indexElementEngimon == 1 || indexElementEngimon == 4) //jika engimon liar yang muncul bertipe water atau ice
        {
            y = rand() % render.size();    // 10
            x = rand() % render[0].size(); // 12
            // Syarat
            //  index x = 6-11 dan index y = 0-5
            while ((x < 6 || y > 4) || (x == pemain.getPosition().getXPos() && y == pemain.getPosition().getYPos())) // ulangi terus, karena daerah ini daerah land
            {
                y = rand() % render.size();    // 10
                x = rand() % render[0].size(); // 12
            }
        }
        else
        {
            y = rand() % render.size();    // 10
            x = rand() % render[0].size(); // 12
            // Syarat
            // tidak dalam index x = 6-11 dan index y = 0-5
            while ((x > 5 && y < 6) || (x == pemain.getPosition().getXPos() && y == pemain.getPosition().getYPos())) // ulangi terus, karena daerah ini daerah sea
            {
                y = rand() % render.size();    // 10
                x = rand() % render[0].size(); // 12
            }
        }

        Engimon dapet = ensiklopediaEngimon[indexElementEngimon][indexEngimon];
        Position engimonPosition(x, y);

        //INISIALISASI ENEMY BARU
        vector<Element> el;
        // tambahkan elemen
        el.push_back(addElement(indexElementEngimon));
        EngimonEnemy enemy(engimonPosition, dapet.getName(), dapet.getSpecies(), dapet.getId(), el);
        // tambahkan skill
        enemy.addSkill(dapetSkill);

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
<<<<<<< HEAD
            cout << enemy.getPosition().getXPos() << player.getPosition().getXPos() << enemy.getPosition().getYPos() << player.getPosition().getYPos();
            return oldPosition;
        }
        else if (enemy.getPosition().getXPos() == player.getActiveEngimon().getPosition().getXPos() && enemy.getPosition().getYPos() == player.getActiveEngimon().getPosition().getYPos())
        {
            cout << enemy.getPosition().getXPos() << player.getActiveEngimon().getPosition().getXPos() << enemy.getPosition().getYPos() << player.getActiveEngimon().getPosition().getYPos();
=======
            // cout << enemy.getPosition().getXPos() << player.getPosition().getXPos() << enemy.getPosition().getYPos() << player.getPosition().getYPos();
            return oldPosition;
        }
        else if (enemy.getPosition().getXPos() == player.getActiveEngimon().getPosition().getXPos() && enemy.getPosition().getYPos() ==player.getActiveEngimon().getPosition().getYPos())
        {
            // cout << enemy.getPosition().getXPos() << player.getPosition().getXPos() << enemy.getPosition().getYPos() << player.getPosition().getYPos();
>>>>>>> 9888f909918efdf6746b10278506c202d052e349
            return oldPosition;
        }
        else if (newPosition.getXPos() < 0 || newPosition.getXPos() > 11 || newPosition.getYPos() < 0 || newPosition.getYPos() > 9)
        {
<<<<<<< HEAD
=======
            // cout << enemy.getPosition().getXPos() << player.getPosition().getXPos() << enemy.getPosition().getYPos() << player.getPosition().getYPos();
>>>>>>> 9888f909918efdf6746b10278506c202d052e349
            return oldPosition;
        }
        else
        {
            for (int i = 0; i < listEngimonLiar.size(); i++)
            {
                if (isPositionSama(newPosition, listEngimonLiar[i]))
                {
                    sama = true;
                    break;
                }
                if (PositionEnemyWrong(newPosition, enemy.getId()))
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

    bool isPositionSama(Position enemy1, EngimonEnemy enemy2)
    {
        if (enemy1.getXPos() == enemy2.getPosition().getXPos() && enemy1.getYPos() == enemy2.getPosition().getYPos())
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool PositionEnemyWrong(Position enemy, int id)
    {
        if (id > 2900) // artinya enemy memiliki tipe water dan ice
        {
            if (enemy.getXPos() < 6 || enemy.getYPos() > 4) // Jika berada di grassland
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else // artinya enemy memiliki tipe electric, fire dan ground
        {
            if (enemy.getXPos() > 5 && enemy.getYPos() < 6) // Jika berada di water
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }

    Element addElement(int tipeEngimon)
    {
        if (tipeEngimon == 0)
        {
            return Element::Fire;
        }
        else if (tipeEngimon == 1)
        {
            return Element::Water;
        }
        else if (tipeEngimon == 2)
        {
            return Element::Electric;
        }
        else if (tipeEngimon == 3)
        {
            return Element::Ground;
        }
        else
        {
            return Element::Ice;
        }
    }

    int EnemyNear(Player player, vector<EngimonEnemy> listEngimonLiar)
    {
        for (int i = 0; i < listEngimonLiar.size(); i++)
        {
            //
            if (player.getPosition().getXPos() == listEngimonLiar[i].getPosition().getXPos())
            {
                if ((player.getPosition().getYPos() + 1 == listEngimonLiar[i].getPosition().getYPos()) || (player.getPosition().getYPos() - 1 == listEngimonLiar[i].getPosition().getYPos()))
                {
                    return i;
                }
            }
            else if (player.getPosition().getYPos() == listEngimonLiar[i].getPosition().getYPos())
            {
                if ((player.getPosition().getXPos() + 1 == listEngimonLiar[i].getPosition().getXPos()) || (player.getPosition().getXPos() - 1 == listEngimonLiar[i].getPosition().getXPos()))
                {
                    return i;
                }
            }
        }
        return 999;
    }
};

#endif