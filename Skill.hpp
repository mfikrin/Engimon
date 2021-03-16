#ifndef SKILL_H
#define SKILL_H

#include <string>

class Skill {
    private :
        int id;
        int masteryLevel;
        int numerikBasePower;
        string skillName;
        Element element;

    public :
        Skill() : id(0), masteryLevel(0), numerikBasePower(0), skillName("No Name"){}
        Skill(int idSkill, int level, int basePWR, string skillName, Element el) : id(idSkill), masteryLevel(level), numerikBasePower(basePWR), skillName(skillName), element(el) {}
        void setMasteryLevel(int level){this->masteryLevel = level;}
        void setBasePower(int pwr) {this->numerikBasePower = pwr;}
        void setSkillName (string newskillname) {this->skillName = newskillname;}
        int getMasteryLevel() {return this->masteryLevel;}
        int getBasePower() {return this->numerikBasePower;}
        string getSkillName() {return this->skillName;}
        int getSkillId() {return id;}
        Element getElement() {return element;}
};


#endif