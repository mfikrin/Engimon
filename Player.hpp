#ifndef PLAYER_HPP
#define PLAYER_HPP

#define INIT_PLAYER_X 1
#define INIT_PLAYER_Y 0
#define INIT_ACTIVEMON_X 0
#define INIT_ACTIVEMON_Y 0

#include <string.h>
#include <stdlib.h>

#include "Position.hpp"
#include "Inventory.hpp"
#include "Engimon.hpp"
#include "SkillItem.hpp"
// #include "Map.hpp"
#include "EngimonUser.hpp"
#include "Element.hpp"


class Player{
    protected:
        string name;
        Position position;
        // Inventory inventory; 
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

};

#endif // PLAYER_HPP