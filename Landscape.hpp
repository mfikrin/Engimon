#ifndef LANDSCAPE__HPP
#define LANDSCAPE__HPP
#include "LandscapeType.hpp"
#include "Engimon.hpp"
#include <stdlib.h>

class Landscape {
    private:
        LandscapeType type;
        Engimon engimonLiar; // kalau yang di-spawn engimonLiar, harusnya pakai class EngimonEnemy

    public:
        Landscape(LandscapeType type) {
            this->type = type;
        }

        void SpawnEngimon(vector<vector<Engimon>> Ensiklopedia) {
            if (this->type == LandscapeType::Grassland)
            {
                int randomElement = rand() % 5;
                
                while (randomElement == 1 || randomElement == 4) 
                {
                    randomElement = rand() % 5;
                }
                
                int randomEngimon = rand() % Engimon[randomElement].size(); // ini apa gk typo vaz? mungkin maksudnya Ensiklopedia[randomElement].size()
                engimonLiar = Ensiklopedia[randomElement][randomEngimon];

                
            } else // (this->type == LandscapeType::Sea)
            {
                int randomElement = rand() % 5;
                while (randomElement == 0 || randomElement == 2 || randomElement == 3) 
                {
                    randomElement = rand() % 5;
                }
            }
            
            int randomEngimon = rand() % Engimon[randomElement].size(); // ini juga
                engimonLiar = Ensiklopedia[randomElement][randomEngimon];
            
        }
};

#endif