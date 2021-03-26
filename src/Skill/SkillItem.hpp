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
		number = 1;
		containedSkill = skill;
	}

	SkillItem(){
		number = 1;
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

	void reduceNumber(){
		number--;
	}

	int getId()
	{
		return containedSkill.getSkillId();
	}

	bool learn(Engimon& chosen)
	{
		if (number > 0)
		{
			vector<Element> chosensElement = chosen.getElements();
			bool added = false;
			for (int i = 0; i < chosensElement.size(); ++i)
			{
				if (chosensElement[i] == containedSkill.getElement() || containedSkill.getElement() == Element::NoElement)
				{
					chosen.addSkill(containedSkill);
					added = true;
					break;
				}
			}
			if (!added)
			{
				cout << "Not Compatible!" << endl;
			}
			return added;
		}
		else
		{
			cout << "Can't learn!" << endl;
			return false;
		}
	}

	friend ostream &operator<<(ostream &os, SkillItem &skill_item)
	{
		os << "[" << skill_item.getName();
		if (skill_item.containedSkill.getElement() == Element::Fire){
			os << "|Element:Fire";
		}else if (skill_item.containedSkill.getElement() == Element::Water)
		{
			os << "|Element:Water";
		}else if (skill_item.containedSkill.getElement() == Element::Electric)
		{
			os << "|Element:Electric";
		}else if (skill_item.containedSkill.getElement() == Element::Ground)
		{
			os << "|Element:Ground";
		}else if (skill_item.containedSkill.getElement() == Element::Ice)
		{
			os << "|Element:Ice";
		}else if (skill_item.containedSkill.getElement() == Element::NoElement)
		{
			os << "|Element:No Element";
		}
		os << "|Power:" << skill_item.containedSkill.getPower();
		os << "|Number:" << skill_item.number << "]";
		
		return os;
	}
};

#endif