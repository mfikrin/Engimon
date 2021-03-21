#ifndef BOOKOF_LORE_HPP
#define BOOKOF_LORE_HPP

#include "Engimon.hpp"
#include "Skill.hpp"
#include <fstream>

class BookOfLore{
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
		}else if (el == Element::NoElement)
		{
			filename = "skill_basic.txt";
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
				i++;
			}
			result.push_back(Skill(stoi(id),1,stoi(numBase),name,el));
		}
		listSkill.close();
		return result;
	}

	vector<vector<Skill>> allSkill(){
		vector<vector<Skill>> result;
		Element elements[6] = {Element::Fire,
			Element::Water,
			Element::Electric,
			Element::Ground,
			Element::Ice,
			Element::NoElement};
		for (int i = 0; i < 6; ++i)
		{
			result.push_back(generateSkillPerElement(elements[i]));
		}
		return result;
	}

	vector<Engimon> engimonByElement(const Element& el){
		string filename;
		if (el == Element::Fire)
		{
			filename = "engimon_fire.txt";
		}else if (el == Element::Water)
		{
			filename = "engimon_water.txt";
		}else if (el == Element::Electric)
		{
			filename = "engimon_electric.txt";
		}else if (el == Element::Ground)
		{
			filename = "engimon_ground.txt";
		}else if (el == Element::Ice)
		{
			filename = "engimon_ice.txt";
		}
		ifstream listEngimon(filename);
		string line;
		vector<Engimon> engimons;
		while(getline(listEngimon,line)){
			string name = "";
			string species = "";
			string id = "";
			int i = 0;
			while(line[i] != ','){
				name += line[i];
				i++;
			}
			i++; //offset ','
			while(line[i] != ','){
				species =+ line[i];
				i++;
			}
			i++; //offset ','
			while(line[i] != '.'){
				id += line[i];
				i++;
			}
			vector<Element> base;
			base.push_back(el);
			engimons.push_back(Engimon(name,species,stoi(id),base));
		}
		listEngimon.close();
		return engimons;
	}

	vector<vector<Engimon>> allEngimon(){
		Element elements[5] = {Element::Fire,
			Element::Water,
			Element::Electric,
			Element::Ground,
			Element::Ice};
		vector<vector<Engimon>> listAllEngimon;
		for (int i = 0; i < 5; ++i)
		{
			listAllEngimon.push_back(engimonByElement(elements[i]));
		}
		return listAllEngimon;
	}
};

#endif