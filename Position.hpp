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
        Position() : x(0), y(0) {}
        Position(int x_, int y_){
            x = x_;
            y = y_;
        }
        
        // Getter X,Y 
        int getXPos(){
            return x;
        }
        int getYPos(){
            return x;
        }

        void up(){
            y--;
        }

        void down(){
            y++;
        }

        void left(){
            x--;
        }

        void right(){
            x++;
        }
        
};

#endif // _Position_hpp_
