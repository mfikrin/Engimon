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
// #include "EngimonUser.hpp"


class Player{
    protected:
        string name;
        Position position;
        // Inventory inventory; 
        // EngimonUser activeEngimon; 
    public:
        


        // OTHER METHOD
        // void Move(const Map& m, char direction); 
        void showAllEngimons();
        void showEngimonData(const Engimon& e); 
        void handleShowEngimonData();  
        void changeActiveEngimon();
        void showSkillItems();
        void useSkillItem(SkillItem& si, Engimon& e);
        Engimon breed(const Engimon& a, const Engimon& b);
        // void battle(const Map& m);
        void interact();
        void switchActiveEngimon();


        // CTOR
        Player(string name_){
            name = name_;
            position = Position(INIT_PLAYER_X, INIT_PLAYER_Y);
            // inventory = Inventory();
            // activeEngimon = EngimonUser();
        }

};

#endif // PLAYER_HPP