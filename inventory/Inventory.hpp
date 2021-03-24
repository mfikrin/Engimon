#ifndef _INVENTORY_HPP_
#define _INVENTORY_HPP_


#include <iostream>
#include <map>
#include <iterator>
#include <string>
#include "../SkillItem.hpp"
#include "../Engimon.hpp"
#include "../EngimonEnemy.hpp"
#include "../EngimonUser.hpp"

#define MAX_INV 1000
#define MAX_ENGIMON_INV 500
#define MAX_SKILL_ITEM_INV 500
#define FOUND_ITEM 1
#define NOT_FOUND_ITEM -1
using namespace std;


template<class T, int N> // N akan diisi dengan MAX_INV
class Inventory
{
    private:
        map<int, T> map_item; // Key : Id item (skill atau engimon) ; Value : Informasi class (skill atau engimon)
		int id_inven;
		const int max_inv = N;
		int n_item;
    public:

		// int Inventory::id_inven = 1;
    	Inventory(){
    		this->n_item = 0;
			this->id_inven = 0;
		}
		
		int get_nItem(){
			return this->n_item;
		}

		int get_nMAX()
		{
			return this->max_inv;
		}
		void add_item(T item){
        	if (this->n_item < this->max_inv){
				this->id_inven += 1;
				map_item.insert(pair<int, T> (id_inven, item));
				this->n_item += 1;
			}
			else{
				throw item;
			}
		}

		void delete_item(int id_inven){
			if (this->n_item >= 1)
			{
				if (map_item.erase(id_inven)) // id ada
				{
					cout << "yuhuu" << endl;
					map_item.erase(id_inven);
					this->n_item -= 1;
					cout << "Item dengan ID "<< id_inven<< " telah dihapus" << endl;
				}else{
					cout << "Tidak ada item dengan ID " << id_inven << endl;
				}	
			}
		}
		
		void show_bag(){
			
			cout << "\tID\tITEM\n"; 
			for(auto &it:map_item){
				cout << '\t' << it.first << '\t';
				cout << it.second; // operator overload engimon / skill item
				cout << endl;
			}
    		cout << endl;	 
		}
		
};
#endif