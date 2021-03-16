#ifndef BOOKOF_LORE_HPP
#define BOOKOF_LORE_HPP

#include "Engimon.hpp"
#include "Skill.hpp"
#include <fstream>

class BookOfLore{
private:
	vector<vector<Engimon>> engimonLore; //by element
	vector<vector<Skill>> skillLore; //by element
public:
	vector<Skill> generateSkillPerElement(const Element& el){
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
		ifstream listSkill(filename);
		string line;
		vector<Skill> result;
		while(getline(listSkill,line)){
			string name = "";
			string numBase = "";
			string id = "";
			int i = 0;
			while(line[i] != ','){
				name += line[i];
				i++;
			}
			i++; //offset ','
			while(line[i] != ','){
				numBase += line[i];
				i++;
			}
			i++; //offset ','
			while(line[i] != '.'){
				id += line[i];
			}
			result.push_back(Skill(stoi(id),0,stoi(numBase),name,el));
		}
		listSkill.close();
		return result;
	}

	vector<vector<Skill>> allSkill(){
		vector<vector<Skill>> result;
		Element elements[5] = {Element::Fire,Element::Water,Element::Electric,Element::Ground,Element::Ice};
		for (int i = 0; i < 5; ++i)
		{
			result.push_back(generateSkillPerElement(elements[i]));
		}
		return result;
	}
	BookOfLore(){
		skillLore = allSkill();
	}
};

#endif