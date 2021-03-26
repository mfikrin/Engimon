#ifndef _INVENTORY_HPP_
#define _INVENTORY_HPP_

#include <iostream>
#include <map>
#include <iterator>
#include <string>
#include "../Skill/SkillItem.hpp"
#include "../Engimon/Engimon.hpp"
#include "../Engimon/EngimonEnemy.hpp"
#include "../Engimon/EngimonUser.hpp"

#define MAX_INV 1000
#define MAX_ENGIMON_INV 500
#define MAX_SKILL_ITEM_INV 500
#define FOUND_ITEM 1
#define NOT_FOUND_ITEM -1
using namespace std;

template <class T> // N akan diisi dengan MAX_INV
class Inventory
{
private:
	map<int, T> map_item; // Key : Id item (skill atau engimon) ; Value : Informasi class (skill atau engimon)
	int id_inven;
	const int max_inv = 500;
	int n_item;

public:
	// int Inventory::id_inven = 1;
	Inventory()
	{
		this->n_item = 0;
		this->id_inven = 0;
	}

	void operator=(const Inventory<T>& other){
		this->id_inven = other.id_inven;
		this->n_item = other.n_item;
		this->map_item = other.map_item;
	}

	int get_nItem()
	{
		return this->n_item;
	}

	int get_nMAX()
	{
		return this->max_inv;
	}
	void add_item(T item)
	{
		if (this->n_item < this->max_inv)
		{
			this->id_inven += 1;
			map_item.insert(pair<int, T>(id_inven, item));
			this->n_item += 1;
		}
		else
		{
			throw item;
		}
	}

	void delete_item(int id_inven)
	{
		if (this->n_item >= 1)
		{
			if (map_item.erase(id_inven)) // id ada
			{
				//cout << "yuhuu" << endl;
				map_item.erase(id_inven);
				this->n_item -= 1;
				cout << "Item dengan ID " << id_inven << " telah dihapus" << endl;
			}
			else
			{
				cout << "Tidak ada item dengan ID " << id_inven << endl;
			}
		}
	}

	void show_bag()
	{

		cout << "\tID\tITEM\n";
		for (auto &it : map_item)
		{
			cout << '\t' << it.first << '\t';
			cout << it.second; // operator overload engimon / skill item
			cout << endl;
		}
		cout << endl;
	}

	bool check_item_availability(int id)
	{
		bool available = false;
		for (auto &it : map_item)
		{
			if (it.first == id)
			{
				available == true;
				break;
			}
		}
		return available;
	}

	T select_item(int id_inven)
	{
		T e;

		for (auto &it : map_item)
		{
			if (it.first == id_inven)
			{
				e = it.second;
				delete_item(id_inven);
			}
		}
		return e;
	}

	// void Add_inv_skill(SkillItem &s1)
	// {
	// 	for (auto &it : map_item)
	// 	{
	// 		SkillItem 
	// 		if (it.second ==)
	// 		// SkillItem namaskill = this->inv_skill[i]
	// 		// if (this->[i].get){
	// 	}

	// 	//  this->inv_skill.add_item(s1);
	// }
};

template<>
class Inventory <SkillItem>
{
private:
	map<int, SkillItem> map_item; // Key : Id item (skill atau engimon) ; Value : Informasi class (skill atau engimon)
	int id_inven;
	const int max_inv = 500;
	int n_item;
public:
	Inventory()
	{
		this->n_item = 0;
		this->id_inven = 0;
	}

	void operator=(const Inventory<SkillItem>& other){
		this->id_inven = other.id_inven;
		this->n_item = other.n_item;
		this->map_item = other.map_item;
	}

	int get_nItem()
	{
		return this->n_item;
	}

	int get_nMAX()
	{
		return this->max_inv;
	}
	void add_item(SkillItem item)
	{
		if (this->n_item < this->max_inv)
		{
			bool found = false;
			for(auto &it : map_item){
				if (it.second.getName() == item.getName()){
					it.second.addNumber();
					this->n_item++;
					found = true;
				}
			}

			if(!found){
				this->id_inven += 1;
				map_item.insert(pair<int, SkillItem>(id_inven, item));
				this->n_item += 1;
			}
		}
		else
		{
			throw item;
		}
	}

	void delete_item(int id_inven)
	{
		if (this->n_item >= 1)
		{
			for(auto &it: map_item){
				if (it.second.getNumber() > 1){
					it.second.reduceNumber();
				}else{
					map_item.erase(it.first);
				}
			}
		}
	}

	void show_bag()
	{

		cout << "\tID\tITEM\n";
		for (auto &it : map_item)
		{
			cout << '\t' << it.first << '\t';
			cout << it.second; // operator overload engimon / skill item
			cout << endl;
		}
		cout << endl;
	}

	bool check_item_availability(int id)
	{
		bool available = false;
		for (auto &it : map_item)
		{
			if (it.first == id)
			{
				available = true;
				break;
			}
		}
		return available;
	}

	SkillItem select_item(int id_inven)
	{
		SkillItem e;

		for (auto &it : map_item)
		{
			if (it.first == id_inven)
			{
				e = it.second;
				delete_item(id_inven);
			}
		}
		return e;
	}

	void learn(EngimonUser& e, int id_inven){
		if (check_item_availability(id_inven)){
			if(map_item[id_inven].learn(e)){
				delete_item(id_inven);
			}
		}else{
			//throw mungkin
		}
	}
};
#endif