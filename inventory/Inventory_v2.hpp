#ifndef _INVENTORY_HPP_
#define _INVENTORY_HPP_


#include <iostream>
#include <map>
#include <iterator>
#include <string>
#include "../SkillItem.hpp"
#include "../Engimon.hpp"

#define MAX_INV 1000
#define FOUND_ENGIMON 1
#define FOUND_SKILL_ITEM 2
#define NOT_FOUND_ENGIMON -1
#define NOT_FOUND_SKILL_ITEM -2

using namespace std;


template<int N> // N diisi dengan MAX_INV
class Inventory
{
    private:
        map<int, Engimon> map_engimon; // Key : Id item (skill atau engimon) ; Value : Informasi class (skill atau engimon)
        map<int, SkillItem> map_skill_item;
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

        void add_item(Engimon engimon){
        	if (this->n_item < this->max_inv){
                this->id_inven += 1;
                map_engimon.insert(pair<int, Engimon> (id_inven, engimon));
				this->n_item += 1;
                
            }
			else{
				throw engimon;
			}
		}

        void add_item(SkillItem skill_item)
        {
            if (this->n_item < this->max_inv)
            {
                this->id_inven += 1;
                map_skill_item.insert(pair<int, SkillItem>(id_inven, skill_item));
                this->n_item += 1;
                // this->id_inven += 1;
            }
            else
            {
                throw skill_item;
            }
        }


        void delete_item(int id_inven){

			if (this->n_item >= 1){
                if (map_engimon.erase(id_inven))
                {
                    map_engimon.erase(id_inven);
                    this->n_item -= 1;
                    cout << "Item dengan ID " << id_inven << " telah dihapus" << endl;
                }
                else if (map_skill_item.erase(id_inven))
                {
                    map_skill_item.erase(id_inven);
                    this->n_item -= 1;
                    cout << "Item dengan ID " << id_inven << " telah dihapus" << endl;
                }
                else
                {
                    cout << "Tidak ada id " << id_inven << " di inventory" << endl;
                }
				
				
			}
		}
		
		void show_bag(){
			
			std::cout << "\tID\tITEM (Engimon)\n"; 
			for(auto &it:map_engimon){
				std::cout << '\t' << it.first << '\t';
				cout << it.second; // operator overload engimon
                std::cout << endl;
            }
    		std::cout << endl;

            std::cout << endl;

            std::cout << "\tID\tITEM (Skill item)\n";
            for (auto &it :map_skill_item)
            {
                std::cout << '\t' << it.first << '\t';
                cout << it.second; // operator overload skill_item
                std::cout << endl;
            }
            std::cout << endl;
        }
		
};
#endif