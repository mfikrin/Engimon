#ifndef SKILLITEM_HPP
#define SKILLITEM_HPP

#include "Engimon.hpp"
#include <fstream>

class SkillItem{
private:
	int number;
public:
	SkillItem(){
		number = 0;
	}
	void learn(Engimon * chosenEngimon){
		
		//ngambil element si engimon
		//ngambil nature and ability si engimon(?)
		//bakal randomize skill dari file eksternal sesuaikan dengan
		//elemen dan tipe2 engimonnya
		number--;
	}
};

#endif