#include "Inventory.hpp"

int main (){
	Inventory<int, 4> inv;
	inv.show_bag();
	cout << inv.get_nItem() << endl;
	inv.add_item(2,4);
	inv.show_bag();		
	cout << inv.get_nItem() << endl;
	inv.delete_item(2);
	inv.show_bag();
	cout << inv.get_nItem() << endl;
	
	return 0;
	
}
