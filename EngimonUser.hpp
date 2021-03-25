#ifndef _EngimonUser_hpp_
#define _EngimonUser_hpp_

#include "Engimon.hpp"
#include "Position.hpp"

class EngimonUser : public Engimon
{
private:
    Position engimonUserPosition;

public:
    EngimonUser(const Position &p, string n, string sp, int i, const vector<Element> &el)
        : Engimon(n, sp, i, el)
    {
        this->engimonUserPosition = p;
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