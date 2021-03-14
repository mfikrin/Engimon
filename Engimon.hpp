#ifndef _Engimon_hpp_
#define _Engimon_hpp_

#include <iostream>
#include <string>
#include <vector>

#include "Skill.hpp"
#include "Element.hpp"
// #include "Nature.hpp"
// #include "Ability.hpp"

using namespace std;
class Engimon{
    private:
        int maxSkills = 4;

    protected:
        string name;
        string parentNames[2];
        Skill skills[4];
        vector<Element> elements;
        int level;
        int exp; // experience
        int cExp; // cumulative experience
        // Nature nature;
        // Ability ability;
        
    public:
        int getMaxSkills(){
            return maxSkills;
        }

};

#endif // _Engimon_hpp_