#ifndef _Engimon_hpp_
#define _Engimon_hpp_

#include <iostream>
#include <string>
#include <vector>

#include "../Skill/Skill.hpp"
#include "../Element/Element.hpp"
// #include "Nature.hpp"
// #include "Ability.hpp"

#define MAX_SKILLS 4
#define MAX_C_EXP 5000
#define MAX_EXP 100

using namespace std;
class Engimon
{
private:
protected:
    int id;
    string name;
    string species;
    string parentNames[2];
    string parentSpecieses[2];
    vector<Skill> skills;
    vector<Element> elements;
    int level;
    int exp;  // experience
    int cExp; // cumulative experience

public:
    // ctor, dtor
    Engimon()
    {
        name = "NO NAME";
        species = "SPECIES NONE";
        parentNames[0] = "none";
        parentNames[1] = "none";
        parentSpecieses[0] = "none";
        parentSpecieses[1] = "none";
        level = 1;
        exp = 0;
        cExp = 0;
        id = 0;
        vector<Element> el;
        elements = el;
    }

    Engimon(string n, string sp, int i, const vector<Element> &el)
    {
        name = n;
        species = sp;
        elements = el;
        parentNames[0] = "none";
        parentNames[1] = "none";
        parentSpecieses[0] = "none";
        parentSpecieses[1] = "none";
        level = 1;
        exp = 0;
        cExp = 0;
        id = i;
    }

    Engimon(const Engimon& other){
        this->id = other.id;
        this->name = other.name;
        this->species = other.species;
        this->parentNames[0] = other.parentNames[0];
        this->parentNames[1] = other.parentNames[1];
        this->parentSpecieses[0] = other.parentSpecieses[0];
        this->parentSpecieses[1] = other.parentSpecieses[1];
        this->level = other.level;
        this->exp = other.exp;
        this->cExp = other.cExp;
        this->skills = other.skills;
        this->elements = other.elements;
    }

    void operator=(const Engimon& other){
        this->id = other.id;
        this->name = other.name;
        this->species = other.species;
        this->parentNames[0] = other.parentNames[0];
        this->parentNames[1] = other.parentNames[1];
        this->parentSpecieses[0] = other.parentSpecieses[0];
        this->parentSpecieses[1] = other.parentSpecieses[1];
        this->level = other.level;
        this->exp = other.exp;
        this->cExp = other.cExp;
        this->skills = other.skills;
        this->elements = other.elements;
    }
    // Engimon (string n, const Engimon& p1, const Engimon& p2){

    // }

    // ~Engimon(){
    //     cout  << getName() << " telah mencapai batas Cumulative Experience (" << MAX_C_EXP << " exp).\nEngimon mati (\"x x)" << endl;
    // }

    // GETTER
    string getName()
    {
        return name;
    }
    string *getParentNames()
    {
        return parentNames;
    }
    string *getParentSpecieses()
    {
        return parentSpecieses;
    }
    vector<Skill> getSkills()
    {
        return skills;
    }
    vector<Element> getElements()
    {
        return elements;
    }
    int getLevel()
    {
        return level;
    }
    int getExp()
    {
        return exp;
    }
    int getCExp()
    {
        return cExp;
    }

    // SETTER
    void setName(string n)
    {
        name = n;
    }
    void setParentNames(string p1, string p2)
    {
        parentNames[0] = p1;
        parentNames[1] = p2;
    }
    void setParentSpecies(string parent1Species, string parent2Species)
    {
        parentSpecieses[0] = parent1Species;
        parentSpecieses[1] = parent2Species;
    }
    void addSkill(Skill s)
    {
        if (skills.size() < MAX_SKILLS){
            bool valid = true;
            for (int i = 0; i < skills.size(); i++)
            {
                if (skills[i].getSkillId() == s.getSkillId())
                {
                    valid = false;
                }
            }
            if (valid)
            {
                skills.push_back(s);
            }
            else
            {
                // ERROR di sini
            }
        }
    }
    void setLevel(int l)
    {
        level = l;
    }
    void setExp(int e)
    {
        exp = e;
    }

    // OTHER method
    void levelUp()
    {
        setLevel(this->level + 1);
        for (int i = 0; i < skills.size(); i++)
        {
            skills[i].levelUpMastery();
        }
        setExp(exp - MAX_EXP);
    }

    // dipanggil di setiap loop/turn, melakukan update stats pokemon bila diperlukan
    void updateStats()
    {
        if (exp >= MAX_EXP)
        {
            this->levelUp();
            setExp(exp - MAX_EXP);
        }
        if (cExp >= MAX_C_EXP)
        {
            this->~Engimon();
        }
    }

    int getId()
    {
        return id;
    }

    string getSpecies()
    {
        return species;
    }

    void setId(int id)
    {
        this->id = id;
    }

    void printEngimon()
    {
        cout << "["
             << "ID:" << id << " | "
             << "Name:" << name << " | "
             << "Species:" << species << " | ";
        cout << "Element(s):";
        for (int i = 0; i < elements.size(); ++i)
        {
            if (i != 0)
            {
                cout << ",";
            }
            if (elements[i] == Element::Fire)
            {
                cout << "Fire";
            }
            else if (elements[i] == Element::Water)
            {
                cout << "Water";
            }
            else if (elements[i] == Element::Electric)
            {
                cout << "Electric";
            }
            else if (elements[i] == Element::Ground)
            {
                cout << "Ground";
            }
            else if (elements[i] == Element::Ice)
            {
                cout << "Ice";
            }
            else if (elements[i] == Element::NoElement)
            {
                cout << "No Element";
            }
        }
        cout << "]" << endl;
    }

    void printSkills()
    {
        cout << name << "'s Skills :" << endl;
        for (int i = 0; i < skills.size(); ++i)
        {
            skills[i].printSkill();
        }
    }

    friend ostream &operator<<(ostream &os, const Engimon &engimon)
    {
        os << "[" << engimon.name << "]";
        return os;
    }
};

#endif // _Engimon_hpp_