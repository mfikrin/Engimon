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
            if (false/* Inventory penuh */)
            {
                cout << "Inventory penuh!" << endl;
            } else {
                if (true/* parent ga ada di inventory */)
                {
                    cout << "Parent tidak ada di inventory" << endl;
                } else {
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
                        } else {
                            int elementIndex = rand() % elementParent.size();
                        }
                    
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
        

        void battle (EngimonEnemy enemy){
            vector<Element> element_active = activeEngimon.getElements();
            vector<Element> element_enemy = enemy.getElements();

            vector<float> temp_adv_active;
            vector<float> temp_adv_enemy;

            for (int i = 0; i < element_active.size(); i++)
            {
                for (int j = 0; j < element_enemy.size(); j++)
                {
                    temp_adv_active.push_back(get_advantage(element_active[i],element_enemy[j]));
                    temp_adv_enemy.push_back(get_advantage(element_enemy[j], element_active[i]));
                }
            }

            float adv_user = *max_element(temp_adv_active.begin(),temp_adv_active.end());
            float adv_enemy = *max_element(temp_adv_enemy.begin(),temp_adv_enemy.end());

            if (adv_user > adv_enemy)
            {
                try
                {
                    inv_engimon.add_item(enemy);
                }
                catch(const Engimon& e)
                {
                    cout << "Inventory Engimon penuh" << endl;
                }

                int new_exp = activeEngimon.getExp() + (abs(activeEngimon.getLevel() - enemy.getLevel()))*20; // rumus exp (bisa diubah lg rumusnya)

                activeEngimon.setExp(new_exp);

                // get random skill item (sesuai elemen musuh)

                BookOfLore ensiklopedia;
                vector<vector<Skill>> ensiklopediaSkill = ensiklopedia.allSkill();

                vector<vector<Skill>> Skill_enemy;

                for (int  i = 0; i < element_enemy.size(); i++)
                {
                    int idx = ensiklopedia.get_idx_skill(element_enemy[i]);
                    for (int j = 0; i < ensiklopediaSkill.size(); j++)
                    {
                        if (idx == j){
                            Skill_enemy.push_back(ensiklopediaSkill[j]);
                        }
                    }
                }

                int idxElement = rand() % Skill_enemy.size();
                int idxSkill = rand() % Skill_enemy[idxElement].size();

                Skill get_skill = Skill_enemy[idxElement][idxSkill];

                Skill skill(get_skill.getSkillId(),get_skill.getMasteryLevel(),get_skill.getBasePower(), get_skill.getSkillName(),get_skill.getElement());

                SkillItem skill_item(skill);

                try
                {
                    inv_skill.add_item(skill_item);
                }
                catch (const SkillItem& e)
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