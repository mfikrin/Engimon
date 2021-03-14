#ifndef SKILL_H
#define SKILL_H

#include <string>

class Skill {
    private :
        int masteryLevel;
        int numerikBasePower;
        string skillName;

    public :
        Skill() : masteryLevel(0), numerikBasePower(0), skillName("No Name"){}
        Skill(int level, int basePWR, string skillName) : masteryLevel(level), numerikBasePower(basePWR), skillName(skillName) {}

        void setMasteryLevel(int level){this->masteryLevel = level;}
        void setBasePower(int pwr) {this->numerikBasePower = pwr;}
        void setSkillName (string newskillname) {this->skillName = newskillname;}
        int getMasteryLevel() {return this->masteryLevel;}
        int getBasePower() {return this->numerikBasePower;}
        string getSkillName() {return this->skillName;}
};


#endif