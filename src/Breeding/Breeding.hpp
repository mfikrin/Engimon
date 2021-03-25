#ifndef BREEDING__HPP
#define BREEDING__HPP
#include "../Player/Player.hpp"
#include "../BookOfLore/BookOfLore.hpp"
#include "../Element/Element.hpp"
#include "../Engimon/Engimon.hpp"
class Breeding
{
public:
    Engimon breeding(Player player, BookOfLore ensiklopedia, Engimon parent1, Engimon parent2)
    {
        if (player.get_inv_engimon().get_nItem() == MAX_ENGIMON_INV) /* Inventory penuh */
        {
            cout << "Inventory penuh!" << endl;
        }
        else
        {
            bool parent1Available = player.get_inv_engimon().check_item_availability(parent1.getId());
            bool parent2Available = player.get_inv_engimon().check_item_availability(parent2.getId());
            if (!parent1Available) // parent1 ga ada di inventory
            {
                if (parent2Available) // parent2 ada di inventory
                {
                    cout << "Parent 1 tidak ada di inventory" << endl;
                }
                else
                { // parent2 ga ada di inventory juga
                    cout << "Parent 1 dan Parent 2 tidak ada di inventory" << endl;
                }
            }
            else if (!parent2Available)
            { // parent1 ada di inventory tapi parent2 ga ada
                cout << "Parent 2 tidak ada di inventory" << endl;
            }
            else
            {                                                           // parent1 dan parent2 ada di inventory
                if (parent1.getLevel() < 30 || parent2.getLevel() < 30) // Salah satu parent berlevel kurang dari 30
                {
                    if (parent1.getLevel() < 30)
                    {
                        if (parent2.getLevel() >= 30)
                        {
                            cout << "Level Parent 1 kurang dari 30!" << endl;
                        }
                        else
                        {
                            cout << "Level Parent 1 dan Parent 2 kurang dari 30!" << endl;
                        }
                    }
                    else
                    {
                        cout << "Level Parent 2 kurang dari 30!" << endl;
                    }
                }
                else
                { // Level kedua parent >= 30
                    int childID;
                    vector<Element> parentElement;
                    vector<Element> parent1Element = parent1.getElements();
                    vector<Element> parent2Element = parent2.getElements();
                    vector<Element> childElement;
                    string childName;
                    string childSpecies;
                    cout << "Masukkan nama anak!" << endl;
                    cin >> childName;

                    // MENGOLEKSI ELEMENT PARENT1 KE DALAM ELEMENTPARENT
                    for (int i = 0; i < parent1Element.size(); i++)
                    {
                        parentElement.push_back(parent1Element[i]);
                    }

                    // MENGOLEKSI ELEMENT PARENT2 KE DALAM ELEMENTPARENT
                    for (int i = 0; i < parent2Element.size(); i++)
                    {
                        // Mengecek apakah element dari elementParent2 sudah ada di elementParent
                        bool present = false;
                        for (int j = 0; j < parentElement.size(); j++)
                        {
                            if (parent2Element[i] == parentElement[j])
                            {
                                present = true;
                            }
                        }

                        // Mengoleksi elementParent2 ke dalam elementParent
                        if (!present)
                        {
                            parentElement.push_back(parent2Element[i]);
                        }
                    }

                    // MEMBANDINGKAN ELEMENT KEDUA PARENT
                    if (parent1Element.size() == parent2Element.size())
                    {
                        bool parentSimilarity = true;
                        int i = 0;
                        while (i < parent1Element.size() && parentSimilarity)
                        {
                            if (parent1Element[i] != parent2Element[i])
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
                                if (player.get_advantage(parent1Element[0], parent2Element[0]) > player.get_advantage(parent2Element[0], parent1Element[0]))
                                {
                                    childSpecies = parent1.getSpecies();
                                    childID = parent1.getId();
                                    childElement = parent1.getElements();
                                }
                                else if (player.get_advantage(parent1Element[0], parent2Element[0]) < player.get_advantage(parent2Element[0], parent1Element[0]))
                                {
                                    childSpecies = parent2.getSpecies();
                                    childID = parent2.getId();
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
                    { // Elemen kedua parent berbeda
                        if (parent1Element.size() == 1 && parent2Element.size() == 1)
                        {
                            if (player.get_advantage(parent1Element[0], parent2Element[0]) > player.get_advantage(parent2Element[0], parent1Element[0]))
                            {
                                childSpecies = parent1.getSpecies();
                                childID = parent1.getId();
                                childElement = parent1.getElements();
                            }
                            else if (player.get_advantage(parent1Element[0], parent2Element[0]) < player.get_advantage(parent2Element[0], parent1Element[0]))
                            {
                                childSpecies = parent2.getSpecies();
                                childID = parent2.getId();
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

                    parent1.setLevel(parent1.getLevel() - 30);
                    parent2.setLevel(parent2.getLevel() - 30);

                    return child;
                }
            }
        }
    }
};

#endif