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


class Player{
    protected:
        string name;
        Position position;
        Inventory<Engimon, MAX_ENGIMON_INV> inv_engimon;
        Inventory<SkillItem, MAX_SKILL_ITEM_INV> inv_skill;
        EngimonUser activeEngimon; 
    public:
        


        // OTHER METHOD
        void Move(char direction){
            activeEngimon.moveEngimonUser(position);
            switch(direction){
                case 'w': position.up(); break;
                case 'a': position.left(); break;
                case 's': position.down(); break;
                case 'd': position.right(); break;
            }
        }

        Position getPosition(){
            return position;
        }

        Position getActiveEngimonPosition(){
            return activeEngimon.getPosition();
        }
        //void showAllEngimons();
        //void showEngimonData(const Engimon& e); 
        //void handleShowEngimonData();  
        //void changeActiveEngimon();
        //void showSkillItems();
        //void useSkillItem(SkillItem& si, Engimon& e);
        //Engimon breed(const Engimon& a, const Engimon& b);
        // void battle(const Map& m);
        //void interact();
        //void switchActiveEngimon();


        // CTOR
        Player(string name_ , Engimon& active) : activeEngimon(Position(INIT_ACTIVEMON_X,INIT_ACTIVEMON_Y),active.getName(),active.getSpecies(),active.getId(),active.getElements()){
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

        // void getActiveEngimon(Engimon& engimon){
        //     activeEngimon = EngimonUser(Position(0,0),engimon.getName(),engimon.getSpecies(),engimon.getId(),engimon.getElements());
        // }

        

        void breeding(Engimon parent1, Engimon parent2){
            if (this->inv_engimon.get_nItem() == MAX_ENGIMON_INV) /* Inventory penuh */
            {
                cout << "Inventory penuh!" << endl;
            } else {
                bool parent1Available = inv_engimon.check_item_availability(parent1.getId());
                bool parent2Available = inv_engimon.check_item_availability(parent2.getId());
                if (!parent1Available) // parent1 ga ada di inventory
                {
                    if (parent2Available) // parent2 ada di inventory
                    {
                        cout << "Parent 1 tidak ada di inventory" << endl;
                    } else {// parent2 ga ada di inventory juga
                        cout << "Parent 1 dan Parent 2 tidak ada di inventory" << endl;
                    }
                } else if (!parent2Available) {// parent1 ada di inventory tapi parent2 ga ada
                    cout << "Parent 2 tidak ada di inventory" << endl;
                } else {// parent1 dan parent2 ada di inventory 
                    if (parent1.getLevel() < 30 || parent2.getLevel() < 30) // Salah satu parent berlevel kurang dari 30
                    {
                        if (parent1.getLevel() < 30)
                        {
                            if (parent2.getLevel() >= 30)
                            {
                                cout << "Level Parent 1 kurang dari 30!" << endl;
                            } else {
                                cout << "Level Parent 1 dan Parent 2 kurang dari 30!" << endl;
                            }
                            
                        } else {
                            cout << "Level Parent 2 kurang dari 30!" << endl;
                        }
                        
                    } else {// Level kedua parent >= 30
                        int childID;
                        vector<Element> parentElement;
                        vector<Element> parent1Element = parent1.getElements();
                        vector<Element> parent2Element = parent2.getElements();
                        vector<Element> childElement;
                        string childName;
                        string childSpecies;
                        cout << "Masukkan nama anak!" << endl;
                        cin >> childName;

                        // MENGOLEKSI ELEMENT PARENT1 KE DALAM ELEMENTPARENT
                        for (int i = 0; i < parent1Element.size(); i++)
                        {
                            parentElement.push_back(parent1Element[i]);
                        }

                        // MENGOLEKSI ELEMENT PARENT2 KE DALAM ELEMENTPARENT
                        for (int i = 0; i < parent2Element.size(); i++)
                        {
                            // Mengecek apakah element dari elementParent2 sudah ada di elementParent
                            bool present = false;
                            for (int j = 0; j < parentElement.size(); j++)
                            {
                                if (parent2Element[i] == parentElement[j])
                                {
                                    present = true;
                                }
                                
                            }
                            
                            // Mengoleksi elementParent2 ke dalam elementParent
                            if (!present)
                            {
                                parentElement.push_back(parent2Element[i]);
                            }
                            
                        }

                        // MEMBANDINGKAN ELEMENT KEDUA PARENT
                        if (parent1Element.size() == parent2Element.size())
                        {
                            bool parentSimilarity = true;
                            int i = 0;
                            while (i < parent1Element.size() && parentSimilarity)
                            {
                                if (parent1Element[i] != parent2Element[i])
                                {
                                    parentSimilarity = false;
                                }
                                i++;
                            }
                            
                            if (parentSimilarity) // Kedua parent ber-element sama
                            {
                                int speciesRandomizer = rand() % 2;
                                childElement = parent1Element;
                                if (speciesRandomizer){
                                    childSpecies = parent1.getSpecies();
                                } else {
                                    childSpecies = parent2.getSpecies();
                                }
                            } else {// Elemen kedua parent berbeda
                                if (parent1Element.size() == 1 && parent2Element.size() == 1)
                                {
                                    if (get_advantage(parent1Element[0], parent2Element[0]) > get_advantage(parent2Element[0], parent1Element[0]))
                                    {
                                        childSpecies = parent1.getSpecies();
                                        childID = parent1.getId();
                                        childElement = parent1.getElements();

                                    } else if (get_advantage(parent1Element[0], parent2Element[0]) < get_advantage(parent2Element[0], parent1Element[0])){
                                        childSpecies = parent2.getSpecies();
                                        childID = parent2.getId();
                                        childElement = parent2.getElements();
                                    } else { // Element advantage sama
                                        
                                        int mutationRandomizer = rand() % 10000;
                                        childSpecies = parent1.getSpecies() + to_string(mutationRandomizer);
                                        while (childSpecies == parent1.getSpecies() || childSpecies == parent2.getSpecies())
                                        {
                                            mutationRandomizer = rand() % 10000;
                                            childSpecies = parent1.getSpecies() + to_string(mutationRandomizer);
                                            
                                        }
                                        childElement = parentElement;
                                        childID = mutationRandomizer;
                                        
                                    }
                                    
                                } else {// Element parent lebih dari 1
                                    int duaElement = rand() % 2;
                                    if (duaElement)
                                    {
                                        int element1Index = rand() % parentElement.size();
                                        int element2Index = rand() % parentElement.size();
                                        while (element2Index == element1Index)
                                        {
                                            element2Index = rand() % parentElement.size();
                                        }
                                        
                                        childElement.push_back(parentElement[element1Index]);
                                        childElement.push_back(parentElement[element2Index]);
                                    }
                                    else
                                    {
                                        int elementIndex = rand() % parentElement.size();
                                        childElement.push_back(parentElement[elementIndex]);
                                    }
                                }
                                
                            }
                            
                        } else {// Elemen kedua parent berbeda
                            int mutationRandomizer = rand() % 10000;
                                        childSpecies = parent1.getSpecies() + to_string(mutationRandomizer);
                                        while (childSpecies == parent1.getSpecies() || childSpecies == parent2.getSpecies())
                                        {
                                            mutationRandomizer = rand() % 10000;
                                            childSpecies = parent1.getSpecies() + to_string(mutationRandomizer);
                                        }
                                        childElement = parentElement;
                        }
                        
                    Engimon child(childName, childSpecies, childID, childElement);
                    
                    parent1.setLevel(parent1.getLevel() - 30);
                    parent2.setLevel(parent2.getLevel() - 30);
                    }
                    

                }
                
        


            }
            
        }

        float get_advantage(Element e1, Element e2){
            if (e1 == Element::Fire){
                switch (e2)
                {
                case Element::Fire: return 1; // break;
                case Element::Water: return 0; // break;
                case Element::Electric: return 1; // break;
                case Element::Ground: return 0.5; // break;
                case Element::Ice: return 2; // break;
                default: return 0; // break; // Untuk No element (?) 
                }
            }
            else if (e1 == Element::Water){
                switch (e2)
                {
                case Element::Fire: return 2;   
                case Element::Water: return 1;
                case Element::Electric: return 0;
                case Element::Ground: return 1;
                case Element::Ice: return 1;
                default: return 0; // break; // Untuk No element (?)
                }
            }
            else if (e1 == Element::Electric){
                switch (e2)
                {
                case Element::Fire: return 1; 
                case Element::Water: return 2;  
                case Element::Electric: return 1; 
                case Element::Ground: return 0;
                case Element::Ice: return 1.5;
                default: return 0;
                }
            }
            else if (e1 == Element::Ground){
                switch (e2)
                {
                case Element::Fire: return 1.5;
                case Element::Water: return 1;
                case Element::Electric: return 2;
                case Element::Ground:  return 1;
                case Element::Ice: return 0;
                default: return 0;
                
                 \
                }
            }
            else if (e1 == Element::Ice){
                switch (e2)
                {
                case Element::Fire: return 0;
                case Element::Water: return 1;
                case Element::Electric: return 0.5;
                case Element::Ground: return 2;
                case Element::Ice: return 1;
                default: return 0;
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
};

#endif // PLAYER_HPP