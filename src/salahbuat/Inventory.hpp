#ifndef _INVENTORY_HPP_
#define _INVENTORY_HPP_

#include <iostream>
#include <map>
#include <iterator>
//#include "SkillItem.hpp"
//#include "Engimon.hpp"

#define MAX_INV 1000
using namespace std;


template<class T, int N>
class Inventory
{
    private:
        map<int, T> map_item; // Key : Id item (skill atau engimon) ; Value : Informasi class (skill atau engimon)
        int n_item;
    public:
    	Inventory(){
    		this->n_item = 0;
		}
		
		int get_nItem(){
			return this->n_item;
		}
        void add_item(int id, T item){
        	if (this->n_item < MAX_INV){
				map_item.insert(pair<int, T> (id,item));
				this->n_item += 1;
			}
			else{
				throw item;
			}
		}
		
		void delete_item(int id){
			if (this->n_item >= 1){
				map_item.erase(id);
				this->n_item -= 1;
			}
		}
		
		void show_bag(){
			map<int, int>::iterator it;
			cout << "\tID\tITEM\n"; 
    		for (it = map_item.begin(); it != map_item.end(); it++) { 
        		cout << '\t' << it->first 
             	<< '\t' << it->second << '\n'; 
    		} 
    		cout << endl; 
		}
		
};
#endif

// blm dicoba klw tipenya class

//int main (){
//	Inventory<int, 4> inv;
//	inv.show_bag();
//	cout << inv.get_nItem() << endl;
//	inv.add_item(2,4);
//	inv.show_bag();		
//	cout << inv.get_nItem() << endl;
//	inv.delete_item(2);
//	inv.show_bag();
//	cout << inv.get_nItem() << endl;
//	
//	return 0;
//	
//}
