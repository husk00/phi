#ifndef _OF_STEP // if this class hasn't been defined, the program can define it
#define _OF_STEP // by using this if statement you prevent the class to be called more
                 // than once which would confuse the compiler

#include "ofMain.h"
#include "ofxOsc.h"

#define M8HOST "192.168.0.123"
#define M8PORT 8002

#define LIVEHOST "192.168.0.123"
//#define LIVEHOST "127.0.0.1"
#define LIVEPORT 9000

class ofStep {

    public:
        // methods
        void update(int counter);
        void draw();
        void _mouseMoved(int x, int y);
        void _mouseDragged(int x, int y, int button);
        void _mousePressed(int x, int y, int button);
        void _mouseReleased(int x, int y, int button);
        void insideOver(int x, int y);
        bool inside(int x, int y);
        void drawPattern(int id);
        void getCenter();
        void sendToM8();
        void sendToLive();

       ofStep(int id, ofPoint _center); // constructor - used to initialize an object, if no properties are passed
                  //               the program sets them to the default value

        //variables
        ofPolyline step;
        ofPath stepPath;
        int id, numPattern;
        ofPoint center, myCenter;
        ofColor sliceColor;
        bool active,over, hasPattern, send;
        ofxOscSender M8sender;
        ofxOscSender liveSender;


    private: // place private functions or variables declarations here

}; // dont't forget the semicolon!!

#endif
