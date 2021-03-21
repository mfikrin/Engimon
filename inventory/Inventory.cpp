#include "Inventory.hpp"
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
    Skill s2;
    SkillItem sk(s1);
    SkillItem sk_2(s2);

    s1.printSkill();

    cout << sk << endl;

    e1.printEngimon();

    cout << e1 << endl;

    // Inventory<Engimon,MAX_ENGIMON_INV> inv;
    Inventory<Engimon,3> inv_engimon;

    cout <<"MAX : " <<inv_engimon.get_nMAX()<< endl;

    // string name = e1.getName();
    // cout << name << endl;
    try
    {
        inv_engimon.add_item(e1);
        inv_engimon.add_item(e2);
        inv_engimon.add_item(e3);
        inv_engimon.add_item(e4);
    }
    catch(const Engimon& e)
    {
        cout << "Ga cukup lg euy (Engimon)" << endl;
    }

    inv_engimon.show_bag();

    cout << inv_engimon.get_nItem() << endl;
    
    inv_engimon.delete_item(1);
    cout << inv_engimon.get_nItem() << endl;
    inv_engimon.delete_item(4);
    cout << inv_engimon.get_nItem() << endl;

    inv_engimon.show_bag();
    // Inventory<SkillItem,MAX_SKILL_ITEM_INV> inv;
    Inventory<SkillItem,3> inv_skill_item;

    try
    {
        inv_skill_item.add_item(sk);
        inv_skill_item.add_item(sk_2);
        inv_skill_item.add_item(sk);
        inv_skill_item.add_item(sk_2);
    }
    catch(const SkillItem& e)
    {
        cout << "Ga cukup lg euy (skill)" << endl;
    }
    cout << inv_skill_item.get_nItem() << endl;
    inv_skill_item.show_bag();

    inv_skill_item.delete_item(2);
    cout << "item :"<<inv_skill_item.get_nItem() << endl;

    inv_skill_item.add_item(sk);
    cout << "item :" << inv_skill_item.get_nItem() << endl;
    inv_skill_item.show_bag();

}