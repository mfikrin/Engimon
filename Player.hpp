#ifndef PLAYER_HPP
#define PLAYER_HPP

#define INIT_PLAYER_X 1
#define INIT_PLAYER_Y 0
#define INIT_ACTIVEMON_X 0
#define INIT_ACTIVEMON_Y 0

#include <string.h>
#include <stdlib.h>
#include <algorithm>

#include "Position.hpp"
#include "inventory/Inventory.hpp"
#include "Engimon.hpp"
#include "SkillItem.hpp"
// #include "Map.hpp"
#include "EngimonUser.hpp"
#include "Element.hpp"
#include "BookOfLore.hpp"

// #include "MAP_SIZE.hpp"

class Player
{
protected:
    string name;
    Position position;
    Inventory<EngimonUser, MAX_ENGIMON_INV> inv_engimon;
    Inventory<SkillItem, MAX_SKILL_ITEM_INV> inv_skill;
    EngimonUser activeEngimon;

public:
    // OTHER METHOD
    void Move(char direction)
    {
        activeEngimon.moveEngimonUser(position);
        if ((direction == 'w' && position.getXPos() == 0) || (direction == 'a' && position.getYPos() == 0) || (direction == 's' && position.getXPos() == MAP_HEIGHT - 1) || (direction == 'd' && position.getXPos() == MAP_WIDTH - 1))
        {
            throw "KELUAR MAP CUY!!";
        }
        else
        {
            switch (direction)
            {
            case 'w':
                position.up();
                break;
            case 'a':
                position.left();
                break;
            case 's':
                position.down();
                break;
            case 'd':
                position.right();
                break;
            }
        }
    }

    Position getPosition()
    {
        return position;
    }

    Position getActiveEngimonPosition()
    {
        return activeEngimon.getPosition();
    }
    void showAllEngimons()
    {
        inv_engimon.show_bag();
    }
    void showEngimonData(const EngimonUser &e)
    {
        cout << "-==Data Engimon==-\n";
        cout << "Nama: " << e.getName() << endl;
        cout << "Spesies: " << e.getSpecies() << endl;
        cout << "Element(s): ";
        for (int i = 0; i < e.getElements().size(); i++)
        {
            cout << e.getElements()[i] << " ";
        }
        cout << endl;
        cout << "Parents: <";
        cout << "(" << e.getParentNames()[0] << e.getParentSpecieses[0] << "),";
        cout << "(" << e.getParentNames()[1] << e.getParentSpecieses[1] << ")>" << endl;
        cout << "Level: " << e.getLevel() << endl;
        cout << "Exp: " << e.getExp() << endl;
        cout << "Cumulative Exp: " << e.getCExp() << endl;
    }
    void handleShowEngimonData()
    {
        inv_engimon.show_bag();
        cout << "\ta\t[" << activeEngimon.getName() << "]" << endl
             << " >> ";
        string input;
        cin >> input;
        if (input == "a" || input == "A")
        {
            showEngimonData(activeEngimon);
        }
        else
        {
            // Menunggu Inventory. getEngimon -> showEngimonData
        }
    }
    void changeActiveEngimon()
    {
        // menunggu Inventory
    }
    //void showSkillItems(); // Nunggu Inventory
    void useSkillItem(SkillItem &si, Engimon &e)
    {
        si.learn(&e);

        // UDAH BELUM YAK?????
    }
    //Engimon breed(const Engimon& a, const Engimon& b);
    // void battle(const Map& m);
    //void interact();
    //void switchActiveEngimon();

    // CTOR
    Player(string name_, Engimon &active) : activeEngimon(Position(INIT_ACTIVEMON_X, INIT_ACTIVEMON_Y), active.getName(), active.getSpecies(), active.getId(), active.getElements())
    {
        name = name_;
        position = Position(INIT_PLAYER_X, INIT_PLAYER_Y);
        //vector<Element> apakek;
        //apakek.push_back(Element::Fire);
        //activeEngimon = EngimonUser(Position(0,0),"a","a",123,apakek);
        //activeEngimon = EngimonUser(Position(0,0),active.getName(),active.getSpecies(),active.getId(),active.getElements());
        // inventory = Inventory();
        //activeEngimon = EngimonUser(Position(INIT_ACTIVEMON_X,INIT_ACTIVEMON_Y),active.getName(),active.getSpecies(),active.getId(),active.getElements());
        //activeEngimon = EngimonUser(Position(0,0),active);
    }
    else
    {
        if (true /* parent ga ada di inventory */)
        {
            cout << "Parent tidak ada di inventory" << endl;
        }
        else
        {
            vector<Element> elementParent;
            vector<Element> elementParent1 = parent1.getElements();
            vector<Element> elementParent2 = parent2.getElements();

            // Mengoleksi element parent 1 ke dalam elementParent
            for (int i = 0; i < elementParent1.size(); i++)
            {
                elementParent.push_back(elementParent1[i]);
            }

            // Mengoleksi element parent 2 ke dalam elementParent
            for (int i = 0; i < elementParent2.size(); i++)
            {
                // Mengecek apakah element dari elementParent2 sudah ada di elementParent
                bool present = false;
                for (int j = 0; j < elementParent.size(); j++)
                {
                    if (elementParent2[i] == elementParent[j])
                    {
                        present = true;
                    }
                }

                // Mengoleksi elementParent2 ke dalam elementParent
                if (!present)
                {
                    elementParent.push_back(elementParent2[i]);
                }
            }

            if (elementParent.size() > 2)
            {
                int duaElement = rand() % 2;
                if (duaElement)
                {
                    int element1Index = rand() % elementParent.size();
                    int element2Index = rand() % elementParent.size();
                }
                else
                {
                    int elementIndex = rand() % elementParent.size();
                }
            }
        }
    }
}

