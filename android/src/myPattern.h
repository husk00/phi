#ifndef _MY_PATTERN // if this class hasn't been defined, the program can define it
#define _MY_PATTERN // by using this if statement you prevent the class to be called more
                 // than once which would confuse the compiler

#include "ofMain.h"

class myPattern {

    public:
        // methods
        void update();
        void draw();
        void _touchMoved(int x, int y);
        void _touchDown(int x, int y, int button);
        void _touchUp(int x, int y, int button);

       myPattern(int id); // constructor - used to initialize an object, if no properties are passed
                  //               the program sets them to the default value

        //variables
        bool isOver, isSelected,isDragging, occupied;
        int id, page,l,f,onStep;
        ofTrueTypeFont font;
        ofColor color;
        ofVec2f startPos, pos;
        float radius;

    private: // place private functions or variables declarations here

}; // dont't forget the semicolon!!

#endif
