#ifndef BREEDING__HPP
#define BREEDING__HPP
#include "../Player/Player.hpp"
#include "../MainProgram/BookOfLore.hpp"
#include "../Element/Element.hpp"
#include "../Engimon/Engimon.hpp"
#include "../Engimon/EngimonUser.hpp"
#include "../Battle/Battle.hpp"
class Breeding {
public:

    bool parentAvailable(Player player, Engimon parentA, Engimon parentB){
        bool parent1Available = player.get_inv_engimon().check_item_availability(parentA.getId());
        bool parent2Available = player.get_inv_engimon().check_item_availability(parentB.getId());
            if (!parent1Available) // parent1 ga ada di inventory
            {
                if (parent2Available) // parent2 ada di inventory
                {
                    cout << "Parent 1 tidak ada di inventory" << endl;
                    return false;
                }
                else
                { // parent2 ga ada di inventory juga
                    cout << "Parent 1 dan Parent 2 tidak ada di inventory" << endl;
                    return false;
                }
            }
            else if (!parent2Available)
            { // parent1 ada di inventory tapi parent2 ga ada
                cout << "Parent 2 tidak ada di inventory" << endl;
                return false;
            } else {
                return true;
            }
    }

    bool parentLevelAbove30(Engimon parentA, Engimon parentB){
        if (parentA.getLevel() < 30 || parentB.getLevel() < 30) // Salah satu parent berlevel kurang dari 30
        {
            if (parentA.getLevel() < 30){
                if (parentB.getLevel() >= 30){
                    cout << "Level Parent 1 kurang dari 30!" << endl;
                    return false;
                } else {
                    cout << "Level Parent 1 dan Parent 2 kurang dari 30!" << endl;
                    return false;
                }
            } else {
                cout << "Level Parent 2 kurang dari 30!" << endl;
                return false;
            }
        } else {
            return true;
        }
    }

    vector<Element> collectParentElement(Engimon parentA, Engimon parentB){
        vector<Element> parentAElement = parentA.getElements();
        vector<Element> parentBElement = parentB.getElements();
        vector<Element> parentElement;
        // MENGOLEKSI ELEMENT PARENT1 KE DALAM ELEMENTPARENT
        for (int i = 0; i < parentAElement.size(); i++){
            parentElement.push_back(parentAElement[i]);
        }

        // MENGOLEKSI ELEMENT PARENT2 KE DALAM ELEMENTPARENT
        for (int i = 0; i < parentBElement.size(); i++){
            // Mengecek apakah element dari elementParent2 sudah ada di elementParent
            bool present = false;
            for (int j = 0; j < parentElement.size(); j++)
            {
                if (parentBElement[i] == parentElement[j]){
                        present = true;
                }
            }

            // Mengoleksi elementParent2 ke dalam elementParent
            if (!present){
                parentElement.push_back(parentBElement[i]);
            }
        }

        return parentElement;
    }

