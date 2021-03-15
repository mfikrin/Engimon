#ifndef SKILLITEM_HPP
#define SKILLITEM_HPP

#include "Engimon.hpp"
#include <fstream>
#include <stdlib.h>
#include <time.h>
//string and vectors from engimon

class SkillItem{
private:
	int number;
public:
	SkillItem(){
		number = 0;
	}

	Skill learnByElement(Element el){
		string filename;
		if (el == Element::Fire)
		{
			filename = "skill_fire.txt";
		}else if (el == Element::Water)
		{
			filename = "skill_water.txt";
		}else if (el == Element::Electric)
		{
			filename = "skill_electric.txt";
		}else if (el == Element::Ground)
		{
			filename = "skill_ground.txt";
		}else if (el == Element::Ice)
		{
			filename = "skill_ice.txt";
		}
		string lines;
		ifstream fireSkillList(filename);
		vector<string> names;
		vector<int> numBase;
		int lineCount = 0;
		while(getline(fireSkillList,lines)){
			string name = "";
			string numBaseStr = "";
			int i = 0;
			while(lines[i] != ','){
				name += lines[i];
				i++;
			}
			i++; //offset ','
			while (lines[i] != '.'){
				numBaseStr += lines[i];
				i++;
			}
			names.push_back(name);
			numBase.push_back(stoi(numBaseStr));
			lineCount++;
		}
		fireSkillList.close();
		srand(time(NULL));
		int randomIndexSkill = rand() % lineCount;
		Skill resultSkill = Skill(0,numBase[randomIndexSkill],names[randomIndexSkill]);
		return resultSkill;
	}
	void learn(Engimon * chosenEngimon){
		
		//ngambil element si engimon
		//ngambil nature and ability si engimon(?)
		//bakal randomize skill dari file eksternal sesuaikan dengan
		//elemen dan tipe2 engimonnya
		if (number > 0)
		{
			vector<Element> engimonsElement = chosenEngimon->getElements();
			Element chosenElement = engimonsElement[0];
			if (engimonsElement.size() > 1)
			{
				srand(time(NULL));
				int randomIndex = rand() % engimonsElement.size(); //paling cuman 2
				chosenElement = engimonsElement[randomIndex];
			}
			Skill resultSkill = learnByElement(chosenElement);
			chosenEngimon->addSkill(resultSkill);
			number--;
		}
	}
};

#endif