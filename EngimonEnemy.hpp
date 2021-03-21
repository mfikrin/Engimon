#ifndef _EngimonEnemy_hpp_
#define _EngimonEnemy_hpp_

#include "Engimon.hpp"
#include "Position.hpp"

class EngimonEnemy : public Engimon {
    private:
        Position engimonEnemyPosition;
    public:
        EngimonEnemy (const Position& p, string n, string sp, int i, const vector<Element>& el) 
        : Engimon (n,sp,i,el) {
            this->engimonEnemyPosition = p;
        }

        void moveEngimonEnemy(const Position& p){
            this->engimonEnemyPosition = p;
        }
};

#endif // _EngimonEnemy_hpp_