    void breeding(Player player, BookOfLore ensiklopedia, Engimon parent1, Engimon parent2)
    {
        // Sebelum pake breeding, cek dulu apakah inventory penuh// // // // // 
        if (player.get_inv_engimon().get_nItem() == MAX_ENGIMON_INV) /* Inventory penuh */
        {
            cout << "Inventory penuh!" << endl;
        } else {
            bool bothParentAvailable = parentAvailable(player, parent1, parent2);
            if (!bothParentAvailable) // parent1 ga ada di inventory
            {
                // Parent availability udah di-handle di dalem fungsi parentAvailable()

            } else {// parent1 dan parent2 ada di inventory
                bool bothParentLevelAbove30 = parentLevelAbove30(parent1, parent2);
                if (!bothParentLevelAbove30) // Salah satu parent berlevel kurang dari 30
                {
                    // Kasus level parent di bawah 30 udah di handel di dalam fungsi bothParentLevelAbove30()
                } else { // Level kedua parent >= 30
                    int childID;
                    vector<Element> parentElement = collectParentElement(parent1, parent2);
                    vector<Element> parent1Element = parent1.getElements();
                    vector<Element> parent2Element = parent2.getElements();
                    vector<Element> childElement;
                    vector<Skill> parentSkill;
                    vector<Skill> childSkill;
                    string childName;
                    string childSpecies;
                    cout << "Masukkan nama anak!" << endl;
                    cin >> childName;
                    
                    // MEMBANDINGKAN ELEMENT KEDUA PARENT
                    if (parent1Element.size() == parent2Element.size())
                    {
                        bool parentSimilarity = true;
                        int i = 0;
                        while (i < parent1Element.size() && parentSimilarity)
                        {
                            if (parent1Element[i] != parent2Element[i]) // Kalau masih ada waktu bisa improve
                            {
                                parentSimilarity = false;
                            }
                            i++;
                        }
                        if (parentSimilarity) // Kedua parent ber-element sama
                        {
                            int speciesRandomizer = rand() % 2;
                            childElement = parent1Element;
                            if (speciesRandomizer)
                            {
                                childSpecies = parent1.getSpecies();
                            }
                            else
                            {
                                childSpecies = parent2.getSpecies();
                            }
                        }
                        else
                        { // Elemen kedua parent berbeda
                            if (parent1Element.size() == 1 && parent2Element.size() == 1)
                            {
                                if (Battle::get_advantage(parent1Element[0], parent2Element[0]) > Battle::get_advantage(parent2Element[0], parent1Element[0]))
                                {
                                    childSpecies = parent1.getSpecies();
                                    childElement = parent1.getElements();
                                }
                                else if (Battle::get_advantage(parent1Element[0], parent2Element[0]) < Battle::get_advantage(parent2Element[0], parent1Element[0]))
                                {
                                    childSpecies = parent2.getSpecies();
                                    childElement = parent2.getElements();
                                }
                                else
                                { // Element advantage sama
                                    int indexRandomizer = rand() % ensiklopedia.allEngimon().size();
                                    int speciesRandomizer = rand() % ensiklopedia.allEngimon()[indexRandomizer].size();
                                    childSpecies = ensiklopedia.allEngimon()[indexRandomizer][speciesRandomizer].getSpecies();
                                    while (childSpecies == parent1.getSpecies() || childSpecies == parent2.getSpecies())
                                    {
                                        indexRandomizer = rand() % ensiklopedia.allEngimon().size();
                                        speciesRandomizer = rand() % ensiklopedia.allEngimon()[indexRandomizer].size();
                                        childSpecies = parent1.getSpecies() + to_string(speciesRandomizer);
                                        childSpecies = ensiklopedia.allEngimon()[indexRandomizer][speciesRandomizer].getSpecies();
                                    }
                                    childElement = parentElement;
                                }
                            }
                            else
                            { // Element parent lebih dari 1
                                int duaElement = rand() % 2;
                                if (duaElement)
                                {
                                    int element1Index = rand() % parentElement.size();
                                    int element2Index = rand() % parentElement.size();
                                    while (element2Index == element1Index)
                                    {
                                        element2Index = rand() % parentElement.size();
                                    }

                                    childElement.push_back(parentElement[element1Index]);
                                    childElement.push_back(parentElement[element2Index]);
                                }
                                else
                                {
                                    int elementIndex = rand() % parentElement.size();
                                    childElement.push_back(parentElement[elementIndex]);
                                }
                            }
                        }
                    }
                    else
                    { // Element kedua parent berbeda
                        if (parent1Element.size() == 1 && parent2Element.size() == 1)
                        {
                            if (Battle::get_advantage(parent1Element[0], parent2Element[0]) > Battle::get_advantage(parent2Element[0], parent1Element[0]))
                            {
                                childSpecies = parent1.getSpecies();
                                childElement = parent1.getElements();
                            }
                            else if (Battle::get_advantage(parent1Element[0], parent2Element[0]) < Battle::get_advantage(parent2Element[0], parent1Element[0]))
                            {
                                childSpecies = parent2.getSpecies();
                                childElement = parent2.getElements();
                            }
                            else
                            { // Element advantage sama
                                int indexRandomizer = rand() % ensiklopedia.allEngimon().size();
                                int speciesRandomizer = rand() % ensiklopedia.allEngimon()[indexRandomizer].size();
                                childSpecies = ensiklopedia.allEngimon()[indexRandomizer][speciesRandomizer].getSpecies();
                                while (childSpecies == parent1.getSpecies() || childSpecies == parent2.getSpecies())
                                {
                                    indexRandomizer = rand() % ensiklopedia.allEngimon().size();
                                    speciesRandomizer = rand() % ensiklopedia.allEngimon()[indexRandomizer].size();
                                    childSpecies = parent1.getSpecies() + to_string(speciesRandomizer);
                                    childSpecies = ensiklopedia.allEngimon()[indexRandomizer][speciesRandomizer].getSpecies();
                                }
                                childElement = parentElement;
                            }
                        }
                        else
                        { // Element parent lebih dari 1
                            int duaElement = rand() % 2;
                            if (duaElement)
                            {
                                int element1Index = rand() % parentElement.size();
                                int element2Index = rand() % parentElement.size();
                                while (element2Index == element1Index)
                                {
                                    element2Index = rand() % parentElement.size();
                                }

                                childElement.push_back(parentElement[element1Index]);
                                childElement.push_back(parentElement[element2Index]);
                            }
                            else
                            {
                                int elementIndex = rand() % parentElement.size();
                                childElement.push_back(parentElement[elementIndex]);
                            }
                        }
                    }

                    /*--- MENENTUKAN SKILL CHILD ---*/
                    // MENGOLEKSI SKILL PARENT1 KE DALAM PARENTSKILL
                    for (int i = 0; i < parent1.getSkills().size(); i++)
                    {
                        parentSkill.push_back(parent1.getSkills()[i]);
                    }

                    // MENGOLEKSI SKILL PARENT2 KE DALAM PARENTSKILL
                    for (int i = 0; i < parent2.getSkills().size(); i++)
                    {
                        // Mengecek apakah skill dari skillParent2 sudah ada di skillParent
                        bool present = false;
                        for (int j = 0; j < parentSkill.size(); j++)
                        {
                            if (parent2.getSkills()[i].getSkillId() == parentSkill[j].getSkillId())
                            {
                                present = true;
                            }
                        }

                        // Mengoleksi elementParent2 ke dalam elementParent
                        if (!present)
                        {
                            parentSkill.push_back(parent2.getSkills()[i]);
                        }
                    }

                    // Max Mastery Level Skill
                    Skill maxMasteryLevelSkill;
                    while (childSkill.size() < 5 && parentSkill.size() != 0){
                        // Mengambil Skill dengan Max Mastery Level
                        maxMasteryLevelSkill = parentSkill[0]; 
                        for (int i = 1; i < parentSkill.size(); i++)
                        {
                            if (maxMasteryLevelSkill.getMasteryLevel() < parentSkill[i].getMasteryLevel())
                            {
                                maxMasteryLevelSkill = parentSkill[i];
                            }
                            
                        }
                        // Mengumpulkan Skill Max Mastery Level
                        vector<Skill> skillOfNMasteryLevel;
                        for (int i = 0; i < parentSkill.size(); i++)
                        {
                            if (parentSkill[i].getMasteryLevel()== maxMasteryLevelSkill.getMasteryLevel())
                            {
                                skillOfNMasteryLevel.push_back(parentSkill[i]);
                                parentSkill.erase(parentSkill.begin()+i);
                            }
                            
                        }                    

                        // Mengumpulkan Skill Max Mastery Level dari Parent A
                        if (skillOfNMasteryLevel.size() > 1){
                            vector<Skill> skillOfNMasteryLevelParentA;
                            for (int i = 0; i < skillOfNMasteryLevel.size(); i++){
                                for (int j = 0; j < parent1.getSkills().size(); j++){
                                    if (skillOfNMasteryLevel[i].getSkillId() == parent1.getSkills()[j].getSkillId()){
                                        skillOfNMasteryLevelParentA.push_back(skillOfNMasteryLevel[i]);
                                        skillOfNMasteryLevel.erase(skillOfNMasteryLevel.begin()+i);
                                    }
                                }
                            }
                            for (int i = 0; i < skillOfNMasteryLevelParentA.size(); i++)
                            {
                                childSkill.push_back(skillOfNMasteryLevelParentA[i]);
                            }
                            for (int i = 0; i < skillOfNMasteryLevel.size(); i++)
                            {
                                childSkill.push_back(skillOfNMasteryLevel[i]);
                            }

                        } else {
                            childSkill.push_back(skillOfNMasteryLevel[0]);
                            skillOfNMasteryLevel.erase(skillOfNMasteryLevel.begin() + 0);
                        }
                    } // childSkill.size() >= 5 atau parentSkill.size() = 0
                    
                    // Membuang skill ke-5 dan seterusnya
                    if (childSkill.size() > 4)
                    {
                        for (int i = 4; i < childSkill.size(); i++)
                        {
                            childSkill.erase(childSkill.begin()+i);
                        }
                        
                    }

                    bool bothParentHave = false;
                    for (int i = 0; i < childSkill.size(); i++)
                    {
                        int j = 0;
                        bool parent1Have = false;
                        while (!parent1Have && j < parent1.getSkills().size()){
                            if (parent1.getSkills()[j].getSkillId() == childSkill[i].getSkillId())
                            {
                                parent1Have = true;
                            }
                            
                            j++;
                        }
                        
                        int k = 0;
                        bool parent2Have = false;
                        while (!parent2Have && k < parent2.getSkills().size()){
                            if (parent2.getSkills()[k].getSkillId() == childSkill[i].getSkillId())
                            {
                                parent1Have = true;
                            }
                            
                            k++;
                        }

                        bothParentHave = parent1Have && parent2Have;
                        if (bothParentHave)
                        {
                            if (parent1.getSkills()[j].getMasteryLevel() == parent2.getSkills()[k].getMasteryLevel())
                            {
                                childSkill[i].setMasteryLevel(parent1.getSkills()[j].getMasteryLevel() + 1);
                            } else {
                                if (parent1.getSkills()[j].getMasteryLevel() > parent2.getSkills()[k].getMasteryLevel())
                                {
                                    childSkill[i].setMasteryLevel(parent1.getSkills()[j].getMasteryLevel());
                                } else {
                                    childSkill[i].setMasteryLevel(parent2.getSkills()[k].getMasteryLevel());
                                }
                                
                            }
                            
                        }
                        
                        
                    }

                    // MENENTUKAN ID
                    int maxID = ensiklopedia.allEngimon()[0][0].getId();
                    for (int i = 0; i < ensiklopedia.allEngimon().size(); i++)
                    {
                        for (int j = 0; j < ensiklopedia.allEngimon()[i].size(); j++)
                        {
                            if (maxID < ensiklopedia.allEngimon()[i][j].getId())
                            {
                                maxID = ensiklopedia.allEngimon()[i][j].getId();
                            }
                        }
                    }
                    childID = maxID + 1;

                    Engimon child(childName, childSpecies, childID, childElement);
                    child.setParentNames(parent1.getName(), parent2.getName());
                    child.setParentSpecies(parent1.getSpecies(), parent2.getSpecies());
                    for (int i = 0; i < childSkill.size(); i++)
                    {
                        child.addSkill(childSkill[i]);
                    }

                    EngimonUser childUser(child);

                    player.Add_inv_engimon(childUser);
                    
                    parent1.setLevel(parent1.getLevel() - 30);
                    parent2.setLevel(parent2.getLevel() - 30);
                }
            }
        }
    }
};

#endif