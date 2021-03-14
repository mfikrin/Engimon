#ifndef SKILL_H
#define SKILL_H

class Skill {
    private :
        int masteryLevel;
        int numerikBasePower;

    public :
        Skill() : masteryLevel(0), numerikBasePower(0){}
        Skill(int level, int basePWR) : masteryLevel(level), numerikBasePower(basePWR) {}

        void setMasteryLevel(int level){this->masteryLevel = level;}
        void setBasePower(int pwr) {this->numerikBasePower = pwr;}
        int getMasteryLevel() {return this->masteryLevel;}
        int getBasePower() {return this->numerikBasePower;}

};


#endif