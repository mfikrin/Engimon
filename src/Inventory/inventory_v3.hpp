#ifndef _INVENTORYV3_HPP_
#define _INVENTORYV3_HPP_

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

template <class T, int N> // N akan diisi dengan MAX_INV
class Inventory
{
private:
    map<int, map<T,int>> map_item; // Key : Id item (skill atau engimon) ; Value : Informasi class (skill atau engimon)
    int id_inven;
    const int max_inv = N;
    int n_item;

public:
    // int Inventory::id_inven = 1;
    Inventory()
    {
        this->n_item = 0;
        this->id_inven = 0;
    }

    void operator=(const Inventory<T, N> &other)
    {
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
    void add_item(EngimonUser item)
    {
        if (this->n_item < this->max_inv)
        {
            // m.insert(make_pair("Noob", map<int, int>()));
            // m["Noob"].insert(make_pair(0, 5));

            this->id_inven += 1;
            map_item.insert(make_pair(this->id_inven, map<EngimonUser,int>())); 
            int n_T = 1;
            map_item[this->id_inven].insert(make_pair(item,n_T));
            this->n_item += 1;
        }
        else
        {
            throw item;
        }
    }

    bool check_key(map<T,int> map, T key){
        if (map.find(key) == map.end()){
            return false;
        }
        return true;
    }
    

    void add_item(SkillItem item)
    {
        if (this->n_item < this->max_inv)
        {
            // m.insert(make_pair("Noob", map<int, int>()));
            // m["Noob"].insert(make_pair(0, 5));
            
            this->id_inven += 1;
            if (!(check_key(map_item[this->id_inven],item)))
                map_item.insert(make_pair(this->id_inven, map<SkillItem, int>()));
                int n_T = item.getNumber();
                map_item[this->id_inven].insert(make_pair(item, n_T));
                this->n_item += 1;
            else{
                int n_current = item.getNumber();
                int n_new = n_current + 1;
                map_item[item] = n_new;
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
#endif