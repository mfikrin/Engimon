#ifndef LANDSCAPE__HPP
#define LANDSCAPE__HPP
#include "LandscapeType.hpp"
#include "Engimon.hpp"
#include <stdlib.h>
#include <time.h>

class Landscape
{
private:
    LandscapeType type;
    Engimon engimonLiar; // kalau yang di-spawn engimonLiar, harusnya pakai class EngimonEnemy

public:
    Landscape(LandscapeType type)
    {
        this->type = type;
    }

    Skill GetSkillEngimonLiar(const vector<vector<Skill>>& Ensiklopedia , Element el){
        int idx = 0;
        if (el == Element::Fire){
            idx = 0;
        }else if(el == Element::Water){
            idx = 1;
        }else if (el == Element::Electric)
        {
            idx = 2;
        }else if (el == Element::Ground)
        {
            idx = 3;
        }else if (el == Element::Ice){
            idx = 4;
        }else if (el == Element::NoElement)
        {
            idx = 5;
        }

        srand(time(NULL));

        int idxSkill = rand() % Ensiklopedia[idx].size();
        return Ensiklopedia[idx][idxSkill];

    }

    void SpawnEngimon(const vector<vector<Engimon>>& Ensiklopedia , const vector<vector<Skill>>& EnsiklopediaSkill)
    {
        //nanti coba kasih parameter level active engimon biar bisa dapet level musuh yang sesuai
        //begitu pun mastery level skill2nya dan jumlah skill2nya
        srand(time(NULL));
        int randomElement;
        if (this->type == LandscapeType::Sea)
        {
            do{
                randomElement = rand() % 5;
            }while (randomElement == 1 || randomElement == 4);

            int randomEngimon = rand() % Engimon[randomElement].size(); // ini apa gk typo vaz? mungkin maksudnya Ensiklopedia[randomElement].size()
            engimonLiar = Ensiklopedia[randomElement][randomEngimon];
        }
        else // (this->type == LandscapeType::GrassLand)
        {
            do{
                randomElement = rand() % 5;
            }while (randomElement == 0 || randomElement == 2 || randomElement == 3)
        }

        Element el;
        if (randomElement == 0){
            el == Element::Fire
        }else if(randomElement == 1){
            el == Element::Water
        }else if (randomElement == 2)
        {
            el == Element::Electric
        }else if (randomElement == 3)
        {
            el == Element::Ground
        }else if (randomElement == 4){
            el == Element::Ice
        }

        int randomEngimon = rand() % Engimon[randomElement].size(); // ini juga
        engimonLiar = Ensiklopedia[randomElement][randomEngimon];
        engimonLiar.addSkill(GetSkillEngimonLiar(EnsiklopediaSkill,el));
        engimonLiar.addSkill(GetSkillEngimonLiar(EnsiklopediaSkill,Element::NoElement));
    }
};

#endif