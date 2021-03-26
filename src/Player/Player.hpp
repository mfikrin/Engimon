#ifndef PLAYER_HPP
#define PLAYER_HPP

#define INIT_PLAYER_X 1
#define INIT_PLAYER_Y 0
#define INIT_ACTIVEMON_X 0
#define INIT_ACTIVEMON_Y 0

#define MAP_HEIGHT 10 // ???
#define MAP_WIDTH 12  /// ???

#include <string.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>

#include "../Position/Position.hpp"
#include "../Inventory/Inventory.hpp"
#include "../Engimon/Engimon.hpp"
#include "../Skill/SkillItem.hpp"
//#include "../MainProgram/Map.hpp"
#include "../Engimon/EngimonUser.hpp"
#include "../Element/Element.hpp"
#include "../MainProgram/BookOfLore.hpp"
#include "../Exception/Exception.hpp"

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
        if ((direction == 'w' && position.getYPos() == 0) || (direction == 'a' && position.getXPos() == 0) || (direction == 's' && position.getYPos() == MAP_HEIGHT - 1) || (direction == 'd' && position.getXPos() == MAP_WIDTH - 1))
        {
            throw OutOfBoundException();
        }
        else
        {

            switch (direction)
            {
            case 'w':
                activeEngimon.moveEngimonUser(position);
                position.up();
                break;
            case 'a':
                activeEngimon.moveEngimonUser(position);
                position.left();
                break;
            case 's':
                activeEngimon.moveEngimonUser(position);
                position.down();
                break;
            case 'd':
                activeEngimon.moveEngimonUser(position);
                position.right();
                break;
            }
        }
    }
    // BATAS NGEDIT
    Position getPosition()
    {
        return position;
    }

    EngimonUser getActiveEngimon()
    {
        return activeEngimon;
    }

    void print_active_engimon(){
        cout << "Nama: " << this->activeEngimon.getName() << endl << endl;
    }

    Position getActiveEngimonPosition()
    {
        return activeEngimon.getPosition();
    }
    void showAllEngimons()
    {
        inv_engimon.show_bag();
    }

    void command(string com)
    {
        if (com == "w" || com == "a" || com == "s" || com == "d")
        {
            Move(com[0]);
        }
        else if (com == "i")
        {
            cout << "1. Engimon Inventory" << endl;
            cout << "2. Skill Item Inventory" << endl;
            string invent;
            do
            {
                cin >> invent;
                if (invent != "1" && invent != "2")
                {
                    cout << "Type 1 or 2!" << endl;
                }
                else if (invent == "1")
                {
                    inv_engimon.show_bag();
                }
                else
                {
                    inv_skill.show_bag();
                }
            } while (invent != "1" && invent != "2");
        }else if(com == "show" || com == "sae"){
            print_active_engimon();
        }else if(com == "talk" || com == "int"){
            interact();
        }else if(com == "q" || com == "quit" || com == "exit"){
            cout << "GoodBye!" << endl;
            exit(0);
        }
    }

    void changeActiveEngimon()
    {
        // menunggu Inventory
        if (inv_engimon.get_nItem() > 0)
        {
            inv_engimon.show_bag();
            cout << "Input id : ";
            int id;
            cin >> id;
            activeEngimon = inv_engimon.select_item(id);
        }
        else
        {
            cout << "GAME OVER" << endl;
            exit(1);
        }
    }
    void useSkillItem(SkillItem &si, Engimon &e)
    {
        si.learn(&e);

        // UDAH BELUM YAK?????
    }
    void interact(){
        cout << "Halo! \nAku " << this->activeEngimon.getName() << endl;
        cout << "Engimon tipe ";
        int num_skills = this->activeEngimon.getElements().size(); 
        for (int i=0; i<num_skills; i++){
            string s = "";
            switch (this->activeEngimon.getElements()[i])
            {
            case Element::NoElement:
                s = "None";
                break;
            
            case Element::Fire:
                s = "Fire";
                break;
            
            case Element::Water:
                s = "Water";
                break;
            
            case Element::Electric:
                s = "Electric";
                break;
            
            case Element::Ground:
                s = "Ground";
                break;
            
            case Element::Ice:
                s = "Ice";
                break;
            
            default:
                s="";
                break;
            }
            cout << s << "; ";
        }
        cout << "level " << this->activeEngimon.getLevel() << endl;
        cout << "EXP : " << this->activeEngimon.getExp() << "/" << MAX_EXP << endl << endl;

    }
    //void switchActiveEngimon();

    // CTOR
    // Player(string name_, Engimon &active) : activeEngimon(Position(INIT_ACTIVEMON_X, INIT_ACTIVEMON_Y), active.getName(), active.getSpecies(), active.getId(), active.getElements())
    // {
    //     name = name_;
    //     position = Position(INIT_PLAYER_X, INIT_PLAYER_Y);
    // }

    Player(string name_, Engimon &active) : activeEngimon(active)
    {
        name = name_;
        position = Position(INIT_PLAYER_X, INIT_PLAYER_Y);
        activeEngimon.setPosition(Position(INIT_ACTIVEMON_X,INIT_ACTIVEMON_Y));
    }

    Player(vector<Element> a) : activeEngimon(Position(0,0),"a","a",0,a){
        name = "";
        position = Position(1,0);
    }

    Player(const Player& other){
        this->name = other.name;
        this->position = other.position;
        this->inv_engimon = other.inv_engimon;
        this->inv_skill = other.inv_skill;
        this->activeEngimon = other.activeEngimon;
    }

    void operator=(const Player& other){
        this->name = other.name;
        this->position = other.position;
        this->inv_engimon = other.inv_engimon;
        this->inv_skill = other.inv_skill;
        this->activeEngimon = other.activeEngimon;
    }

    // Inventory<EngimonUser, MAX_ENGIMON_INV> get_inv_engimon() {
    //     return this->inv_engimon;
    // }

    void Add_inv_engimon(EngimonUser& e1){
        this->inv_engimon.add_item(e1);
    }

    void Add_inv_skill(SkillItem &s1)
    {
        this->inv_skill.add_item(s1);
    }
};

#endif // PLAYER_HPP