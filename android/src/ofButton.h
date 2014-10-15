#ifndef _OF_BUTTON // if this class hasn't been defined, the program can define it
#define _OF_BUTTON // by using this if statement you prevent the class to be called more
                 // than once which would confuse the compiler

#include "ofMain.h"


class ofButton {

    public:
        // methods
        void update();
        void draw();
        void _touchUp(int x, int y, int button);
        void _touchDown(int x, int y, int button);
        bool inside(int x, int y);

       ofButton(int _id, ofPoint _pos,string _text, bool image=false); // constructor - used to initialize an object, if no properties are passed
                  //               the program sets them to the default value

        //variables
        ofPoint pos;
        ofColor buttonColor;
        ofTrueTypeFont font;
        ofImage background;
        ofRectangle form;
        int id, fontSize;
        bool image, action[3], over;
        string text;


    private: // place private functions or variables declarations here

}; // dont't forget the semicolon!!

#endif
