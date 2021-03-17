#ifndef SKILL_H
#define SKILL_H

#include <string>
#include "Element.hpp"
#include <iostream>
using namespace std;

class Skill {
    private :
        int id;
        int masteryLevel;
        int numerikBasePower;
        string skillName;
        Element element;

    public :
        Skill() : id(0), masteryLevel(0), numerikBasePower(0), skillName("No Name"), element(Element::NoElement){}
        Skill(int idSkill, int level, int basePWR, string skillName, Element el) : id(idSkill), masteryLevel(level), numerikBasePower(basePWR), skillName(skillName), element(el) {}
        void setMasteryLevel(int level){this->masteryLevel = level;}
        void setBasePower(int pwr) {this->numerikBasePower = pwr;}
        void setSkillName (string newskillname) {this->skillName = newskillname;}
        int getMasteryLevel() {return this->masteryLevel;}
        int getBasePower() {return this->numerikBasePower;}
        string getSkillName() {return this->skillName;}
        int getSkillId() {return id;}
        void setSkillId(int id) {this->id = id;}
        Element getElement() {return element;}
        void setElement(Element element) {this->element = element;}
        void printSkill(){
            cout << "[";
            cout << "id:" << id <<" | ";
            cout << "Skill's Name:" << skillName << " | ";
            cout << "Numerik Base Power:" << numerikBasePower << " | ";
            cout << "Element:";
            if (element == Element::Fire)
            {
                cout << "Fire";
            }else if (element == Element::Water)
            {
                cout << "Water";
            }else if (element == Element::Electric)
            {
                cout << "Electric";
            }else if (element == Element::Ground)
            {
                cout << "Ground";
            }else if (element == Element::Ice)
            {
                cout << "Ice";
            }else if (element == Element::NoElement)
            {
                cout << "No Element";
            }
            cout << " | ";
            cout << "Mastery Level:" << masteryLevel << "]" << endl;
        }
};


#endif