float
get_advantage(Element e1, Element e2)
{
    if (e1 == Element::Fire)
    {
        switch (e2)
        {
        case Element::Fire:
            return 1; // break;
        case Element::Water:
            return 0; // break;
        case Element::Electric:
            return 1; // break;
        case Element::Ground:
            return 0.5; // break;
        case Element::Ice:
            return 2; // break;
        default:
            return 0; // break; // Untuk No element (?)
        }
    }
    else if (e1 == Element::Water)
    {
        switch (e2)
        {
        case Element::Fire:
            return 2;
        case Element::Water:
            return 1;
        case Element::Electric:
            return 0;
        case Element::Ground:
            return 1;
        case Element::Ice:
            return 1;
        default:
            return 0; // break; // Untuk No element (?)
        }
    }
    else if (e1 == Element::Electric)
    {
        switch (e2)
        {
        case Element::Fire:
            return 1;
        case Element::Water:
            return 2;
        case Element::Electric:
            return 1;
        case Element::Ground:
            return 0;
        case Element::Ice:
            return 1.5;
        default:
            return 0;
        }
    }
    else if (e1 == Element::Ground)
    {
        switch (e2)
        {
        case Element::Fire:
            return 1.5;
        case Element::Water:
            return 1;
        case Element::Electric:
            return 2;
        case Element::Ground:
            return 1;
        case Element::Ice:
            return 0;
        default:
            return 0;
        }
    }
    else if (e1 == Element::Ice)
    {
        switch (e2)
        {
        case Element::Fire:
            return 0;
        case Element::Water:
            return 1;
        case Element::Electric:
            return 0.5;
        case Element::Ground:
            return 2;
        case Element::Ice:
            return 1;
        default:
            return 0;
        }
    }

    // Untuk No element
    // else if (e1 == Element::NoElement){
    //     switch (e2)
    //     {
    //     case Element::Fire: return 0;
    //     case Element::Water: return 0;
    //     case Element::Electric: return 0;
    //     case Element::Ground: return 0;
    //     case Element::Ice: return 0;
    //     default: return 0;
    //     }
    // }
}

void battle(EngimonEnemy enemy)
{
    vector<Element> element_active = activeEngimon.getElements();
    vector<Element> element_enemy = enemy.getElements();

    vector<float> temp_adv_active;
    vector<float> temp_adv_enemy;

    for (int i = 0; i < element_active.size(); i++)
    {
        for (int j = 0; j < element_enemy.size(); j++)
        {
            temp_adv_active.push_back(get_advantage(element_active[i], element_enemy[j]));
            temp_adv_enemy.push_back(get_advantage(element_enemy[j], element_active[i]));
        }
    }

    float adv_user = *max_element(temp_adv_active.begin(), temp_adv_active.end());
    float adv_enemy = *max_element(temp_adv_enemy.begin(), temp_adv_enemy.end());

    vector<Skill> skill_user = activeEngimon.getSkills();

    float sum_skill_user = 0;

    for (int i = 0; i < skill_user.size(); i++)
    {
        sum_skill_user += (skill_user[i].getBasePower() * skill_user[i].getMasteryLevel());
    }

    vector<Skill> skill_enemy = enemy.getSkills();

    float sum_skill_enemy = 0;

    for (int i = 0; i < skill_enemy.size(); i++)
    {
        sum_skill_enemy += (skill_enemy[i].getBasePower() * skill_enemy[i].getMasteryLevel());
    }

    float power_user = activeEngimon.getLevel() * adv_user * sum_skill_user;
    float power_enemy = enemy.getLevel() * adv_enemy * sum_skill_enemy;

    cout << "POWER KEDUA ENGIMON" << endl;
    cout << "Power Engimon User : " << power_user << endl;
    cout << "Power Engimon Enemy : " << power_enemy << endl;

    if (power_user > power_enemy)
    {
        try
        {
            inv_engimon.add_item(enemy);
        }
        catch (const Engimon &e)
        {
            cout << "Inventory Engimon penuh" << endl;
        }

        int new_exp = activeEngimon.getExp() + (abs(activeEngimon.getLevel() - enemy.getLevel())) * 20; // rumus exp (bisa diubah lg rumusnya)

        activeEngimon.setExp(new_exp);

        // get random skill item (sesuai elemen musuh)

        BookOfLore ensiklopedia;
        vector<vector<Skill>> ensiklopediaSkill = ensiklopedia.allSkill();

        vector<vector<Skill>> Skill_enemy;

        for (int i = 0; i < element_enemy.size(); i++)
        {
            int idx = ensiklopedia.get_idx_skill(element_enemy[i]);
            for (int j = 0; i < ensiklopediaSkill.size(); j++)
            {
                if (idx == j)
                {
                    Skill_enemy.push_back(ensiklopediaSkill[j]);
                }
            }
        }

        int idxElement = rand() % Skill_enemy.size();
        int idxSkill = rand() % Skill_enemy[idxElement].size();

        Skill get_skill = Skill_enemy[idxElement][idxSkill];

        Skill skill(get_skill.getSkillId(), get_skill.getMasteryLevel(), get_skill.getBasePower(), get_skill.getSkillName(), get_skill.getElement());

        SkillItem skill_item(skill);

        try
        {
            inv_skill.add_item(skill_item);
        }
        catch (const SkillItem &e)
        {
            cout << "Inventory Skill Item penuh" << endl;
        }
    }

    else
    {
        // engimon mati
        // activeEngimon = select(); // select ENgimon dr inventory
    }
}
}
;

#endif // PLAYER_HPP