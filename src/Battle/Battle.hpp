#ifndef BATTLE_HPP
#define BATTLE_HPP
#include "../Player/Player.hpp"
#include "../Engimon/Engimon.hpp"
#include "../Engimon/EngimonEnemy.hpp"
#include "../Element/Element.hpp"
#include "../BookOfLore/BookOfLore.hpp"
#include <vector>

class Battle
{
public:
    static float get_advantage(Element e1, Element e2)
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
        else
        {
            return 0;
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

    static int battleEngimon(Player player, EngimonEnemy enemy)
    {
        vector<Element> element_active = player.getActiveEngimon().getElements(); // semua elemen dari engimon aktif
        vector<Element> element_enemy = enemy.getElements();                      // semua elemen dari engimon element

        vector<float> temp_adv_active;
        vector<float> temp_adv_enemy;
        // LOOPING SEMUA KEMUNGKINAN GET ADVANTAGE
        for (int i = 0; i < element_active.size(); i++)
        {
            for (int j = 0; j < element_enemy.size(); j++)
            {
                temp_adv_active.push_back(Battle::get_advantage(element_active[i], element_enemy[j]));
                temp_adv_enemy.push_back(Battle::get_advantage(element_enemy[j], element_active[i]));
            }
        }
        // CARI MAKS DARI HASIL GET ADVANTAGE
        float adv_user = *max_element(temp_adv_active.begin(), temp_adv_active.end());
        float adv_enemy = *max_element(temp_adv_enemy.begin(), temp_adv_enemy.end());

        // cout << adv_enemy << " " << adv_user << "ACTIVE " << player.getActiveEngimon().getLevel() << endl;

        // PENJUMLAH SKIL USERR
        vector<Skill> skill_user = player.getActiveEngimon().getSkills();
        //cout << "jumlah" << skill_user.size();
        float sum_skill_user = 0;
        for (int i = 0; i < skill_user.size(); i++)
        {
            //cout << "skillUser " << skill_user[i].getBasePower() << skill_user[i].getMasteryLevel() << endl;
            sum_skill_user += (skill_user[i].getPower() * skill_user[i].getMasteryLevel());
        }

        // PENJUMLAH SKIL ENEMY
        vector<Skill> skill_enemy = enemy.getSkills();
        float sum_skill_enemy = 0;
        for (int i = 0; i < skill_enemy.size(); i++)
        {
            sum_skill_enemy += (skill_enemy[i].getPower() * skill_enemy[i].getMasteryLevel());
        }

        // PRINT NILAI POWER
        float power_user = player.getActiveEngimon().getLevel() * adv_user + sum_skill_user;
        float power_enemy = enemy.getLevel() * adv_enemy + sum_skill_enemy;
        cout << "POWER KEDUA ENGIMON" << endl;
        cout << "Power Engimon User : " << power_user << endl;
        cout << "Power Engimon Enemy : " << power_enemy << endl;

        // JIKA USER MENANG
        if (power_user > power_enemy)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    
    }
};

#endif