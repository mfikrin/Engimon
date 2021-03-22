#ifndef PLAYER_HPP
#define PLAYER_HPP

#define INIT_PLAYER_X 1
#define INIT_PLAYER_Y 0
#define INIT_ACTIVEMON_X 0
#define INIT_ACTIVEMON_Y 0

#include <string.h>

#include "Position.hpp"
#include "Inventory.hpp"
#include "Engimon.hpp"
#include "SkillItem.hpp"
// #include "Map.hpp"
#include "EngimonUser.hpp"


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
        Player(string name_){
            name = name_;
            position = Position(INIT_PLAYER_X, INIT_PLAYER_Y);
            vector<Element> apakek;
            apakek.push_back(Element::Fire);
            activeEngimon = EngimonUser(Position(0,0),"a","a",123,apakek);
            //activeEngimon = EngimonUser(Position(0,0),active.getName(),active.getSpecies(),active.getId(),active.getElements());
            // inventory = Inventory();
            //activeEngimon = EngimonUser(Position(INIT_ACTIVEMON_X,INIT_ACTIVEMON_Y),active.getName(),active.getSpecies(),active.getId(),active.getElements());
            //activeEngimon = EngimonUser(Position(0,0),active);
        }

        void getActiveEngimon(Engimon& engimon){
            activeEngimon = EngimonUser(Position(0,0),engimon.getName(),engimon.getSpecies(),engimon.getId(),engimon.getElements());
        }

};

#endif // PLAYER_HPP