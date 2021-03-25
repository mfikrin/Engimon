#ifndef SKILLITEM_HPP
#define SKILLITEM_HPP

#include "../Engimon/Engimon.hpp"
#include <iostream>

using namespace std;

//string and vectors from engimon

class SkillItem
{
private:
	int number;
	Skill containedSkill;

public:
	SkillItem(const Skill &skill)
	{
		number = 0;
		containedSkill = skill;
	}

	int getNumber()
	{
		return number;
	}

	string getName()
	{
		return containedSkill.getSkillName();
	}

	void setNumber(int number)
	{
		this->number = number;
	}

	void addNumber()
	{
		number++;
	}

	int getId()
	{
		return containedSkill.getSkillId();
	}

	void learn(Engimon *chosen)
	{
		if (number > 0)
		{
			vector<Element> chosensElement = chosen->getElements();
			bool added = false;
			for (int i = 0; i < chosensElement.size(); ++i)
			{
				if (chosensElement[i] == containedSkill.getElement() || containedSkill.getElement() == Element::NoElement)
				{
					chosen->addSkill(containedSkill);
					added = true;
					number--;
					break;
				}
			}
			if (!added)
			{
				cout << "Not Compatible!" << endl;
			}
		}
		else
		{
			cout << "Can't learn!" << endl;
		}
	}

	friend ostream &operator<<(ostream &os, SkillItem &skill_item)
	{
		os << "[" << skill_item.getName() << "]"; //
		return os;
	}
};

#endif