#include "Inventory_v2.hpp"
#include "../Engimon.hpp"
#include <string>
#include "../SkillItem.hpp"
#include "../Skill.hpp"
#include <iostream>
#include <vector>

using namespace std;

int main(){
    vector<Element> elements;
    Engimon e1("digimon", "emon", 1, elements);
    Engimon e2("digimon2", "emon1", 1, elements);
    Engimon e3("digimon3", "emon2", 1, elements);
    Engimon e4("digimon4", "emon3", 1, elements);
    // Skill(int idSkill, int level, int basePWR, string skillName, Element el)
    Skill s1;
    SkillItem sk(s1);

    s1.printSkill();

    cout << sk << endl;

    e1.printEngimon();

    cout << e1 << endl;

    

    Inventory<1000> inv ;

    cout << "MAX : " << inv.get_nMAX() << endl;
    try
    {
        inv.add_item(e1);
        inv.add_item(sk);
        inv.add_item(e2);
        inv.add_item(e3);
        inv.add_item(e4);
    }
    catch(const Engimon& e)
    {
        cout << "Ga cukup lg euy(Engimon)"  << endl;
    }
    catch(const SkillItem& e)
    {
        cout << "Ga cukup lg euy(Skill item)" << endl;
    }
    
    
    

    cout << "Banyak item : "<<inv.get_nItem() << endl;
    inv.show_bag();

    // cout << inv.search_id_engimon(1) << endl;

    // cout << inv.search_id_engimon(2) << endl;

    inv.delete_item(1);

    cout << "banyak item " << inv.get_nItem() << endl;

    inv.show_bag();

    cout << "banyak item " << inv.get_nItem() << endl;

    // // string name = e1.getName();
    // // cout << name << endl;

    // inv_engimon.add_item(1,e1);

    // inv_engimon.show_bag();

    // Inventory<SkillItem,4> inv_skill_item;

    // inv_skill_item.add_item(2,sk);

    // inv_skill_item.show_bag();
}