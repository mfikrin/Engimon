#ifndef _Position_hpp_
#define _Position_hpp_

#include <iostream>
#include <string>

using namespace std;

class Position{
    protected:
        int x;
        int y;
        // Landscape landscape;
        // Generic class entities
    public:
    Position();
    Position(int x_, int y_){
        x = x_;
        y = y_;
    }
        
};

#endif // _Position_hpp_
