#ifndef SKILLITEM_HPP
#define SKILLITEM_HPP

#include "Engimon.hpp"
//string and vectors from engimon

class SkillItem{
private:
	int number;
	Skill containedSkill;
public:
	SkillItem(const Skill& skill){
		number = 0;
		containedSkill = skill;
	}

	int getNumber(){
		return number;
	}

	void learn(Engimon * chosen){
		vector<Element> chosensElement = chosen->getElements();
		for (int i = 0; i < chosensElement.size(); ++i)
		{
			if (chosensElement[i] == containedSkill.getElement())
			{
				chosen->addSkill(containedSkill);
			}
		}
	}
};

#endif