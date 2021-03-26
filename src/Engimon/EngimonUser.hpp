#ifndef _EngimonUser_hpp_
#define _EngimonUser_hpp_

#include "Engimon.hpp"
#include "../Position/Position.hpp"

vector<Element> listKosong;

class EngimonUser : public Engimon
{
private:
    Position engimonUserPosition;

public:
    EngimonUser() : Engimon("","",0,listKosong){
        this->engimonUserPosition = Position(0,0);
    }
    EngimonUser(const Position &p, string n, string sp, int i, const vector<Element> &el): Engimon(n, sp, i, el)
    {
        this->engimonUserPosition = p;
    }
    EngimonUser(const Engimon& otherEngimon) : Engimon(otherEngimon){
        this->engimonUserPosition = Position(0,0);
    }

    void operator=(const EngimonUser(& other)){
        this->name = other.name;
        this->species = other.species;
        this->id = other.id;
        this->elements = other.elements;
        this->engimonUserPosition = other.engimonUserPosition;
        this->skills = other.skills;
    }

    void moveEngimonUser(const Position &p)
    {
        this->engimonUserPosition = p;
    }

    Position getPosition()
    {
        return engimonUserPosition;
    }
    void setPosition(Position p)
    {
        engimonUserPosition = p;
    }
};

#endif // _EngimonUser_hpp_