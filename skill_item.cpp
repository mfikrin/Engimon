#include <iostream>

using namespace std;

#define MAX_INV 1000
template<class T, int N>

class Inventory
{
    private:
        T *elements;
        int n_item;
    public:
        Inventory();
        ~Inventory();
        virtual void learn();

};
